//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_TOKENIZER_H
#define CHAINC_TOKENIZER_H
#include "tokens.h"
#include "constants.h"
#define strvector_p const std::vector<std::string> &


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
                chain::IllegalTokenFound(m_line, " $$VARCHAR");
            }

            if (mem!=npos){
                auto verify = (i.substr(i.length()-11, 11)==" $$MEMLOC$$");
                if (verify){
                    auto reduced = i.substr(0, i.length()-11);
                    try {
                        // check if string is a register
                        auto registers = constants.registers()->at(reduced);
                        chain::UnsupportedRegisterAddressExtraction(reduced);
                        tokenstream.emplace_back(token(not_op, mem_reg, registers.reg, reduced));
                        continue;
                    } catch (std::out_of_range &e) {

                        if (!constants.allDecimal(reduced)){
                            tokenstream.emplace_back(token(not_op, mem_label, reduced));
                            continue;
                        }
                        tokenstream.emplace_back(token(not_op, reference, reduced));
                        continue;
                    }
                } chain::IllegalTokenFound(m_line, "$$MEMLOC$$");
            }

            if (binary!=npos){
                auto verify = (i.substr(i.length()-8, 8)==" $$BIN$$");
                auto remID = i.substr(0, i.length()-8);
                int parsed_num = constants.binToDec(remID);
                if (verify){
                    tokenstream.emplace_back(token(not_op, num, parsed_num, remID));
                    continue;
                } chain::IllegalTokenFound(m_line, "$$BIN$$");
            }

            if (decimal!=npos){
                auto verify = (i.substr(i.length()-8, 8)==" $$DEC$$");
                auto remID = i.substr(0, i.length()-8);;
                int parsed_num = constants.strToDec(remID);
                if (verify){
                    tokenstream.emplace_back(token(not_op, num, parsed_num, remID));

                    continue;
                } chain::IllegalTokenFound(m_line, "$$DEC$$");
            }

            if (hex!=npos){
                auto verify = (i.substr(i.length()-8, 8)==" $$HEX$$");
                auto remID = i.substr(0, i.length()-8);
                int parsed_num = constants.hexToDec(remID);
                if (verify){
                    tokenstream.emplace_back(token(not_op, num, parsed_num, remID));
                    continue;
                } chain::IllegalTokenFound(m_line, "$$HEX$$");
            }

            tokenstream.emplace_back(token(not_op, label_ref, i));




        }
        return tokenstream;
    }


};

#endif //CHAINC_TOKENIZER_H
