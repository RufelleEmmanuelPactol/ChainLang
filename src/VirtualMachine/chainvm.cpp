//
// Created by Rufelle on 17/01/2023.
//

#include "../extern/vectorize.h"
#include "vm_macros.h"
#include "chaintimeVM.h"
#include "args_handler.h"
#include "../extern/diveColors.h"
#include <vector>

int main (int argc, char ** argv){
    {
        // scope to destruct chain time object
        Timer time;
        auto args = dive::vectorize(argc, argv);
        chain::handle(args);
    }
    if (preprocessor.isSilent()) return 0;
    else {
        colorize::end_state();
        std::cout << colorize(color::bright_blue, "<!> Press any key to finish processes.\n");
        getchar();
    }
}