//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_SPLITTER_H
#define CHAINC_SPLITTER_H

namespace chain
{
    strvector stack_split (const std::string& line){
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

            // varchar
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
                continue;
            }

            if (c==','){
                if (stack.empty()){
                    DanglingCommaException(line);
                }
                ret.push_back(stack);
                stack.clear();
            } else if (c==':'){
                if (stack.empty()){
                    StrayLabelDeclaration(line);
                }
                stack.append(" $$LABEL$$");
                ret.push_back(stack);
                stack.clear();
                continue;
            } else if (c=='[') {
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
