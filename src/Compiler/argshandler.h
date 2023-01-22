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
        for (auto&i : args){
            if (c!=0){
                if (c%2==0){
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
            auto &j = arguments[i];
            auto &k = commands[i];

            if (k == "-c"){
                fn = j;
                compileq = true;
            }

            if (k == "-o"){
                output_name = j;
            }


        }
        // compile command takes last precedence
        if (compileq){
            compiler(fn);
        }



    }

}

#endif //CHAIN_ARGSHANDLER_H
