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
        // scoped namespace
        using namespace chain;
       // std::cout << "pass timer\n";
        auto args_vector = vectorize(argc, argv);
       // std::cout << "pass vector\n";
        handle(args_vector);
     //   std::cout << "pass handler\n";

        if (argc == 1 ) compiler("../src/compiler/hello.ch");

        if (!preprocessor.isAuto() && !preprocessor.isSilent()){
        std::cout << "<!> Compilation success.\n";
        std::cout << "<!> Compiled under file name '" << output_name + ".exec'\n";
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