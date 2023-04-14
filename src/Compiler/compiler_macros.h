//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_COMPILER_MACROS_H
#define CHAIN_COMPILER_MACROS_H
#include "../extern/divefile.h"
#include <iostream>
#include "../extern/memory_unit.h"
#include "../extern/preprocessor.h"

#define __ver__ "0.5.1"

#define func constexpr auto
#define let const auto
#define strvector_p const std::vector<std::string> &
#define strvector std::vector<std::string>

auto const& npos = std::string::npos;
std::string m_line, output_name = "out";
bool isexit = false;
Memory memory;
size_t line = 0;
#define __CURR_YEAR__ 2023

void the_chain_lang()
{
    std::cout << "The Chain Lang\n"
                 "(c) " << __CURR_YEAR__ << " by Rufelle Emmanuel Pactol.\n" <<
                 "version " << __ver__  << "\n" <<
                 "The ChainLang, ASSEMBLY programming for learners.\n"
                 "My ideology for developing ChainLang is to create a usable language\n"
                 "that inherits from ASM, but is learner-oriented.\n"
                 "ASM can be quite difficult to use, but with a centralized, easier version,\n"
                 "and other learner-centric features, hopefully, ChainLang can make ASM a lot less\n"
                 "scary for beginners.\n\n"
                 "Feature set as of the current version:\n"
                 "(1) The Math Instructions\n"
                 "(2) Virtual Machine directives\n"
                 "(3) Iterator support\n"
                 "(4) Label support\n"
                 "(5) Address extraction support\n"
                 "(6) Exception handling support\n"
                 "\nFuture plans:\n"
                 "(1) @trace VM directive for processor tracing\n"
                 "(2) @experimental VM directive for experimental integration\n"
                 "(3) @memset for a more flexible heap memory size.\n"
                 "(4) -b experimental compiler flag to create binary-compressed compilation\n\n"
                 "Visit the official documentation website:\n"
                 "<placeholder>\n";
    colorize::end_state();
            exit(0);
}


using namespace dive;
#endif //CHAIN_COMPILER_MACROS_H
