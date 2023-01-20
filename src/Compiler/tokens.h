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

enum Operand{
    inv, mem, math, print, mov, alloc
};
using std::string;

struct token {
    Kind kind;
    Datatype datatype;
    string name;
    Operand operand;

    token(){
        kind = invalid;
        datatype = null;
        operand = inv;

    }

    token (Kind kind, Datatype datatype, const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        operand = inv;
    }

    token (Kind kind, Datatype datatype, Operand operand, const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        this->operand = operand;
    }

};



#endif //CHAINC_TOKENS_H
