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
    if (preprocessor.isAuto()) return 0;
    else {
        std::cout << "<!> Press any key to finish processes.";
        getchar();
    }
}