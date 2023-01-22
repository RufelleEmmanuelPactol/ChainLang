//
// Created by Rufelle on 20/01/2023.
//

#ifndef CHAINC_TKNSTRINGIFY_H
#define CHAINC_TKNSTRINGIFY_H

#include "tokens.h"

class Tknstringify{
public:
    static string getDatatypeFromToken (Datatype type_2){
        string type_str;
        if (type_2 == str){
            type_str = "string literal";
        } else if (type_2 == reference){
            type_str = "memory location";
        } else if (type_2 == reg){
            type_str = "register";
        } else if (type_2 == num){
            type_str = "numeric";
        } else if (type_2 == label_ref){
            type_str = "label reference";
        } else {
            type_str = "null";
        }
        return type_str;
    }


    static size_t getDataSizeFromToken (Register reg){
        if (reg == reg16){
            return 16;
        } if (reg == reg8){
            return 8;
        } return 1;
    }
};


#endif //CHAINC_TKNSTRINGIFY_H
