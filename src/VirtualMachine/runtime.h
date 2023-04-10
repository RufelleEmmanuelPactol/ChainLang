
//
// Created by Rufelle on 10/02/2023.
//

#ifndef CHAINC_RUNTIME_H
#define CHAINC_RUNTIME_H
#include "signature.h"
#include "string"
#include "../extern/divefile.h"
#include "vm_macros.h"
#include "constants.h"
#include "../extern/memory_unit.h"

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
                std::cout << "<!> Cannot find the instance of file '" << getPath(path_name) << "'.\n";
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
            pair<string, string> res;
            if (id_1 == EMPTY) res.first = sgTKN::EMPTY;
            else if (id_1 == REGISTER8) res.first = sgTKN::REGISTER8;
            else if (id_1 == REGISTER16) res.first = sgTKN::REGISTER16;
            else if (id_1 == ADDRESS) res.first = sgTKN::ADDRESS;
            else if (id_1 == POINTER) res.first = sgTKN::POINTER;
            else InternalCompilerError();
            if (id_2 == EMPTY) res.second = sgTKN::EMPTY;
            else if (id_2 == REGISTER8) res.second = sgTKN::REGISTER8;
            else if (id_2 == REGISTER16) res.second = sgTKN::REGISTER16;
            else if (id_2 == ADDRESS) res.second = sgTKN::ADDRESS;
            else if (id_2 == POINTER) res.second = sgTKN::POINTER;
            else InternalCompilerError();
            return res;
        }

        void binaryREPL(){
            printf("Entering binary REPL\n");
            while(true){
                auto command = memory.HEAP()[memory.PC()];
                auto signature = memory.HEAP()[memory.PC()+1];
                auto op1 = memory.HEAP()[memory.PC()+2];
                decouple(signature);
                printf("Decoupling Done!\n");
                exit(0);
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
                    std::cerr << "<!> This file is corrupted. Unable to proceed with runtime.\n";
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
                    std::cerr << "<!> This file is corrupted. Unable to proceed with runtime.\n";
                    exit(3);
                }

            }
        }

    };

}

#endif //CHAINC_RUNTIME_H
