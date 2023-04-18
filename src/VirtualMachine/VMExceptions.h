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
#include <sstream>
namespace VMexcept{

    std::stringstream stream;
    void displayERROR(const std::string & e){
        std::cerr.flush();
        std::cout.flush();
        (stream << std::hex << memory.PC());
        std::string error_trace = "The ChainVM encountered an exception at address 0x00000000" + stream.str() + ".\nThis occurred with error message: " + e;
        MessageBox( nullptr, TEXT(error_trace.c_str()), TEXT( "Chain VM EXCEPTION" ), MB_OK );
    }

    void displayException(const std::string & e)
    {
        MessageBox( nullptr, TEXT(e.c_str()), TEXT( "Chain VM EXCEPTION" ), MB_OK );
    }

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
        stream.clear();
        stream << "ERR 0x1 Command Load Error [VMError]: Invalid OPCODE '" << opcode << "' located at address '"
               << address << "'.\n" <<
               "Possible causes for OPCODE load error include the following:\n" << "[1] Mixture of .bss variables with commands\n"
                                                                                   "[2] Missing start directive.\n"
                                                                                   "[3] Incorrect start address.\n"
                                                                                   "[4] Tampered code.\n" << "<Please Check Your Code>\n";
        std::string msg = stream.str();
        displayException(msg);
        exit(10);
    }
}

#endif //CHAINC_VMEXCEPTIONS_H
