
//
// Created by Rufelle on 10/02/2023.
//

#ifndef CHAINC_RUNTIME_H
#define CHAINC_RUNTIME_H
#include "VMExceptions.h"
#include "../extern/debug.h"
#include "signature.h"
#include "string"
#include "../extern/divefile.h"
#include "vm_macros.h"
#include "constants.h"
#include "../extern/memory_unit.h"
#include "command_loader.h"
namespace fs = std::filesystem;


namespace chain {
    class Runtime {
        dive::FileReader * fr;
        std::shared_ptr<std::vector<std::string>> vector_binaries;

    public:
        explicit Runtime(std::string path_name) {
            try {
                fr = new dive::FileReader(getPath(path_name));
                preprocessor.load_preprocessor(fr->readLine());
                memory.set_start(fr->readLine());
                if (preprocessor.isDebugging()){
                    std::cout << "<!> Debug/Developer mode is [ON] in the virtual machine.\n";
                    std::cout << "marked start at: " << memory.PC() << '\n';
                }
                if (preprocessor.isTracing()){
                    std::cout << "<!> Trace mode is [ON] in the virtual machine.\n";
                }
                vector_binaries = fr->readFile();
                load_to_memory();
                run_binaries();
            }  catch (FileNotFoundException & e){
                colorize::in_this_state_color_is(color::yellow);
                std::cout << "<!> Cannot find the instance of file '" << getPath(path_name) << "'.\n";
                colorize::end_state();
            colorize::end_state();
            exit(0);
            }
        }

        ~Runtime() {
            fr->close();
        }

        string getFileExtension(const string& fileName)
        {
            if(fileName.find_last_of(".") != string::npos)
                return fileName.substr(fileName.find_last_of(".")+1);
            return "";
        }


        string getPath(const string& filePath)
        {
            using namespace std;
            fs::path pathObj(filePath);
            auto fn = pathObj.filename().string();
            auto x = getFileExtension(fn);

            // checks if the binary read flag is turned on
            if (x == ".binc") constants.BINARY_READ_MODE = true;
            return fn;
        }



    private:
        auto run_binaries() -> void {
            if (preprocessor.isDebugging()) {
            for (int x = 0; x < 50; x++) {
                    auto i = memory.HEAP()[x];
                    std::string parsed = i;
                    parsed[8] = '\0';
                    // ensures that there is a termination character
                    try {
                        parsed.at(8) = '\0';
                    } catch (std::exception &e) {
                        parsed.push_back('\0');
                    }
                    printf("%d: %s\n", x, parsed.c_str());
                    fflush(stdout);
                }
            } binaryREPL();
        }


        auto decouple (const string && signature)
        {
            using namespace signature;
            auto id_1 = signature.substr(0, 4);
            auto id_2 = signature.substr(4, 4);
            using std::pair;
            pair<int, int> res;
            if (id_1 == NOOP) res.first = sgTKN::EMPTY;
            else if (id_1 == REGISTER8) res.first = sgTKN::REGISTER8;
            else if (id_1 == REGISTER16) res.first = sgTKN::REGISTER16;
            else if (id_1 == ADDRESS) res.first = sgTKN::ADDRESS;
            else if (id_1 == POINTER) res.first = sgTKN::POINTER;
            else res.first = -1;
            if (id_2 == NOOP) res.second = sgTKN::EMPTY;
            else if (id_2 == REGISTER8) res.second = sgTKN::REGISTER8;
            else if (id_2 == REGISTER16) res.second = sgTKN::REGISTER16;
            else if (id_2 == ADDRESS) res.second = sgTKN::ADDRESS;
            else if (id_2 == POINTER) res.second = sgTKN::POINTER;
            else res.second = -1;
            return res;
        }

        int push(std::pair<int, int> & couple)
        {
            int ret = 2;
            if (couple.first == sgTKN::REGISTER16) ret++;
            if (couple.first == sgTKN::REGISTER8) ret++;
            if (couple.first == sgTKN::ADDRESS) ret+=2;
            if (couple.first == sgTKN::POINTER) ret+=2;
            if (couple.second == sgTKN::REGISTER16) ret++;
            if (couple.second == sgTKN::REGISTER8) ret++;
            if (couple.second == sgTKN::ADDRESS) ret+=2;
            if (couple.second == sgTKN::POINTER) ret+=2;
            return ret;
        }

        void binaryREPL(){
            string instruction_pointer;
            std::pair<string, string> args;
            while(instruction_pointer!=constants.commands()->find("end")->second.opcode){
                auto command = memory.HEAP()[memory.PC()];
                instruction_pointer = command;
                auto signature = memory.HEAP()[memory.PC()+1];
                auto x = decouple(signature);
                args_handler(args, x, memory.PC()+2);

                /* This checks for any exceptions caused by invalid command
                 * loading due to programmer error.
                 */

                if (x.first == -1 || x.second == -1) VMexcept::InvalidProgramSequence(command, memory.PC());
                auto loaded = commandloader.direct(instruction_pointer);
                loaded(x.first, x.second);
                memory.inc(push(x));
            }
        }


        void args_handler(std::pair<string, string> & args, const std::pair<int, int> & op, int start_ptr)
        {
            string empty = "00000000";
            if (op.first == sgTKN::NOOP) {
                args.first.append(empty);
            }
            else if (op.first == sgTKN::REGISTER8 || op.first == sgTKN::REGISTER16) {
                args.first.append(memory.getBitString(start_ptr, 8));
                start_ptr++;
            } else {
                args.first.append(memory.getBitString(start_ptr, 16));
                start_ptr+=2;
            }

            if (op.second == sgTKN::NOOP) {
                args.second.append(empty);
            }
            else if (op.second == sgTKN::REGISTER8 || op.second == sgTKN::REGISTER16) {
                args.second.append(memory.getBitString(start_ptr, 8));
                start_ptr++;
            } else {
                args.second.append(memory.getBitString(start_ptr, 16));
                start_ptr+=2;
            }

        }

        bool all_bit(const std::string & code_pc){
            for (auto i: code_pc) {
                if (i != '0' && i != '1' && i != 0 && i != 1) {
                   return false;
                }
            } return true;
        }

        void binary_load(){
            for (auto i : *vector_binaries) {
                if (all_bit(i)) continue;
                else {
                    colorize::in_this_state_color_is(color::yellow);
                    std::cout << "<!> This file is corrupted. Unable to proceed with runtime.\n";
                    colorize::end_state();
            exit(3);
                }
            }
        }

        void load_to_memory(){
            int indexer = -1;
            if (constants.BINARY_READ_MODE)
            {
                binary_load();
            }
            for (auto &i: *vector_binaries){
                indexer++;
                if (constants.allBinary(i)){
                    memory.writeAt(indexer, i);
                } else {
                    colorize::in_this_state_color_is(color::yellow);
                    std::cout << "<!> This file is corrupted. Unable to proceed with runtime.\n";
                    colorize::end_state();
            colorize::end_state();
            exit(3);
                }

            }
        }

    };

}

#endif //CHAINC_RUNTIME_H
