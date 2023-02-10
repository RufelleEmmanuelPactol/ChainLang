//
// Created by Rufelle on 17/01/2023.
//
#include "compiler_macros.h"
#include "../extern/vectorize.h"
#include "argshandler.h"
#include "chaintime.h"
#include "errorhelper.h"


int main (int argc, char ** argv){
    {

        Timer timer;
        // scoped namespace
        using namespace chain;
        auto args_vector = vectorize(argc, argv);
        handle(args_vector);
      if (argc == 1 ) compiler("../src/compiler/hello.ch");
       // memory.display(0, 100);
       // scope = true;
        std::cout << "<!> Compilation success.\n";
    }


}


#undef func
#undef let