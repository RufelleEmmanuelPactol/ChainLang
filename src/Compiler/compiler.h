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
#include "exceptions.h"
#include <vector>
#include "parser.h"
#include <functional>
#include "writer.h"
namespace chain
{
    auto checkpiece (const string & i) -> bool {
        for (auto &j : i){
            if (j == ' '){
                continue;
            }
            if (j == ';'){
                return true;
            }
            return false;
        }
        return false;
    }

    auto compiler (const std::string& path){
        //FileReader fr = FileReader("../src/compiler/hello.link");
        FileReader fr = FileReader(path);
        if (!fr.isOpen()){
            FileNotFoundException(path);
        }

        std::vector<AST> AbstractSyntaxTree;
        auto indexes = std::vector<size_t>(); // valid indexes that are not empty tokens
        auto commands = fr.readFile();
        for (auto i : *commands){
            line++;
            if (i.empty() || checkpiece(i)){
                continue;
            }
            m_line = i;
            indexes.push_back(line);
            auto tokenstream = Tokenizer::stream(stack_split(i));
            auto ast = Parser::stream(tokenstream);
            AbstractSyntaxTree.emplace_back(ast);
        }


        // move this to the writer unit after
        // the m_line is a general macro used for detecting errors
        size_t ctr = 0;
        Translator t;
        for (auto &i: AbstractSyntaxTree){
            line = indexes[ctr];
            ctr++;
            m_line = commands->at(line-1);
            t.translate(i);
        }

        auto fw = dive::FileWriter(output_name + ".bcc");
        Writer write = Writer(fw);









    }
}

#endif //CHAIN_COMPILER_MODULE_H

#endif //CHAINC_COMPILER_H
