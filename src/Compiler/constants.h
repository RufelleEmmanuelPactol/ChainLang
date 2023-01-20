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

        // not accessible for users
        /*      m_registers.emplace("pc", token(not_op, reg16, "pc"));
        m_registers.emplace("ar", token(not_op, reg16, "ar"));
        m_registers.emplace("flag", token(not_op, reg1, "flag"));*/

        // init for m_directives
        m_directives.emplace("start", token(op, directive, mem, "start"));
        m_directives.emplace("org", token(op, directive, mem, "org"));
        m_directives.emplace("db", token(op, directive, alloc, "db"));
        m_directives.emplace("dw", token(op, directive, alloc, "dw"));
        m_directives.emplace("end", token(op, directive, mem, "end"));

        // init for m_commands
        m_commands.emplace("add", token(op, complex, math, "add"));
        m_commands.emplace("sub", token(op, complex, math, "sub"));
        m_commands.emplace("mul", token(op, complex, math, "mul"));
        m_commands.emplace("div", token(op, complex, math,"div"));
        m_commands.emplace("cmp", token(op, complex, math,"cmp"));
        m_commands.emplace("equ", token(op, complex, math,"equ"));
        m_commands.emplace("jmp", token(op, basic,mem, "jmp"));
        m_commands.emplace("jpt", token(op, complex, mem, "jpt"));
        m_commands.emplace("jpf", token(op, complex, mem, "jpf"));
        m_commands.emplace("char", token(op, basic, print, "char"));
        m_commands.emplace("int8", token(op, basic, print,  "int8"));
        m_commands.emplace("int16", token(op, basic, print, "int16"));
        m_commands.emplace("mov", token(op, basic, mov, "mov"));

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
