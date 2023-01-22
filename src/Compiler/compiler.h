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
namespace chain
{
    auto compiler (const std::string& path){
        //FileReader fr = FileReader("../src/compiler/hello.link");
        FileReader fr = FileReader(path);
        auto fw = dive::FileWriter(output_name + ".bin");

        if (!fr.isOpen()){
            FileNotFoundException(path);
        }


        auto commands = fr.readFile();
        for (auto i : *commands){
            line++;
            m_line = i;
            auto tokenstream = Tokenizer::stream(stack_split(i));
            auto ast = Parser::stream(tokenstream);
            Translator::translate(ast, fw);
        }





    }
}

#endif //CHAIN_COMPILER_MODULE_H

#endif //CHAINC_COMPILER_H
