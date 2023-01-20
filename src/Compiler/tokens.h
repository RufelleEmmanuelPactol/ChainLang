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

    // data
    null, str, ref, reg, num, label_ref,
    // operators
    label, complex, basic, directive
};

enum Register{
    not_reg, reg16, reg8, flag
};

enum Numeric{
    not_numeric, num2, num10, num16
};



enum Operand{
    not_operand, mem, math, print, mov, alloc
};
using std::string;

struct token {
    Kind kind;
    Datatype datatype;
    string name;

    //optional
    Operand operand;
    Register reg;
    Numeric numeric;
    size_t operand_count = -1;


    token(){
        kind = invalid;
        datatype = null;
        operand = not_operand;
        reg = not_reg;
        numeric = not_numeric;

    }

    token (Kind kind, Datatype datatype, const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        operand = not_operand;
        reg = not_reg;
        numeric = not_numeric;
    }

    // OPERAND
    token (Kind kind, Datatype datatype, Operand operand, size_t operand_count,  const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        this->operand = operand;
        this->operand_count = operand_count;
        reg = not_reg;
        numeric = not_numeric;
    }

    // REGISTER
    token (Kind kind, Datatype datatype, Register reg, const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        this->reg = reg;
        operand = not_operand;
        numeric = not_numeric;
    }

    // NUMERIC
    token (Kind kind, Datatype datatype, Numeric numeric, const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        this->numeric = numeric;
        reg = not_reg;
        operand = not_operand;

    }

};



#endif //CHAINC_TOKENS_H
