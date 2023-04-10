//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_ARGSHANDLER_H
#define CHAIN_ARGSHANDLER_H
#include "exceptions.h"
#include "compiler.h"
#include <filesystem>
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
            auto &j = arguments[i];
            auto &k = commands[i];


            if (k == "-c"){
                fn = j;
                if (fn == "this") the_chain_lang();
                output_name = std::filesystem::path(fn).filename().string();
                output_name = output_name.substr(0, output_name.find('.'));
                compileq = true;
                continue;
            }

            if (k == "-o"){
                output_name = j;
                continue;
            }

            if (k == "-b")
            {
                if (j!="true") continue;
                constants.COMPILE_MODE_BINARY = true;
                continue;
            }
            InvalidCommandSequence(args);




        }
        // compile command takes last precedence
        if (compileq){
            auto k = std::filesystem::path(fn).extension();
            if (k.string()!=".ch") InvalidFileExtension(fn, k.string());
            compiler(fn);
        } else if (!compileq){
            exit(0);
        }



    }

}

#endif //CHAIN_ARGSHANDLER_H
