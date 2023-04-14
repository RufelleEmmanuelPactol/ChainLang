//
// Created by Rufelle on 12/04/2023.
//

#ifndef CHAINC_VMEXCEPTIONS_H
#define CHAINC_VMEXCEPTIONS_H
#include <iostream>
using std::cerr;
#include <string>
using std::string;
#include "../extern/diveColors.h"

namespace VMexcept{


    void InvalidProgramSequence(const string &opcode, const int address) {
        using namespace color;
        cerr << "ERR 0x1 Command Load Error [VMError]: Invalid OPCODE '" << opcode << "' located at address '"
             << address << "'.\n" <<
             "Possible causes for OPCODE load error include the following:\n" <<
             colorize(yellow, "[1] Mixture of .bss variables with commands\n"
             "[2] Missing start directive.\n"
             "[3] Incorrect start address.\n"
             "[4] Tampered code.\n") <<
             colorize(bright_blue, "<Please Check Your Code>\n");
        colorize::end_state();
            exit(10);
    }
}

#endif //CHAINC_VMEXCEPTIONS_H
