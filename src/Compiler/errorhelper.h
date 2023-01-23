//
// Created by Rufelle on 23/01/2023.
//
#include "constants.h"
#ifndef CHAINC_ERRORHELPER_H
#define CHAINC_ERRORHELPER_H



namespace chainhelp{


    void resolveOperands(const std::vector<token>&tokens){
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
            std::cerr << "Consider, maybe you forgot to add a comma after: ";
            for (int x=0; x<valid.size(); x++){
                std::cerr << valid[x];
                if (x!=valid.size()-1){
                    std::cerr << ", ";
                }
            }
        }
    }
}


#endif //CHAINC_ERRORHELPER_H
