//
// Created by Rufelle on 10/02/2023.
//

#ifndef CHAINC_ARGS_HANDLER_H
#define CHAINC_ARGS_HANDLER_H
#include <vector>
#include <string>
#include "runtime.h"
#include <sstream>
namespace chain {
    using namespace color;
    void HideConsole()
    {
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    }

    void handle(const std::vector<std::string> &args) {
        try {
            Runtime(args.at(1));
        } catch (std::invalid_argument & e){
            std::cout << colorize(color::yellow, "<!> The Chain Virtual Machine cannot read non '.exec' and '.binc' files. Please load the appropriate file.\n");
            colorize::end_state();
            exit(3);
        } catch (std::ios_base::failure & e){
            colorize::in_this_state_color_is(color::yellow);
            std::cout << colorize(color::yellow, "<!> Instance of file '" + args.at(1) + "' not found.\n");
            colorize::end_state();
        } catch (std::exception & e){
            std::cout << colorize(color::yellow, "<!> The Chain Virtual Machine (CVM) encountered an exception at runtime.\n"
            "<!> ErrorTrace: ");
            auto x = e.what();
            std::cout << colorize(color::red, x) << std::endl;
            cerr.flush();
            VMexcept::displayERROR(e.what());
            exit(3);
        }
    }




    
}


#endif //CHAINC_ARGS_HANDLER_H
