//
// Created by Rufelle on 20/01/2023.
//

#ifndef CHAINC_PARSER_H
#define CHAINC_PARSER_H
#include "constants.h"
#include "compiler_macros.h"
#include "tokens.h"
#define op1dt operators[0].datatype
#define op2dt operators[1].datatype
#define op1 operators[0]
#define op2 operators[1]



namespace chain {
    class Parser {
    public:
        static auto stream(const std::vector<token> &tokenstream) {
            AST ast;
            token &instance_operand = ast.op;
            instance_operand.name = "badtoken";
            std::vector<token>& operators = ast.operands;

            for (auto &i: tokenstream) {

                if (i.datatype == label) {
                    if (instance_operand.name != "badtoken" || !operators.empty()){
                        InvalidLabelTokenDeclaration(i.name, tokenstream);
                    }
                    ast.labels = i.name;
                    continue;
                }

                if (i.kind == op) {
                    if (instance_operand.operand == not_operand) {
                        instance_operand = i;
                        continue;
                    }
                    UnexpectedInstanceOfOperator(i.name);
                }

                if (i.kind == not_op) {
                    operators.emplace_back(i);
                    continue;
                }

            }

            // check if operand is null

            if (instance_operand.name == "badtoken" && !operators.empty()){
                CannotResolveOperands(operators);
            }

            // check operand match
            if (instance_operand.operand_count != operators.size() && instance_operand.name != "badtoken") {
                if (!(instance_operand.datatype == complex && operators.size() != 1)) {
                    ParameterMismatch(instance_operand, operators.size());
                }
            }

            // check param data type match
            if (instance_operand.operand == mem){
                if (op1dt != reference && op1dt != label_ref ){
                    ParameterDataMismatch(instance_operand.name, label, label_ref, op1dt);
                }
            }

            if (instance_operand.operand == math){
                if (!operators.empty()){
                    if (op1dt != reg){
                        ParameterDataMismatch(instance_operand.name, reg, op1dt);
                    }
                    if (op2dt == reg){
                        if (op2.reg != op1.reg){
                            DataSizeMismatch(op1.name, op1.reg, op2.name, op2.reg);
                        }
                    }
                }
            }

            if (instance_operand.operand == reg_param8){

            }



            return ast;

        }

    };
}
#endif //CHAINC_PARSER_H
