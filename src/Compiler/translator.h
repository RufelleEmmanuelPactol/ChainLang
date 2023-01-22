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
    static void translate (Unit unit, dive::FileWriter& fw){
        std::string buffer;
        // debug
        buffer.append(unit.labels.append(": "));
        buffer.append(unit.op.name + ", ");
        for (auto &i : unit.operands){
            buffer.append(i.name + ", ");
        }
        fw.writeLine(buffer + '\n');
        fw.flush();
    }
};

#endif //CHAINC_TRANSLATOR_H
