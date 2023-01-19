//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_EXCEPTIONS_H
#define CHAIN_EXCEPTIONS_H

namespace chain
{
    using namespace std;
    void NoPathProvidedException(const string& command){
        cerr << "ERR 021C [CompilerCall]: No path specified after invoking instance of command [" << command << "].\n";
        exit(021);
    }

    void DanglingCommaException (const string& m_line){
        cerr << "ERR121 [Syntax]: Dangling comma found at line " << line << ".\n" << "in line:  " << m_line << endl;
        exit(121);
    }

    void DanglingQuoteException (const string& m_line){
        cerr << "ERR122 [Syntax]: Dangling double quote found at line " << line << ".\n" << "in line:  " << m_line << endl;
        exit(122);
    }

    void StrayQuoteException (const string& m_line){
        cerr << "ERR123 [Syntax]: Stray double quote found at line " << line << ".\n" << "in line:   " << m_line << endl;
        exit(123);
    }

    void StrayLabelDeclaration(const string& m_line){
        cerr << "ERR124 [Syntax]: Stray label declaration found at line " << line << ".\n" << "in line:   " << m_line << endl;
        exit(124);
    }

    void NullMemoryLocation (const string& m_line){
        cerr << "ERR125 [Syntax]: Null memory location specified found at line " << line << ".\nin line:" << m_line << endl;
        exit(125);
    }

    void StrayBracketDeclaration (const string& m_line){
        cerr << "ERR126 [Syntax]: Declaration of stray opening bracket found at line " << line << ".\nin line: " << m_line << endl;
        exit(126);
    }

    void DanglingOpeningBracket (const string& m_line){
        cerr << "ERR127 [Syntax]: Unresolved opening bracket found at line " << line << ".\nin line: " << m_line << endl;
        exit(127);
    }

    void StrayClosingDeclaration (const string& m_line){
        cerr << "ERR127 [Syntax]: Declaration of stray closing bracket found at line " << line << ".\nin line: " << m_line << endl;
        exit(127);
    }

    void RepeatLabelException(const string& label){
        cerr << "ERR201 [Variables]: Redeclaration of label " << label << " found in line " << line << ".\n";
        exit(201);
    }


}


#endif //CHAIN_EXCEPTIONS_H
