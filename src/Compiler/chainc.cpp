//
// Created by Rufelle on 17/01/2023.
//
#include "compiler_macros.h"
#include "../extern/vectorize.h"
#include "argshandler.h"
#include "compiler.h"





int main (int argc, char ** argv){
    {
        // scoped namespace
        using namespace chain;
        auto args_vector = vectorize(argc, argv);
        handle(args_vector);
        compiler("debug");
    }


}

#undef func
#undef let