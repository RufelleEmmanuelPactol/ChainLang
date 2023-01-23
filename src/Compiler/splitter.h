//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_SPLITTER_H
#define CHAINC_SPLITTER_H
#include "constants.h"
namespace chain
{
    strvector stack_split (std::string& line){
        strvector ret;
        std::string stack;
        for (int i=0; i<line.size(); i++){
            char c = line[i];

            // ignores whitespace
            if (c==' '){
                continue;
            }

            // comment
            if (c==';'){
                ret.emplace_back(stack);
                return ret;
            }

            // string splitter
            else if (c=='\"'){

                // checks for stray quote
                if (!stack.empty()){
                    StrayQuoteException(line);
                }
                stack.clear();

                i++;
                while (line[i]!='\"'){
                    if (i>=line.size()){
                        DanglingQuoteException(line);
                    }
                    stack.push_back(line[i]);
                    i++;
                }
                stack.append(" $$VARCHAR$$");
                ret.push_back(stack);
                stack.clear();

                // ensure no dangling comma
                if (i+1 != line.size()){
                    i++;
                }
                continue;
            }

            // numeric tokenizer
            if (c=='0' && stack.empty()){

                // hex
                if (line[i+1] == 'x' || line[i+1] == 'h'){
                    i+=2;
                    while (true){

                        if (line[i]==';'){
                            if (stack.empty()){
                                NullNumericToken(line);
                            } break;
                        }

                        if (!constants.isHex(line[i])){
                            InvalidNumericToken(line, line[i]);
                        }

                        stack.push_back(line[i]);
                        i++;

                        if (i >= line.size() || line[i] == ','){
                            break;
                        }
                    }
                    stack.append(" $$HEX$$");
                    ret.emplace_back(stack);
                    stack.clear();
                    continue;
                }

                // decimal
                if (line[i+1] == 'd'){
                    i+=2;
                    while (true){

                        if (line[i]==';'){
                            if (stack.empty()){
                                NullNumericToken(line);
                            } break;
                        }

                        if (!constants.isDecimal(line[i])){
                            InvalidNumericToken(line, line[i]);
                        }

                        stack.push_back(line[i]);
                        i++;

                        if (i >= line.size() || line[i] == ','){
                            break;
                        }
                    }
                    stack.append(" $$DEC$$");
                    ret.emplace_back(stack);
                    stack.clear();
                    continue;
                }

                // binary
                if (line[i+1] == 'b'){
                    i+=2;
                    while (true){

                        if (line[i]==';'){
                            if (stack.empty()){
                                NullNumericToken(line);
                            } break;
                        }

                        if (!constants.isBinary(line[i])){
                            InvalidNumericToken(line, line[i]);
                        }

                        stack.push_back(line[i]);
                        i++;

                        if (i >= line.size() || line[i] == ','){
                            break;
                        }
                    }
                    stack.append(" $$BIN$$");
                    ret.emplace_back(stack);
                    stack.clear();
                    continue;
                }
            }

            // escape sequence
            if (c==','){
                if (stack.empty()){
                    DanglingCommaException(line);
                }
                ret.push_back(stack);
                stack.clear();
            }

            // label tokenizer
            else if (c==':'){
                if (stack.empty()){
                    StrayLabelDeclaration(line);
                }
                stack.append(" $$LABEL$$");
                ret.push_back(stack);
                stack.clear();
                continue;
            }

            // memory location tokenizer
            else if (c=='[') {
                i++;
                // check if an instance of [] is invoked
                if (line[i]==']'){
                    NullMemoryLocation(line);
                }

                // if stack is not empty
                if (!stack.empty()) {
                    StrayBracketDeclaration(line);
                }

                while (true){
                    stack.push_back(line[i]);
                    i++;
                    if (line[i]==']'){
                        if (i+1 < line.size()){
                            if (line[i+1] == ','){
                                i++;
                            }
                        }
                        break;
                    }
                    if (i>=line.size()){
                        DanglingOpeningBracket(line);
                    }
                }
                stack.append(" $$MEMLOC$$");
                ret.push_back(stack);
                stack.clear();
                continue;
            } else if (c==']'){
                StrayClosingDeclaration(line);
            } else {
                stack.push_back(c);
            }
        }


        if (stack.empty()){
            return ret;
        }
        ret.push_back(stack);
        return ret;
    }
}

#endif //CHAINC_SPLITTER_H
