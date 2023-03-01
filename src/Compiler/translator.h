//
// Created by Rufelle on 21/01/2023.
//

#ifndef CHAINC_TRANSLATOR_H
#define CHAINC_TRANSLATOR_H
#include "tokens.h"
#include <vector>
#include "../extern/divefile.h"
#include "compiler_macros.h"



class Translator {
public:

    // OPERAND OPCODE
    const string EMPTY = "00000000";
    const string NOOP = "0000";
    const string REGISTER8 = "0001";
    const string REGISTER16 = "0010";
    const string ADDRESS = "0011";
    const string POINTER = "0100";



    void translate (AST ast){
        bool writeMode = false;
        if (!ast.labels.empty()){
            constants.emplaceLabel(ast.labels, memory.PC());
        }

        if (ast.op.name != "badtoken"){
            // directives execution
            if (ast.op.datatype == directive){

                // org
                if (ast.op.name == "org"){
                    memory.set(atoi(ast.operands[0].name.c_str()));
                    return;
                }

                // db and dw
                if (ast.op.operand == alloc){
                    writeMode = true;
                }


            }


            if (!ast.op.opcode.empty()){
                memory.write(8, ast.op.opcode);
                memory.inc();
                string operator_write;




                if (ast.operands.size() == 0 ){
                    memory.write(8, EMPTY);
                    goto operator_analysis;
                }
                operator_write.append(getOpType(ast.operands[0]));
                if (ast.operands.size() == 1){
                    operator_write.append(NOOP);
                } else {
                    operator_write.append(getOpType(ast.operands[1]));
                }

                memory.write(8, operator_write);
                memory.inc();
            }
        }

        operator_analysis:
        if (!ast.operands.empty()){
            for (auto i : ast.operands){

                // label checkers
                    if (i.datatype == label_ref || i.datatype == mem_label){
                        auto found_label = constants.labels().find(i.name);
                        if (found_label == constants.labels().end()) chain::NoSuchLabelException(i.name);
                        auto get_address = constants.fetchLabel(i.name);
                        std::cout << "Ad: " << constants.decToBin(get_address, 16) << ' ' << get_address << std::endl;
                        memory.write(16, constants.decToBin(get_address, 16));
                        memory.inc(2);
                    }

                    else if (i.datatype == mem_reg){
                        auto opcode_finder_reg = constants.registers()->at(i.name);
                        memory.write(8, opcode_finder_reg.opcode);
                    }

                    // mem_ref writer

                    else if (i.datatype == reference){
                        auto str_ptr = i.name.c_str();
                        auto end_ptr = str_ptr + i.name.length()-1;
                        memory.write(16, constants.decToBin(16, strtol(str_ptr, const_cast<char **>(&end_ptr), 10)));
                    }

                    else if (writeMode){
                        if (ast.op.name == "dw"){
                            memory.write(16, constants.decToBin(ast.operands[0].numeric, 16));
                            memory.inc(2);
                        } else {
                            if (ast.operands[0].datatype == str) {
                                for (auto i : ast.operands[0].name){
                                    memory.write(8, constants.decToBin(i, 8));
                                    memory.inc();
                                }
                            } else {
                                memory.write(8, constants.decToBin(ast.operands[0].numeric, 8));
                                memory.inc();
                            }
                        }

                        return;
                    }



                    else {
                        memory.write(8, i.opcode);
                        memory.inc();
                    }
            }
        }
    }

    string getOpType (const token & op){
        if (op.datatype == reg){
            if (op.reg == reg8){
                return REGISTER8;
            }
            return REGISTER16; // 16 bit register
        } else if (op.datatype == reference) return ADDRESS;
        else if (op.datatype == label_ref) return ADDRESS;
        else if (op.datatype == mem_label) return POINTER;
        return NOOP;
    }

};

#endif //CHAINC_TRANSLATOR_H
