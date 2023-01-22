//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_COMPILER_MACROS_H
#define CHAIN_COMPILER_MACROS_H
#include "../extern/divefile.h"
#include <iostream>
#include "memory_unit.h"

#define __ver__ "0.0.1"

#define func constexpr auto
#define let const auto
#define strvector_p const std::vector<std::string> &
#define strvector std::vector<std::string>

auto const& npos = std::string::npos;
std::string m_line, output_name = "out";


Memory memory = Memory();
size_t line = 0;



using namespace dive;
#endif //CHAIN_COMPILER_MACROS_H
