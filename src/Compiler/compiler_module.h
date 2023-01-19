//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_COMPILER_MODULE_H
#define CHAIN_COMPILER_MODULE_H
#include "splitter.h"
#include "compiler_module.h"
#include "tokenizer.h"
namespace chain
{
    auto compiler (const std::string& path){
        FileReader fr = FileReader(path);
        auto commands = fr.readFile();
        for (auto& i : *commands){
            line++;
            Tokenizer::stream(stack_split(i));
        }
    }
}

#endif //CHAIN_COMPILER_MODULE_H
