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
            }
        }
    }
};

#endif //CHAINC_TRANSLATOR_H
