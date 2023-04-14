//
// Created by Rufelle on 21/01/2023.
//

#ifndef CHAINC_DIVECOLORS_H
#define CHAINC_DIVECOLORS_H
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <string>
namespace color {
    enum colors {
        retain, blue, green, cyan, red, purple, dark_yellow, white, grey, bright_blue, bright_green,
        bright_cyan, bright_red, pink, yellow, bright_white, disable
    };
}

auto __color__handle__ = GetStdHandle(STD_OUTPUT_HANDLE);

struct __color__state__linker__
{
    bool color_retain;
    __color__state__linker__(){
        color_retain = false;
    }
};

namespace __colorize__private__global__
{
    __color__state__linker__ _get_color_state_;
}


class colorize {
private:

public:
    colorize(color::colors text_color, const std::string && output) {
        function_colorize(text_color, output);
    }

    static void color_set_lifetime(color::colors is_retain)
    {
        if (is_retain == color::retain)
            __colorize__private__global__::_get_color_state_.color_retain = true;
    }

    static void in_this_state_color_is (color::colors text_color)
    {
        SetConsoleTextAttribute(__color__handle__, static_cast<int>(text_color));
    }

    static void end_state()
        {
            SetConsoleTextAttribute(__color__handle__, static_cast<int>(color::white));
        }



private:

    void function_colorize(color::colors text_color, const std::string & output){
        SetConsoleTextAttribute(__color__handle__, static_cast<int>(text_color));
        std::cout << output;
        if (!__colorize__private__global__::_get_color_state_.color_retain)
            SetConsoleTextAttribute(__color__handle__, static_cast<int>(color::white));
        std::cout.flush();
        return;
    }
};

auto& operator << (std::ostream & character_out, colorize && ref){
    return character_out;
}





#endif //CHAINC_DIVECOLORS_H
