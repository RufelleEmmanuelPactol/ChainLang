cmake_minimum_required(VERSION 3.23)
project(chainc)

set(CMAKE_CXX_STANDARD 23)


add_executable(chainvm src/VirtualMachine/chainvm.cpp src/VirtualMachine/command_loader.h)
add_executable(chainc src/Compiler/chainc.cpp)




