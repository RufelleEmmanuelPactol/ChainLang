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
        m_registers.emplace("ac", token(not_op, reg, reg16, "ac"));
        m_registers.emplace("acx", token(not_op, reg, reg8, "acx"));
        m_registers.emplace("acy", token(not_op, reg, reg8, "acy"));
        m_registers.emplace("r", token(not_op, reg, reg16, "r"));
        m_registers.emplace("rx", token(not_op, reg, reg8, "rx"));
        m_registers.emplace("ry", token(not_op, reg, reg8, "ry"));
        m_registers.emplace("flag", token(not_op, reg, flag, "flag"));


        // not accessible for users
        /*      m_registers.emplace("pc", token(not_op, reg16, "pc"));
        m_registers.emplace("ar", token(not_op, reg16, "ar"));
        */

        // init for m_directives
        m_directives.emplace("start", token(op, directive, mem, 1, "start"));
        m_directives.emplace("org", token(op, directive, mem, 1, "org"));
        m_directives.emplace("db", token(op, directive, alloc, 1, "db"));
        m_directives.emplace("dw", token(op, directive, alloc, 1, "dw"));
        m_directives.emplace("end", token(op, directive, mem, 0, "end"));

        // init for m_commands
        m_commands.emplace("add", token(op, complex, math, 2, "add"));
        m_commands.emplace("sub", token(op, complex, math, 2, "sub"));
        m_commands.emplace("mul", token(op, complex, math, 2, "mul"));
        m_commands.emplace("div", token(op, complex, math, 2, "div"));
        m_commands.emplace("cmp", token(op, complex, math, 2,"cmp"));
        m_commands.emplace("equ", token(op, complex, math, 2, "equ"));
        m_commands.emplace("jmp", token(op, basic,mem, 1, "jmp"));
        m_commands.emplace("jpt", token(op, complex, mem, 1, "jpt"));
        m_commands.emplace("jpf", token(op, complex, mem, 1, "jpf"));
        m_commands.emplace("char", token(op, basic, print, 1,"char"));
        m_commands.emplace("int8", token(op, basic, print, 1, "int8"));
        m_commands.emplace("int16", token(op, basic, print, 1, "int16"));
        m_commands.emplace("mov", token(op, basic, mov, 2, "mov"));


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


    auto isBinary(const char change){
        if (change=='0' || change=='1'){
            return true;
        } return false;
    }

    auto isDecimal(const char change){
        if (change>='0' && change<='9'){
            return true;
        } return false;
    }

    auto isHex(char & change){
        if (isDecimal(change)) return true;
        change = static_cast<char>(toupper(change));
        if (change >= 'A' && change <= 'F'){
            return true;
        } return false;
    }


    void emplaceLabel(const string& label_name , int address){
        if (m_labels.find(label_name)!=m_labels.end()){
            chain::RepeatLabelException(label_name);
        }
        m_labels.emplace(label_name, address);
    }

    auto getAddress(const string& find){
        if (m_labels.find(find)==m_labels.end()){
            chain::NoSuchLabelException(find);
        }
        return m_labels[find];
    }




};

Constants constants;
#endif //CHAINC_CONSTANTS_H
