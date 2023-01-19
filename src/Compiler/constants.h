//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_CONSTANTS_H
#define CHAINC_CONSTANTS_H
#include <map>
#include "tokens.h"
struct Constants{

private:
    std::map<string, token> m_registers;
    std::map<string, token> m_commands;
    std::map<string, token> m_directives;
    std::map<string, int> m_labels;
    
public:
    Constants(){

        // init for registers
        m_registers.emplace("ac", token(not_op, reg16, "ac"));
        m_registers.emplace("acx", token(not_op, reg8, "acx"));
        m_registers.emplace("acy", token(not_op, reg8, "acy"));
        m_registers.emplace("r", token(not_op, reg16, "r"));
        m_registers.emplace("rx", token(not_op, reg8, "rx"));
        m_registers.emplace("ry", token(not_op, reg8, "ry"));
        m_registers.emplace("pc", token(not_op, reg16, "pc"));
        m_registers.emplace("ar", token(not_op, reg16, "ar"));
        m_registers.emplace("flag", token(not_op, reg1, "flag"));

        // init for m_directives
        m_directives.emplace("start", token(op, directive, "start"));
        m_directives.emplace("org", token(op, directive, "org"));
        m_directives.emplace("db", token(op, directive, "db"));
        m_directives.emplace("dw", token(op, directive, "dw"));
        m_directives.emplace("end", token(op, directive, "end"));

        // init for m_commands
        m_commands.emplace("add", token(op, complex, "add"));
        m_commands.emplace("sub", token(op, complex, "sub"));
        m_commands.emplace("jump", token(op, basic, "jump"));
        m_commands.emplace("jmpt", token(op, complex, "jmpt"));
        m_commands.emplace("jmpf", token(op, complex, "jmpf"));

    }
    
    auto registers(){
        return &m_registers;
    }

    auto commands(){
        return &m_commands;
    }

    auto directives(){
        return &m_directives;
    }


    void emplaceLabel(const string& label_name , int address){
        if (m_labels.find(label_name)!=m_labels.end()){
            chain::RepeatLabelException(label_name);
        }
        m_labels.emplace(label_name, address);
    }

    auto getAddress(const string& find){
        return m_labels[find];
    }
};

Constants constants;
#endif //CHAINC_CONSTANTS_H
