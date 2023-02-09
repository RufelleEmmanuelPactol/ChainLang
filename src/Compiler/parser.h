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
                if (ast.labels.empty()){
                    CannotResolveOperands(operators);
                }
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
                    ParameterDataMismatch(instance_operand.name,  label_ref, reference, op1dt, op1.name);
                }
            }

            // math checker
            if (instance_operand.operand == math){
                if (!operators.empty()){
                    if (op1dt != reg){
                        ParameterDataMismatch(instance_operand.name, reg, op1dt, op1.name);
                    }
                    if (op2dt == reg){
                        if (op2.reg != op1.reg){
                            DataSizeMismatch(op1.name, op1.reg, op2.name, op2.reg);
                        }
                    }
                    if (op2dt != reg && op2dt != label_ref && op2dt != num && op2dt != reference){
                        ParameterDataMismatch(instance_operand.name, reg, label_ref, reference, num, op2dt, op2.name);
                    }
                }
            }

            // reg param8:
            if (instance_operand.operand == reg_param8){
                if (op1.datatype != reg){
                    ParameterDataMismatch(instance_operand.name, reg, op1.datatype, op1.name);
                }
                if (op1.datatype == mem_reg && op1.reg == reg8){
                    ReferenceInvalidData(op1.name);
                }
                if (op1.reg != reg8){
                    RegisterParameterMismatch(instance_operand.name, op1.name,op1.reg, reg8);
                }
            }

            if (instance_operand.operand == reg_param16){
                if (op1.datatype != reg && op1.datatype != mem_reg){
                    ParameterDataMismatch(instance_operand.name, reg, op1.datatype, op1.name);
                }
                if (op1.datatype == mem_reg && op1.reg == reg8){
                    ReferenceInvalidData(op1.name);
                }

                if (op1.reg != reg16){
                    RegisterParameterMismatch(instance_operand.name, op1.name,op1.reg, reg16);
                }
            }

            // alloc type checking
            if (instance_operand.operand == alloc){

                // check if str was allocated using dw
                if (instance_operand.reg == reg16){
                    if (op1dt == str){
                        ParameterDataMismatch(instance_operand.name, num, str, op1.name);
                    }
                }


                // check for generic illegal data types
                if (op1dt != num && op1dt != str){
                    ParameterDataMismatch(instance_operand.name, num, op1dt, op1.name);
                }


            }

            // mov checker

            if (instance_operand.operand == mov){
                if (op1dt == reg && op2dt == reg){
                    if (op1.reg != op2.reg){
                        DataSizeMismatch(op1.name, op1.reg, op2.name, op2.reg);
                    }
                }
                if (op1dt == reg){
                    if (op2dt != reg && op2dt != label_ref && op2dt != reference && op2dt != mem_label && op2dt != mem_reg){
                        ParameterDataMismatch(instance_operand.name, reg, reg, label_ref, reference, op2dt,op2.name);
                    }
                }
                if (op1dt == label_ref || op1dt == reference){
                    if (op2dt != reg){
                        ParameterDataMismatch(instance_operand.name, reg, op2dt, op2.name);
                    }
                }
                // updated label checkers

                for (auto i : operators){
                    if (i.datatype == mem_reg){
                        auto find_instance_of_register = constants.registers()->find(i.name);
                        if (find_instance_of_register!=constants.registers()->end()){
                            if (find_instance_of_register->second.reg != reg16){
                                RegisterParameterMismatch("register address reference", find_instance_of_register->second.name, reg8, reg16);
                            }
                        }
                    }
                }
            }






            return ast;

        }

    };
}
#endif //CHAINC_PARSER_H
