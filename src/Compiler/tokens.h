//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_TOKENS_H
#define CHAINC_TOKENS_H
#include <string>
#include <vector>

enum Kind {
    invalid, op, not_op
};

enum Datatype{

    // data
    null, str, reference, reg, num, label_ref, mem_reg, mem_label,
    // operators
    label, complex, basic, directive, single_op
};

enum Register{
    not_reg, reg16, reg8, flag
};







enum Operand{
    not_operand, mem, math, reg_param16, reg_param8, mov, alloc, reg_param, no_op, iterator
};
using std::string;

struct token {
    Kind kind;
    Datatype datatype;
    string name;

    //optional
    Operand operand;
    Register reg;
    int numeric;
    size_t operand_count = 0;
    bool has_op = false;
    string opcode;

    token(){
        kind = invalid;
        datatype = null;
        operand = not_operand;
        reg = not_reg;


    }

    token (Kind kind, Datatype datatype, const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        operand = not_operand;
        reg = not_reg;
    }

    // Register REFERENCES

    token (Kind kind, Datatype datatype, Register reg, const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        operand = not_operand;
        this->reg = reg;
    }


    // OPERAND
    token (Kind kind, Datatype datatype, Operand operand, size_t operand_count,  const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        this->operand = operand;
        this->operand_count = operand_count;
        reg = not_reg;
    }

    // OPERAND WITH SIZE
    token (Kind kind, Datatype datatype, Operand operand, size_t operand_count, Register reg, const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        this->operand = operand;
        this->operand_count = operand_count;
        this->reg = reg;
    }

    // OPERAND WITH OPCODE
    token (Kind kind, Datatype datatype, Operand operand, size_t operand_count,  const string& name, const string && opcode){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        this->operand = operand;
        this->operand_count = operand_count;
        this->opcode = opcode;
        has_op = true;
        reg = not_reg;
    }

    // REGISTER
    token (Kind kind, Datatype datatype, Register reg, const string& name, const string && opcode){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        this->reg = reg;
        this->opcode = opcode;
        has_op = true;
        operand = not_operand;
    }

    // NUMERIC
    token (Kind kind, Datatype datatype, int numeric, const string& name){
        this->kind = kind;
        this->datatype = datatype;
        this->name = name;
        this->numeric = numeric;
        reg = not_reg;
        operand = not_operand;
    }

};


struct AST { // pseudo-abstract syntax tree nodes
    token op;
    std::vector<token> operands;
    string labels;
};


#endif //CHAINC_TOKENS_H
