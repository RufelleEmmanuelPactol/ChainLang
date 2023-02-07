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

    static void translate (AST ast, dive::FileWriter& fw){
        if (!ast.labels.empty()){
            constants.emplaceLabel(ast.labels, memory.PC());
        }
        if (ast.op.name != "badtoken"){
            if (!ast.op.opcode.empty()){
                memory.write(memory.PC(), ast.op.opcode);
                memory.inc();
                string operator_write;
                // operands checker: where 0001 is register and 0000 is address
                for (size_t i = 1; i<= ast.operands.size(); i++)
                {
                    if (ast.operands[i-1].datatype == reg)
                    {
                        operator_write.append("0000");
                    } else
                    {
                        operator_write.append("0001");
                    }
                }
            }
        }

        if (!ast.operands.empty()){
            for (auto i : ast.operands){
                    if (i.datatype == num){

                    }
            }
        }
    }
};

#endif //CHAINC_TRANSLATOR_H
