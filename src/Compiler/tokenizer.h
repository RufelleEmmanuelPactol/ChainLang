//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_TOKENIZER_H
#define CHAINC_TOKENIZER_H
#include "tokens.h"
#include "compiler_macros.h"
#include "constants.h"
class Tokenizer{

public:
    static auto stream(strvector_p stringstream){
        std::vector<token> tokenstream;
        for (auto &i : stringstream){
            std::cout << "debug token: " << i << std::endl;
        }
        for (auto &i : stringstream){
            auto reg = constants.registers()->find(i);
            auto dir = constants.directives()->find(i);
            auto com = constants.commands()->find(i);
            if ( reg != constants.registers()->end()){
                tokenstream.emplace_back(reg->second);
                std::cout << "This is a register\n";
            } else if (dir != constants.directives()->end()){
                tokenstream.emplace_back(dir->second);
                std::cout << "This is a directive\n";
            } else if (com != constants.commands()->end()){
                tokenstream.emplace_back(com->second);
                std::cout << "This is a command\n";
            } else {

                // individual tokens for non-commands
                auto label = i.find(" $$LABEL$$");
                auto literal = i.find(" $$VARCHAR$$");
                auto numeric = i.find (" $$NUMERIC$$");
                auto memory = i.find(" $$MEMLOC$$");

                if (label!=std::string::npos){
                    std::cout << "This is a label\n";
                }
                // implement syntax here

            }

        }
    }


};

#endif //CHAINC_TOKENIZER_H
