
//
// Created by Rufelle on 10/02/2023.
//

#ifndef CHAINC_RUNTIME_H
#define CHAINC_RUNTIME_H
#include "string"
#include "../extern/divefile.h"
#include "vm_macros.h"
#include "constants.h"

namespace chain {
    class Runtime {
        dive::FileReader * fr;
        std::shared_ptr<std::vector<std::string>> vector_binaries;

    public:
        explicit Runtime(std::string path_name) {
            try {
                fr = new dive::FileReader(getPath(path_name));
                vector_binaries = fr->readFile();
                load_to_memory();
                run_binaries();
            }  catch (std::ios_base::failure & e){
                std::cout << "<!> Invalid file name with no .bcc extension.\n";
                exit(0);
            }
        }

        ~Runtime() {
            fr->close();
        }

        std::string getPath (std::string & path_name){
            std::string result;
                auto index = path_name.find(".bcc");
                if (index == std::string::npos || index > path_name.size()){
                    throw std::invalid_argument("");
                }
                char curr = path_name[index];
                do  {
                    result.insert(result.begin(), curr);
                    index--;
                    curr = path_name[index];
                } while (!(curr == '\\' || curr == '/'));
                result.append("bcc");return result;
        }
    private:
        auto run_binaries() -> void {
            for (int x = 0; x < memory.MEM_CAP(); x++) {
                auto i = memory.HEAP()[x];
                std::string parsed = i;
                parsed[8] = '\0';
                if (x==500){
                    return;
                }

                // ensures that there is a termination character
                try {
                    parsed.at(8) = '\0';
                } catch (std::exception & e){
                    parsed.push_back('\0');
                }
                printf("%d: %s\n", x, parsed.c_str());
                fflush(stdout);
            }
        }

        void load_to_memory(){
            int indexer = -1;
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
