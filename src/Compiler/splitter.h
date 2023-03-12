//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_SPLITTER_H
#define CHAINC_SPLITTER_H
#include "constants.h"
#include "exceptions.h"
namespace chain
{

    void preproc_process(const std::string & directive){
        if (directive == "@trace"){
            std::cerr << "<!> Trace mode is on and is enabled upon compilation.\n";
            preprocessor.set_trace(true);
        } else if (directive == "@debug"){
            std::cerr << "<!> Debug mode is on and is enabled upon runtime.\n";
            preprocessor.set_debug(true);
        } else if (directive == "@auto"){
            std::cerr << "<!> Auto run mode is on and will run the output automatically after compilation.\n";
            preprocessor.set_auto(true);
        } else {
            PreprocessorDirectiveError(directive);
        }
    }


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

            // preprocessor directive splitter

            if (c=='@'){
                string preprocessor_dir;
                while (line[i] != ' ' && i < line.size()){
                    preprocessor_dir.push_back(line[i]);
                    i++;
                }
                preproc_process(preprocessor_dir);
                continue;
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
                if (!isalpha(stack[0])){
                    string token;
                    size_t ctr = 0;
                    if (!isdigit(stack[0])){
                        InvalidLabelCharacter(stack[0]);
                    }
                    while ((isdigit(stack[ctr]))&&ctr < stack.size()){
                        token.push_back(stack[ctr]);
                        ctr++;
                    }
                    InvalidLabelCharacter(token);
                }
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
                        i++;
                        while(true){
                            if (i>=line.size()){
                                break;
                            } if (line[i] == ' '){
                                i++;
                                continue;
                            } else if (line[i] == ','){
                                i++;
                                break;
                            } else {
                                InvalidMemLocDeclaration(stack);
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
        if (!isalpha(stack[0])){
            string token;
            size_t ctr = 0;
            if (!isdigit(stack[0])){
                InvalidLabelReferenceCharacter(stack[0]);
            }
            while ((isdigit(stack[ctr]))&&ctr < stack.size()){
                token.push_back(stack[ctr]);
                ctr++;
            }
            InvalidLabelReferenceCharacter(token);
        }
        ret.push_back(stack);
        return ret;
    }
}

#endif //CHAINC_SPLITTER_H
