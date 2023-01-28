//
// Created by Rufelle on 23/01/2023.
//
#include "constants.h"
#ifndef CHAINC_ERRORHELPER_H
#define CHAINC_ERRORHELPER_H



namespace chainhelp{


    void resolveOperands(const std::vector<token> tokens){
        bool first = true;
        strvector valid;
        for (auto &i : tokens){
            for (auto &j : *constants.commands()){
                const auto & ref = j.first;
                auto find = i.name.find(ref);
                if (find!=npos){
                    first = false;
                    valid.emplace_back(i.name.substr(find, ref.size()));
                }
            }
            for (auto &j : *constants.directives()){
                const auto & ref = j.first;
                auto find = i.name.find(ref);
                if (find!=npos){
                    first = false;
                    valid.emplace_back(i.name.substr(find, ref.size()));
                }
            }
            for (auto &j : *constants.registers()){
                const auto & ref = j.first;
                auto find = i.name.find(ref);
                if (find!=npos){
                    first = false;
                    valid.emplace_back(i.name.substr(find, ref.size()));
                }
            }

            for (auto &j : constants.labels()){
                const auto & ref = j.first;
                auto find = i.name.find(ref);
                if (find!=npos){
                    first = false;
                    valid.emplace_back(i.name.substr(find, ref.size()));
                }
            }

        }
        if (!first){
            std::cerr << ">>> Consider, maybe you need to splice the command with commas: ";
            for (int x=0; x<valid.size(); x++){
                std::cerr << valid[x];
                if (x!=valid.size()-1){
                    std::cerr << ", ";
                }
            }
            std::cout << std::endl;
        }
    }



    void findOperands(const std::vector<token> & tokenstream){
        for (auto& tokens : tokenstream){
            for (auto &commands : *constants.commands()){
                // j iterates through all commands
                size_t it = 0;
                auto command = commands.first;
                size_t max = commands.first.length();
                if (max >= 4) max = 3;
                else if (max == 3) max = 2;
                for (auto &tokenchar : tokens.name){
                    if (tokenchar ==command[it]){
                        it++;
                    } if (it == (max) && tokens.name.length() != command.length()){
                        std::cerr << ">>> Consider: could you have meant '" << commands.first << "' instead of '" << tokens.name << "'?\n";
                        continue;
                    }
                }
            }
            for (auto &commands : *constants.directives()){
                // j iterates through all commands
                size_t it = 0;
                auto command = commands.first;
                size_t max = commands.first.length();
                if (max >= 4) max = 3;
                else if (max == 3) max = 2;
                for (auto &tokenchar : tokens.name){
                    if (tokenchar ==command[it]){
                        it++;
                    } if (it == (max) && tokens.name.length() != command.length()){
                        std::cerr << ">>> Consider: could you have meant '" << commands.first << "' instead of '" << tokens.name << "'?\n";
                    }
                }
            }
            for (auto &commands : constants.labels()){
                // j iterates through all commands
                size_t it = 0;
                auto command = commands.first;
                size_t max = commands.first.length();
                if (max >= 4) max = 3;
                else if (max == 3) max = 2;
                for (auto &tokenchar : tokens.name){
                    if (tokenchar ==command[it]){
                        it++;
                    } if (it == (max)  && tokens.name.length() != command.length()){
                        std::cerr << ">>> Consider: could you have meant '" << commands.first << "' instead of '" << tokens.name << "'?\n";
                    }
                }
            }
            for (auto &commands : *constants.registers()){
                // j iterates through all commands
                size_t it = 0;
                auto command = commands.first;
                size_t max = commands.first.length();
                if (max >= 4) max = 3;
                else if (max == 3) max = 2;
                for (auto &tokenchar : tokens.name){
                    if (tokenchar ==command[it]){
                        it++;
                    } if (it == (max) && tokens.name.length() != command.length()){
                        std::cerr << ">>> Consider: could you have meant '" << commands.first << "' instead of '" << tokens.name << "'?\n";
                    }
                }
            }
        }
    }
}


#endif //CHAINC_ERRORHELPER_H
