//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_TOKENIZER_H
#define CHAINC_TOKENIZER_H
#include "tokens.h"
#include "compiler_macros.h"
#include "constants.h"


class Tokenizer{

public:
    static auto stream(strvector_p stringstream){
        std::vector<token> tokenstream;
        for (auto &i : stringstream){

            // map finds
            auto reg = constants.registers()->find(i);
            auto dir = constants.directives()->find(i);
            auto com = constants.commands()->find(i);


            // checks if it exists on the map
            if ( reg != constants.registers()->end()){
                tokenstream.emplace_back(reg->second);
                continue;
            }

            if (dir != constants.directives()->end()){
                tokenstream.emplace_back(dir->second);
                continue;
            }

            if (com != constants.commands()->end()) {
                tokenstream.emplace_back(com->second);
                continue;
            }

            auto m_label = i.find(" $$LABEL$$");
            auto literal =i.find(" $$VARCHAR$$");
            auto mem = i.find(" $$MEMLOC$$");
            auto binary = i.find(" $$BIN$$");
            auto decimal = i.find(" $$DEC$$");
            auto hex = i.find(" $$HEX$$");


            // the 'verify' variables ensure that they are indeed added by the tokenizer and are not hand-coded
            if (m_label!=npos){
                auto verify = (i.substr(i.length()-10, 10)==" $$LABEL$$");
                if (verify){
                    tokenstream.emplace_back(token(not_op, label, i.substr(0, i.length()-10)));
                    continue;
                }
                chain::IllegalTokenFound(m_line, " $$LABEL$$");

            }

            if (literal!=npos){
                auto verify =(i.substr(i.length()-12, 12)==" $$VARCHAR$$");
                if (verify){
                    tokenstream.emplace_back(token(not_op, str, i.substr(0, i.length()-12)));
                    continue;
                }
                chain::IllegalTokenFound(m_line, "$$ VARCHAR");
            }

            if (mem!=npos){
                auto verify = (i.substr(i.length()-11, 11)==" $$MEMLOC$$");
                if (verify){
                    tokenstream.emplace_back(token(not_op, reference, i.substr(0, i.length()-11)));
                    continue;
                } chain::IllegalTokenFound(m_line, "$$MEMLOC$$");
            }

            if (binary!=npos){
                auto verify = (i.substr(i.length()-8, 8)==" $$BIN$$");
                if (verify){
                    tokenstream.emplace_back(token(not_op, num, num2, i.substr(0, i.length()-8)));
                    continue;
                } chain::IllegalTokenFound(m_line, "$$BIN$$");
            }

            if (decimal!=npos){
                auto verify = (i.substr(i.length()-8, 8)==" $$DEC$$");
                if (verify){
                    tokenstream.emplace_back(token(not_op, num, num10, i.substr(0, i.length()-8)));
                    continue;
                } chain::IllegalTokenFound(m_line, "$$DEC$$");
            }

            if (hex!=npos){
                auto verify = (i.substr(i.length()-8, 8)==" $$HEX$$");
                if (verify){
                    tokenstream.emplace_back(token(not_op, num, num16, i.substr(0, i.length()-8)));
                    continue;
                } chain::IllegalTokenFound(m_line, "$$HEX$$");
            }

            tokenstream.emplace_back(token(not_op, label_ref, i));

            // implement syntax here



        }
        return tokenstream;
    }


};

#endif //CHAINC_TOKENIZER_H
