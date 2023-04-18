//
// Created by Rufelle on 20/01/2023.
//

#ifndef CHAINC_COMPILER_H
#define CHAINC_COMPILER_H


//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_COMPILER_MODULE_H
#define CHAIN_COMPILER_MODULE_H
#include "translator.h"
#include "splitter.h"
#include "tokenizer.h"
#include "../extern/divefile.h"
#include <vector>
#include "parser.h"
#include <functional>
#include "writer.h"




namespace chain
{

    /*
     * The check_piece code is responsible for
     * checking whether if an entire line is to
     * be ignored or not.
     */
    auto check_piece (const string & i) -> bool {
        for (auto &j : i){
            if (j == ' ') continue;
            if (j == ';') return true;
            return false;
        }
        return false;
    }

    auto compiler (const std::string& path){

        // opens the source code in the file
        FileReader fr = FileReader(path, true);
        if (!fr.isOpen()){
            FileNotFoundException(path);
        }

        std::vector<AST> AbstractSyntaxTree;

        // valid indexes that are not empty tokens
        auto indexes = std::vector<size_t>();


        auto commands = fr.readFile();
        for (auto i : *commands){

            /*
             * The following lines are handling line
             * management, omitting empty lines, while
             * still making sure that the errors thrown
             * by the compiler still display the correct
             * line numbers.
             */

            line++;
            if (i.empty() || check_piece(i)) continue;
            m_line = i; // represents the string stream at this specified line
            indexes.push_back(line); // pushes back valid lines

            /*
             *  The following line of code is concerned with
             *  two parts of the tokenizer. The first one
             *  is invoked with the splitter which handles
             *  virtual machine directives and classifying
             *  tokens properly using signatures such as
             *  "$$VARCHAR$$".
             *
             *  Aside from splitting, the splitter is also
             *  involved in checking for delimiters such as
             *  ':', '"', ' ', and ','. Moreover, it ignores
             *  comments marked with ';'.
             *
             *  On the other hand, the Tokenizer
             *  is involved in creating object representations
             *  of the tokens and removes the signatures placed
             *  by the splitter.
             */
            auto tokenstream = Tokenizer::stream(stack_split(i));

            /*
             * The following code holds the parser
             * which is responsible for checking code
             * integrity and grammar correctness.
             * Whenever the parser fails to do its job
             * and allows illegal code to pass through,
             * the compiler in the memory writing stage
             * will throw an 'InternalCompilerError'.
             *
             * The worst case for a parsing failure is that
             * it will cause the Virtual Machine to crash.
             * This is critical as the virtual machine
             * is completely decoupled from the compiler,
             * and debugging these two together can be
             * quite problematic. When this happens,the virtual machine
             * can throw errors such as 'VMError: Command Load Error'.
             */

            auto ast = Parser::stream(tokenstream);

            /*
             * After parsing, the tokens will then be
             * pushed back to the Abstract Syntax
             * Tree.
             */
            AbstractSyntaxTree.emplace_back(ast);
        }


        // move this to the writer unit after
        // the m_line is a general macro used for detecting errors
        size_t ctr = 0;
        Translator t;


        // check for an end token
        if (!constants.END_TOKEN) NoEndDetectedToken(path);

        /*
         * This is the translator module. This module
         * is concerned in translating the tokens to
         * binary code. It writes the code directly to
         * the virtual memory.
         */
        for (auto &i: AbstractSyntaxTree){
            line = indexes[ctr];
            ctr++;
            m_line = commands->at(line-1);
            t.translate(i);
        }


        string extension = ".exec";
        // checks if the 'compile to binary' flag is turned on
        if (constants.COMPILE_MODE_BINARY) extension = ".binc";
        auto fw = dive::FileWriter(output_name + extension);

        /*
         * This is the writer. It writes the virtual memory
         * and turns it into a file. This is also where it can
         * either write 'ASCII binary' or compressed binary.
         * This is also the stage where it writes the start
         * variables and the compiler flag variables.
         */
        Writer write = Writer(fw);
    }
}

#endif //CHAIN_COMPILER_MODULE_H

#endif //CHAINC_COMPILER_H
