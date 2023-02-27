//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_ARGSHANDLER_H
#define CHAIN_ARGSHANDLER_H
#include "exceptions.h"
#include "compiler.h"

namespace chain
{
    auto null_args (strvector_p args){

    }

    auto handle (strvector_p args){
        if (args.size()<=2){
            if (args.size()==2){
                NoPathProvidedException(args.at(1));
            }
            null_args(args);
            return;
        }

        strvector commands;
        strvector arguments;

        int c = 0;
        for (auto&i : args) {
            if (c != 0) {
                if (c % 2 == 0) {
                    arguments.emplace_back(i);
                } else {
                    commands.emplace_back(i);
                }
            }
            c++;
        }

        if (arguments.size()!=commands.size()){
            InvalidCommandSequence(args);
        }

        string fn;
        bool compileq = false;
        for (int i = 0; i<arguments.size(); i++){
            std::cout << "args " << i << std::endl;
            auto &j = arguments[i];
            auto &k = commands[i];


            if (k == "-c"){
                std::cout << "-c\n";
                fn = j;
                auto last = fn.find_last_of('\\') > fn.find_last_of('/') ? fn.find_last_of('/') : fn.find_last_of('\\');
                if (last == npos){
                    last = 0;
                }
                output_name = fn.substr(last, fn.find('.'));
                compileq = true;
                std::cout << "Finished task";
            }

            if (k == "-o"){
                std::cout << "-o\n";
                output_name = j;
            }


        }
        // compile command takes last precedence
        if (compileq){
            compiler(fn);
        } else if (!compileq){
            exit(0);
        }



    }

}

#endif //CHAIN_ARGSHANDLER_H
