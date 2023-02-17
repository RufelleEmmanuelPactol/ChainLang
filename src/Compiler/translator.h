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

    static void translate (AST ast){
        if (!ast.labels.empty()){
            constants.emplaceLabel(ast.labels, memory.PC());
        }
        if (ast.op.name != "badtoken"){
            if (!ast.op.opcode.empty()){
                memory.write(8, ast.op.opcode);
                memory.inc();
                string operator_write;
                // operands checker: where 0001 is register and 0000 is address
                if (ast.operands.size() == 0 ){
                    memory.write(8, "00000000");
                    goto operator_analysis;
                }
                operator_write.append(getOpType(ast.operands[0]));
                if (ast.operands.size() == 1){
                    operator_write.append("0000");
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
                    }

                    else if (i.datatype == mem_reg){
                        auto opcode_finder_reg = constants.registers()->at(i.name);
                        memory.write(8, opcode_finder_reg.opcode);
                    }

                    // label reference writer

                    else if (i.datatype == label_ref){
                        auto get_address = constants.fetchLabel(i.name);
                        std::cout << "Debug: " << constants.decToBin(get_address, 16) << std::endl;
                        memory.write(16, constants.decToBin(get_address, 16));
                        memory.inc(2);
                    }

                    // mem_ref writer

                    else if (i.datatype == mem){
                        auto str_ptr = i.name.c_str();
                        auto end_ptr = str_ptr + i.name.length()-1;
                        memory.write(16, constants.decToBin(16, strtol(str_ptr, const_cast<char **>(&end_ptr), 10)));
                    }

                    else {
                        memory.write(8, i.opcode);
                        memory.inc();
                    }
            }
        }
    }

    static string getOpType (const token & op){
        if (op.datatype == reg){
            if (op.reg == reg8){
                return "1010"; // 8 bit register
            }
            return "1111"; // 16 bit register
        } return "0001"; // not a register
    }

};

#endif //CHAINC_TRANSLATOR_H
