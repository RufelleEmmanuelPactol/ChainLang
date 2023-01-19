cmake_minimum_required(VERSION 3.23)
project(chainc)

set(CMAKE_CXX_STANDARD 14)

add_executable(chainc src/Compiler/chainc.cpp)
add_executable(chainvm src/VirtualMachine/chainvm.cpp)

