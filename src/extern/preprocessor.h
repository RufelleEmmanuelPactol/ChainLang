//
// Created by Rufelle on 10/03/2023.
//

#ifndef CHAINC_PREPROCESSOR_H
#define CHAINC_PREPROCESSOR_H
#include <string>
#include "divefile.h"

struct Preprocessor{
    char word[18];

    Preprocessor(){
        for (int i=0; i<16; i++){
            word[i] = '0';
        } word[16] = '\n';
        word[17] = '\0';
    }

    std::string get_flags(){
        std::string s = word;
        return s;
    }

    void load_preprocessor(const std::string & load){
        for (int i=0; i<16; i++){
            word[i] = load[i];
        }
    }

    void set_trace(bool t){
        if (t) word[0] = '1';
        else word[0] = '0';
    }

    void set_debug(bool t){
        if (t) word[1] = '1';
        else word[1] = '0';
    }

    bool isTracing(){
        if (word[0]=='1') return true;
        return false;
    }

    bool isDebugging(){
        if (word[1]=='1') return true;
        return false;
    }

    void set_auto(bool t){
        if (t) word[2] = '1';
        else word[2] = '0';
    }

    bool isAuto(){
        if (word[2]=='1') return true;
        return false;
    }

    void set_silent(bool t){
        if (t) word[3] = '1';
        else word[3] = '0';
    }

    bool isSilent(){
        if (word[3]=='1') return true;
        return false;
    }

    void set_window_mode(bool t){
        if (t) word[4] = '1';
        else word[4] = '0';
    }

    bool isWindowMode()
    {
        if (word[4]=='1') return true;
        return false;
    }




};
#endif //CHAINC_PREPROCESSOR_H
