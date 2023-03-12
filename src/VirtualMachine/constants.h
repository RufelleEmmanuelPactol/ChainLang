//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_CONSTANTS_H
#define CHAINC_CONSTANTS_H
#include <map>
#include <string>
#include "../compiler/tokens.h"
#include "vm_macros.h"
struct Constants{

private:
    std::map<string, token> m_registers;
    std::map<string, token> m_commands;
    std::map<string, token> m_directives;
    std::map<string, int> m_labels;
    
public:
    Constants(){

        // init for registers
        m_registers.emplace("ac", token(not_op, reg, reg16, "ac", "10110001"));
        m_registers.emplace("acx", token(not_op, reg, reg8, "acx", "10100000"));
        m_registers.emplace("acy", token(not_op, reg, reg8, "acy", "10100001"));
        m_registers.emplace("r", token(not_op, reg, reg16, "r", "10110010"));
        m_registers.emplace("rx", token(not_op, reg, reg8, "rx", "10100010"));
        m_registers.emplace("ry", token(not_op, reg, reg8, "ry", "10100011"));
        m_registers.emplace("flag", token(not_op, reg, flag, "flag", "10100000"));


        // not accessible for users
        /*      m_registers.emplace("pc", token(not_op, reg16, "pc"));
        m_registers.emplace("ar", token(not_op, reg16, "ar"));
        */

        // init for m_directives
        m_directives.emplace("start", token(op, directive, mem, 1, "start"));
        m_directives.emplace("org", token(op, directive, mem, 1, "org"));
        m_directives.emplace("db", token(op, directive, alloc,  1, reg8, "db"));
        m_directives.emplace("dw", token(op, directive, alloc, 1, reg16, "dw"));

        // init for m_commands
        m_commands.emplace("add", token(op, complex, math, 2, "add", "00000100"));
        m_commands.emplace("sub", token(op, complex, math, 2, "sub", "00000101"));
        m_commands.emplace("mul", token(op, complex, math, 2, "mul", "00000110"));
        m_commands.emplace("div", token(op, complex, math, 2, "div", "00000111"));
        m_commands.emplace("cmp", token(op, complex, math, 2,"cmp", "00001010"));
        m_commands.emplace("equ", token(op, complex, math, 2, "equ", "00001011"));
        m_commands.emplace("not", token(op, single_op, reg_param, 1, "not", "00001100"));
        m_commands.emplace("jmp", token(op, basic,mem, 1, "jmp", "00001101"));
        m_commands.emplace("jpt", token(op, complex, mem, 1, "jpt", "00001110"));
        m_commands.emplace("jpf", token(op, complex, mem, 1, "jpf", "00001111"));
        m_commands.emplace("char", token(op, basic, reg_param8, 1,"char", "00000001"));
        m_commands.emplace("int8", token(op, basic, reg_param8, 1, "int8", "00000010"));
        m_commands.emplace("int16", token(op, basic, reg_param16, 1, "int16", "00000011"));
        m_commands.emplace("mov", token(op, basic, mov, 2, "mov", "00001000"));
        m_commands.emplace("inc", token(op, single_op, reg_param, 1, "inc", "00001000"));
        m_commands.emplace("dec", token(op, single_op, reg_param, 1, "dec", "00001001"));
        m_commands.emplace("swp", token(op, basic, reg_param, 2, "swp", "00010001"));
        m_commands.emplace("end", token(op, basic, no_op, 0, "end", "01010101"));
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

    bool allDecimal (const std::string & str){
        for (auto i : str){
            if (!isDecimal(i)) return false;
        } return true;
    }

    bool allBinary (const std::string & str){
        for (auto i : str){
            if (!isBinary(i)) return false;
        } return true;
    }

    auto isHex(char & change){
        if (isDecimal(change)) return true;
        change = static_cast<char>(toupper(change));
        if (change >= 'A' && change <= 'F'){
            return true;
        } return false;
    }

    auto& labels(){
        return m_labels;
    }


    void emplaceLabel(const string& label_name , int address){
        if (m_labels.find(label_name)!=m_labels.end()){
            errMachineError();
        }
        m_labels.emplace(label_name, address);
    }

    auto fetchLabel(const string& find){
        if (m_labels.find(find)==m_labels.end()){
            errMachineError();
        }
        return m_labels[find];
    }

    int binToDecimal(std::string str) {
        int result = 0;
        int len = str.length();
        for (int i = 0; i < len; i++) {
            if (str[i] == '1') {
                result += pow(2, len - 1 - i);
            } else if (str[i] != '0') {
                // if the string contains a non-binary character, return -1 to indicate an error
                return -1;
            }
        }
        return result;
    }





};

Constants constants;
#endif //CHAINC_CONSTANTS_H
