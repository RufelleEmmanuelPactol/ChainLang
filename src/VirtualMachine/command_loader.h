//
// Created by Rufelle on 24/03/2023.
//


#ifndef CHAINC_COMMAND_LOADER_H
#define CHAINC_COMMAND_LOADER_H
#include "signature.h"
#include "constants.h"
#include "vm_macros.h"
#include <functional>
#define fnsig const std::string & signature, std::string & op1, std::string & op2
#define opcode(x) constants.m_commands[x].opcode

class Command {
    std::map<string, std::function<int
            (fnsig)>>
            function_map;

    // template of functions is the following,
    // function(string signature,
    // string operand1,
    // string operand2);

public:
    Command(){
        function_map.emplace(opcode("add"), add);
        function_map.emplace(opcode("end"), end);
    }


    int load (std::string op, fnsig){

    }



private:

    static int add (fnsig) {
        using namespace signature;
        if (signature == EMPTY) return addbasic();
    }

    static int addbasic(){
        int op1 = memory.binToDec(memory.ac);
        int op2 = memory.binToDec(memory.r);
        auto sequence = memory.to_bitstring(op1+op2, 16);
        printf("The bit sequence of add is: %s with the value %d\n",sequence.c_str(), op1+op2);
        memcpy(memory.ac, sequence.c_str(), sizeof(char)*16);
        return 2;
    }

    static int end(fnsig){
        exit(0);
    }



public:

    void load(const string & opcode) {

    }











};

#undef opcode
#undef fnsig
#endif //CHAINC_COMMAND_LOADER_H
