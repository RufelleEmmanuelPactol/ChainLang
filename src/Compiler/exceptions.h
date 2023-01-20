//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_EXCEPTIONS_H
#define CHAIN_EXCEPTIONS_H
#include <string>
#define err_line ", found in line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n"
namespace chain
{
    using namespace std;
    void NoPathProvidedException(const string& command){
        cerr << "ERR 021C NoPathProvided [CompilerCall]: No path specified after invoking instance of command [" << command << "].\n";
        exit(021);
    }

    void FileNotFoundException (const string& file){
        cerr << "ERR 022C FileNotFound [CompilerCall]: The path '" << file << "' is not found within the specified directory.\n";
        exit(022);
    }

    void DanglingCommaException (const string& m_line){
        cerr << "ERR121 DanglingCommaDeclaration [Syntax]: Dangling comma found at line " << line << ".\n" << "In line:  " << m_line << endl;
        exit(121);
    }

    void DanglingQuoteException (const string& m_line){
        cerr << "ERR122 DanglingQuoteDeclaration [Syntax]: Dangling double quote found at line " << line << ".\n" << "In line:  " << m_line << endl;
        exit(122);
    }

    void StrayQuoteException (const string& m_line){
        cerr << "ERR123 StrayQuoteDeclaration [Syntax]: Stray double quote found at line " << line << ".\n" << "In line:   " << m_line << endl;
        exit(123);
    }

    void StrayLabelDeclaration(const string& m_line){
        cerr << "ERR124 StrayLabelDeclaration [Syntax]: Stray label declaration found at line " << line << ".\n" << "In line:   " << m_line << endl;
        exit(124);
    }

    void NullMemoryLocation (const string& m_line){
        cerr << "ERR125 NullMemoryLocation [Syntax]: Null memory location specified found at line " << line << ".\nIn line:" << m_line << endl;
        exit(125);
    }

    void StrayBracketDeclaration (const string& m_line){
        cerr << "ERR126 StrayBracketDeclaration [Syntax]: Declaration of stray opening bracket found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(126);
    }

    void DanglingOpeningBracket (const string& m_line){
        cerr << "ERR127 DanglingOpeningBracket [Syntax]: Unresolved opening bracket found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(127);
    }

    void StrayClosingDeclaration (const string& m_line){
        cerr << "ERR127 StrayClosingDeclaration [Syntax]: Declaration of stray closing bracket found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(127);
    }

    void StrayNumericDeclaration (const string& m_line, char type){
        cerr << "ERR128 StrayNumericDeclaration [Syntax]: Declaration of stray numeric token '0" << type << "' t found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(128);
    }

    void InvalidNumericToken (const string& m_line, char invalid){
        cerr << "ERR129 InvalidNumericToken [Syntax]: Invalid numeric token found with unqualified character '" << invalid << "' found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(129);
    }

    void NullNumericToken (const string& m_line){
        cerr << "ERR130 NullNumericToken  [Syntax]: Invalid numeric token found with unqualified NULL numeric declaration found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(130);
    }

    void IllegalTokenFound (const string& m_line, const string && type){
        cerr << "ERR131 IllegalToken [Syntax]: Illegal token '" << type << "' found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(131);
    }

    void RepeatLabelException(const string& label){
        cerr << "ERR201 RepeatLabel [Variables]: Redeclaration of label '" << label << "' found in line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(201);
    }

    void NoSuchLabelException (const string& label){
        cerr << "ERR 202 NoSuchLabel [Variables]: Cannot find instance of label '" << label <<  "' found in line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(202);
    }

    void InvalidToken (const string& token){
        cerr << "ERR 300 InvalidToken [ParseError]: Token '" << token << "' invalid due to unknown instance, found in line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(300);
    }

    void UnexpectedInstanceOfOperator (const string& m_operator){
        cerr << "ERR 301 UnexpectedOperator [Parse Error]: Unexpected instance of operator '" << m_operator << "'" << err_line;
        exit(301);
    }

    void ParameterMatch (const string& m_operator){

    }


}


#endif //CHAIN_EXCEPTIONS_H
