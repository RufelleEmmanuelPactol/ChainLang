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
#define fnsig int & argtype1, int & argtype2
#define get_op(x) constants.commands()->find(x)->second.opcode
#define get_reg_op(x) constants.registers()->find(x)->second.opcode
#define func [](fnsig)
class CommandLoader{
private:
    map<const string, fn<void(fnsig)>> director;

    // this method returns the register memory
    auto get_register (const std::string & reg)
    {
        try {
            //  this is a dependency when we add new registers
            if (reg == get_reg_op("ac")) return memory.AC();
            else if (reg == get_reg_op("acx")) return memory.ACx();
            else if (reg == get_reg_op("acy")) return memory.ACy();
            else if (reg == get_reg_op("r")) return memory.R();
            else if (reg == get_reg_op("rx")) return memory.Rx();
            else if (reg == get_reg_op("ry")) return memory.Ry();
            else if (reg == get_reg_op("ctr")) return memory.CTR();
            else if (reg == get_reg_op("ctrx")) return memory.CTRx();
            else if (reg == get_reg_op("ctry")) return memory.CTRy();
            else
                VMexcept::InvalidProgramSequence(reg, memory.PC());
        } catch (std::exception & e)
        {
            VMexcept::displayERROR("Internal Virtual Machine Error.");
        }
    }

    void init_commands(){
        director.emplace(
                get_op("add"),
                func{
                    if (argtype1 == sgTKN::NOOP) {
                        int ac = memory.binToDec(memory.AC(), 16);
                        int r = memory.binToDec(memory.R(), 16);
                        memory.set_reg(memory.AC(), 16, memory.to_bitstring(ac+r, 16));
                    }
                    else if (argtype1 == sgTKN::REGISTER16) {
                        if (argtype2 == sgTKN::REGISTER16) {
                            // add logic here to subtract from REG16 to REG16 and store it respectively
                        }
                    }
                }
                );
        director.emplace(
                get_op("end"),
                func {
                    argtype1 = -2;
                    if (preprocessor.isWindowMode()) {
                        std::cout <<
                        colorize(color::yellow, "-----------------------------\n") <<
                        colorize(color::green, "Press return / enter key to terminate process...");
                        getchar();
                    }
                    exit(0);
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