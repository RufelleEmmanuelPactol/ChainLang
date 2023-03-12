//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_COMPILER_MACROS_H
#define CHAIN_COMPILER_MACROS_H
#include "../extern/divefile.h"
#include <iostream>
#include "../extern/memory_unit.h"
#include "../extern/preprocessor.h"

#define __ver__ "0.3.1"

#define func constexpr auto
#define let const auto
#define strvector_p const std::vector<std::string> &
#define strvector std::vector<std::string>

auto const& npos = std::string::npos;
std::string m_line, output_name = "out";
bool isExit = false;
Memory memory;
size_t line = 0;



using namespace dive;
#endif //CHAIN_COMPILER_MACROS_H
