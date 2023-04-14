//
// Created by Rufelle on 10/02/2023.
//


//
// Created by Rufelle on 21/01/2023.
//

#ifndef CHAINC_CHAINTIME_H
#define CHAINC_CHAINTIME_H
#include "chrono"
#include <iostream>
#include "../extern/diveColors.h"

class Timer{

    std::chrono::steady_clock::time_point begin, end;
public:
    Timer(){
        begin = std::chrono::steady_clock::now();
    }

    ~Timer(){
        end = std::chrono::steady_clock::now();
        if (!preprocessor.isSilent()) {
            colorize::color_set_lifetime(color::retain);
            std::cout << colorize(color::bright_blue, "<!> Runtime finished in: ")
                      << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 0.000000001
                      << " seconds.\n";
            colorize::color_set_lifetime(color::disable);
        }
    }

};

#endif //CHAINC_CHAINTIMEVM_H
