
//
// Created by Rufelle on 10/02/2023.
//

#ifndef CHAINC_VM_MACROS_H
#define CHAINC_VM_MACROS_H
#include <iostream>
#include "../extern/preprocessor.h"
#include "../extern/memory_unit.h"
std::size_t MAXCONSTEXPR_line = 0;
#define _LINE_ MAXCONSTEXPR_line
Memory memory = Memory();


void errMachineError(){
    std::cerr << "<!> Runtime Virtual Engine bug. Please contact us at github.\n";
    colorize::end_state();
            exit(3);
}
#endif //CHAINC_VM_MACROS_H

