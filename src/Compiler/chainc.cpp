//
// Created by Rufelle on 17/01/2023.
//
#include "compiler_macros.h"
#include "../extern/vectorize.h"
#include "argshandler.h"
#include "chaintime.h"
#include "errorhelper.h"



int main (int argc, char ** argv){
    auto timer = new Timer();
    {

        try {
            // scoped namespace
            using namespace chain;
            auto args_vector = vectorize(argc, argv);
            handle(args_vector);

            if (argc == 1) compiler("../src/compiler/hello.ch");

            if (!preprocessor.isAuto() && !preprocessor.isSilent()) {
                std::cout << "<!> Compilation success.\n";
                std::cout << "<!> Compiled under file name '" << output_name + ".exec'\n";
            }
        } catch (std::exception & e) {
            std::cerr << "<!> During loading, invalid file provided.\n";
        }
    }
    if (preprocessor.isSilent()) return 0;
    if (preprocessor.isAuto()){
        auto str = output_name + ".exec";
        int on_exit = system(str.c_str());
        return on_exit;
    } else delete timer;


}


#undef func
#undef let