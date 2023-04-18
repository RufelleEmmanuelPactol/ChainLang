#pragma once
#include <functional>
#define fn std::function
#include <vector>
#include <map>
#include <string>
#include "signature.h"
using std::map;
using std::vector;
using std::string;
#include "constants.h"
#define fnsig int argtype1, int argtype2
#define get_op(x) constants.commands()->find(x)->second.opcode
#define func [](fnsig)
class CommandLoader{
private:
    map<const string, fn<void(fnsig)>> director;


    void init_commands(){
        director.emplace(
                get_op("add"),
                func{
                    if (argtype1 == sgTKN::NOOP) {
                        int ac = memory.binToDec(memory.AC(), 16);
                        int r = memory.binToDec(memory.R(), 16);
                        memory.set_reg(memory.AC(), 16, memory.to_bitstring(ac+r, 16));
                    }
                }
                );
    }
public:
    CommandLoader(){
        init_commands();
    }

    auto direct(const string & opcode){
        auto x = director.find(opcode);
    if (x == director.end()) throw std::runtime_error("bad_function_call_chainvm");

        return x->second;
    }




};


CommandLoader commandloader;





#undef fn