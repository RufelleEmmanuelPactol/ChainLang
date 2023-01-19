//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_TOKENS_H
#define CHAINC_TOKENS_H
#include <string>

enum Kind {
    invalid, op, not_op
};

enum Datatype{
    null, varchar, ref, reg8, reg16, reg1,
    // operators
    label, complex, basic, directive
};
using std::string;

struct token {
    Kind kind;
    Datatype datatype;
    string name;

    token(){
        kind = invalid;
        datatype = null;
        name = "";
    }

    token (Kind kind, Datatype datatype, string name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
    }
};



#endif //CHAINC_TOKENS_H
