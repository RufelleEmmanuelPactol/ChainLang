//
// Created by Rufelle on 21/01/2023.
//

#ifndef CHAINC_CHAINTIME_H
#define CHAINC_CHAINTIME_H
#include "chrono"
#include <iostream>

class Timer{

    std::chrono::steady_clock::time_point begin, end;
public:
    Timer(){
        begin = std::chrono::steady_clock::now();
    }

    ~Timer(){
        if (preprocessor.isAuto()) return;
        end = std::chrono::steady_clock::now();
        colorize::in_this_state_color_is(color::bright_blue);
        std::cout << "<!> Compilation finished in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()*0.000000001 << " seconds.\n";
        colorize::end_state();
    }

};
#endif //CHAINC_CHAINTIME_H
