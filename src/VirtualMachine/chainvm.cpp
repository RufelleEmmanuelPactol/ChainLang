//
// Created by Rufelle on 17/01/2023.
//

#include "../extern/vectorize.h"
#include "vm_macros.h"
#include "chaintimeVM.h"
#include "args_handler.h"
int main (int argc, char ** argv){
    {
        // scope to destruct chain time object
        Timer time;
        auto args = dive::vectorize(argc, argv);
        chain::handle(args);
    }
    std::cout << "<!> Press the enter key to destroy the heap.";
    getchar();
    memory.destroy();
    std::cout << "<!> Press any key to finish processes.";
    getchar();
}