//
// Created by Rufelle on 20/01/2023.
//

#ifndef CHAINC_PARSER_H
#define CHAINC_PARSER_H
#include "constants.h"
#include "compiler_macros.h"
#include "tokens.h"

namespace chain {
    class Parser {
    public:
        static auto stream(const std::vector<token> &tokenstream) {
            token instance_operand = token();
            std::vector<token> operators;

            for (auto& i : tokenstream){

                if (i.datatype == label){
                    continue;
                }

                if (i.kind == op){
                    if (instance_operand.operand == not_operand){
                        instance_operand = i;
                        continue;
                    }
                    UnexpectedInstanceOfOperator(i.name);
                }

                if (i.kind == not_op){
                    operators.emplace_back(i);
                }

            }

            // check tree
            if (instance_operand.operand_count != operators.size()){

            }

        }
    };
}
#endif //CHAINC_PARSER_H
