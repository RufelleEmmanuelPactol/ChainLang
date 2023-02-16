//
// Created by Rufelle on 17/01/2023.
//



#ifndef CHAIN_EXCEPTIONS_H
#define CHAIN_EXCEPTIONS_H
#include "tokens.h"


#include "tknstringify.h"
#include "coloredmacros.h"
#define err_line ", found in line " << line << ".\nIn line " << line << ": '" << m_line << "'" << endl
#define err_line2 ", found in line " << line << ".\nIn line " << line << ": '" << m_line << "'" << endl

//helper function
namespace chainhelp{
    void resolveOperands(const std::vector<token>tokens);
    void findOperands(const std::vector<token> & tokenstream);
}

namespace chain {
    using namespace std;

    void NoPathProvidedException(const string &command) {
        cerr << "ERR 021C NoPathProvided [CompilerCall]: No path specified after invoking instance of command ["
             << command << "].\n";
        exit(021);
    }

    void InvalidCommandSequence(strvector_p commands) {
        cerr << "ERR 022C InvalidCommandSequence [CompilerCall]: Invalid seqeuence of commands '";
        bool first = true;
        for (auto &i: commands) {
            if (first) {
                first = false;
                continue;
            }
            cerr << i << " ";
        }
        cerr << "'\n";
        exit(022);
    }

    void FileNotFoundException(const string &file) {
        cerr << "ERR 022C FileNotFound [CompilerCall]: The path '" << file
             << "' is not found within the specified directory.\n";
        exit(022);
    }

    void DanglingCommaException(const string &m_line) {
        cerr << "ERR121 DanglingCommaDeclaration [Syntax]: Dangling comma found at line " << line << ".\n"
             << "In line:  " << m_line << endl;
        exit(121);
    }

    void DanglingQuoteException(const string &m_line) {
        cerr << "ERR122 DanglingQuoteDeclaration [Syntax]: Dangling double quote found at line " << line << ".\n"
             << "In line:  " << m_line << endl;
        exit(122);
    }

    void StrayQuoteException(const string &m_line) {
        cerr << "ERR123 StrayQuoteDeclaration [Syntax]: Stray double quote found at line " << line << ".\n"
             << "In line:   " << m_line << endl;
        exit(123);
    }

    void StrayLabelDeclaration(const string &m_line) {
        cerr << "ERR124 StrayLabelDeclaration [Syntax]: Stray label declaration found at line " << line << ".\n"
             << "In line:   " << m_line << endl;
        exit(124);
    }

    void NullMemoryLocation(const string &m_line) {
        cerr << "ERR125 NullMemoryLocation [Syntax]: Null memory location specified found at line " << line
             << ".\nIn line:" << m_line << endl;
        exit(125);
    }

    void StrayBracketDeclaration(const string &m_line) {
        cerr << "ERR126 StrayBracketDeclaration [Syntax]: Declaration of stray opening bracket found at line " << line
             << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(126);
    }

    void DanglingOpeningBracket(const string &m_line) {
        cerr << "ERR127 DanglingOpeningBracket [Syntax]: Unresolved opening bracket found at line " << line
             << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(127);
    }

    void StrayClosingDeclaration(const string &m_line) {
        cerr << "ERR127 StrayClosingDeclaration [Syntax]: Declaration of stray closing bracket found at line " << line
             << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(127);
    }

    void StrayNumericDeclaration(const string &m_line, char type) {
        cerr << "ERR128 StrayNumericDeclaration [Syntax]: Declaration of stray numeric token '0" << type
             << "' t found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(128);
    }

    void InvalidNumericToken(const string &m_line, char invalid) {
        cerr << "ERR129 InvalidNumericToken [Syntax]: Invalid numeric token found with unqualified character '"
             << invalid << "' found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(129);
    }

    void NullNumericToken(const string &m_line) {
        cerr
                << "ERR130 NullNumericToken  [Syntax]: Invalid numeric token found with unqualified NULL numeric declaration found at line "
                << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(130);
    }

    void IllegalTokenFound(const string &m_line, const string &&type) {
        cerr << "ERR131 IllegalToken [Syntax]: Illegal token '" << type << "' found at line " << line << ".\nIn line "
             << line << ": '" << m_line << "'.\n";
        exit(131);
    }

    void RepeatLabelException(const string &label) {
        cerr << "ERR201 RepeatLabel [Variables]: Redeclaration of label '" << label << "' found in line " << line
             << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(201);
    }

    void NoSuchLabelException(const string &label) {
        cerr << "ERR 202 NoSuchLabel [Variables]: Cannot find instance of label '" << label << "' found in line "
             << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        exit(202);
    }

    void InvalidToken(const string &token) {
        cerr << "ERR 300 InvalidToken [ParseError]: Token '" << token
             << "' invalid due to unknown instance, found in line " << line << ".\nIn line " << line << ": '" << m_line
             << "'.\n";
        exit(300);
    }

    void UnexpectedInstanceOfOperator(const string &m_operator) {
        cerr << "ERR 301 UnexpectedOperator [Parse Error]: Unexpected instance of operator '" << m_operator << "'"
             << err_line;
        exit(301);
    }

    void ParameterMismatch(const token &m_operator, size_t count) {
        cerr << "ERR 302 ParameterMismatch [Parse Error]: Cannot find parameter match of operator '" << m_operator.name
             << "', which needs " << m_operator.operand_count << " operator(s) to work, where " << count
             << " operator(s) was / were provided" << err_line;
        exit(302);
    }

    void
    ParameterDataMismatch(const string &m_operator, Datatype type_1, Datatype type_2, Datatype type_3, Datatype type_4,
                          Datatype type_5, Datatype _other, const string &opname) {
        string type1 = Tknstringify::getDatatypeFromToken(type_1);
        string type2 = Tknstringify::getDatatypeFromToken(type_2);
        string type3 = Tknstringify::getDatatypeFromToken(type_3);
        string type4 = Tknstringify::getDatatypeFromToken(type_4);
        string type5 = Tknstringify::getDatatypeFromToken(type_5);
        string other = Tknstringify::getDatatypeFromToken(_other);
        cerr << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << ", " << type2 << ", " << type3 << ", " << type4
             << ", " << type5 << "' to work, where '" << other << "' was provided" << err_line;
        cerr << ">>> Consider changing: '" << opname << "' to matching data type which can be '" << type1 << "', '"
             << type2 << "', '" << type3 << "', '" << type4 << "', or '" << type5 << "'." << endl;
        exit(303);
    }

    void
    ParameterDataMismatch(const string &m_operator, Datatype type_1, Datatype type_2, Datatype type_3, Datatype type_4,
                          Datatype _other, const string &opname) {
        string type1 = Tknstringify::getDatatypeFromToken(type_1);
        string type2 = Tknstringify::getDatatypeFromToken(type_2);
        string type3 = Tknstringify::getDatatypeFromToken(type_3);
        string type4 = Tknstringify::getDatatypeFromToken(type_4);
        string other = Tknstringify::getDatatypeFromToken(_other);
        cerr << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << ", " << type2 << ", " << type3 << ", " << type4
             << "' to work, where '" << other << "' was provided" << err_line;
        cerr << ">>> Consider changing: '" << opname << "' to matching data type which can be '" << type1 << "', '"
             << type2 << "', '" << type3 << "', or '" << type4 << "'." << endl;
        exit(303);
    }

    void
    ParameterDataMismatch(const string &m_operator, Datatype type_1, Datatype type_2, Datatype type_3, Datatype _other,
                          const string &opname) {
        string type1 = Tknstringify::getDatatypeFromToken(type_1);
        string type2 = Tknstringify::getDatatypeFromToken(type_2);
        string type3 = Tknstringify::getDatatypeFromToken(type_3);
        string other = Tknstringify::getDatatypeFromToken(_other);
        cerr << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << ", " << type2 << ", " << type3
             << "' to work, where '" << other << "' was provided" << err_line;
        cerr << ">>> Consider changing: '" << opname << "' to matching data type which can be '" << type1 << "', '"
             << type2 << "', or '" << type3 << "'." << endl;
        exit(303);
    }

    void ParameterDataMismatch(const string &m_operator, Datatype type_1, Datatype type_2, Datatype _other,
                               const string &opname) {
        string type1 = Tknstringify::getDatatypeFromToken(type_1);
        string type2 = Tknstringify::getDatatypeFromToken(type_2);
        string other = Tknstringify::getDatatypeFromToken(_other);
        cerr << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << ", " << type2 << "' to work, where '" << other
             << "' was provided" << err_line;
        cerr << ">>> Consider changing: '" << opname << "' to matching data type which can be '" << type1 << "', or '"
             << type2 << "'." << endl;
        exit(303);
    }

    void ParameterDataMismatch(const string &m_operator, Datatype type_1, Datatype _other, const string &opname) {
        string type1 = Tknstringify::getDatatypeFromToken(type_1);
        string other = Tknstringify::getDatatypeFromToken(_other);
        cerr << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << "' to work, where '" << other << "' was provided"
             << err_line;
        if (type_1 == num && _other == str && m_operator == "dw") {
            cerr << ">>> Consider changing: '" << m_operator
                 << "' to appropriate alloc directive for strings, which is 'db'." << endl;
            exit(303);
        }
        cerr << ">>> Consider changing: '" << opname << "' to matching data type which is '" << type1 << "'." << endl;
        exit(303);
    }

    void CannotResolveOperands(const std::vector<token> tokens) {
        std::cerr
                << "ERR 304 IllegalOperandInstance [Parse Error]: Cannot resolve operand token stream, unable to operate on tokens ";
        for (auto &i: tokens) {
            std::cerr << "'" << i.name << "' ";
        }
        std::cerr << "because valid operators were not found. To resolve, check for missing operators or missing commas"
                  << err_line;
        chainhelp::resolveOperands(tokens);
        chainhelp::findOperands(tokens);
        exit(304);
    }

    void InvalidLabelTokenDeclaration(const string &label_name, const vector<token> &line_tokens) {
        std::cerr << "ERR 305 IllegalLabelDeclaration [Parse Error]: Cannot resolve token declaration of label '"
                  << label_name
                  << "'. Labels must be either be declared alone or must be placed in the beginning of a line. Postfix labels are not allowed"
                  << err_line;
        std::cerr << ">>> Consider the following syntax instead: '" << label_name << ":";
        string output;
        for (auto &j: line_tokens) {
            if (j.datatype != label) {
                output.append(" " + j.name + ",");
            }
        }
        output[output.size() - 1] = '\'';
        output.append(".");
        cerr << output;
        exit(305);
    }

    void InvalidMemLocDeclaration(const string &str) {
        cerr << "ERR 306 InvalidMemoryLocationDeclaration [Parse Error]: Cannot resolve the declaration of token '["
             << str << "]'. Check for a missing comma" << err_line;
        cerr << ">>> Consider changing token: '[" << str << "]' to token '[" << str << "],'";
        exit(306);
    }

    void InvalidLabelCharacter(const char c) {
        cerr << "ERR 307 InvalidLabelCharacter [Parse Error]: Cannot parse label with starting character '" << c
             << "'. Labels must start with a numeric character" << err_line;
        exit(307);
    }

    void InvalidLabelCharacter(const string &c) {
        cerr << "ERR 307 InvalidLabelCharacter [Parse Error]: Cannot parse label with numeric tokens '" << c
             << "'. Labels must start with a numeric character" << err_line;
        cerr << ">>> Consider, did you perhaps mean to declare a numeric token? Consider changing '" << c << "' to '0d"
             << c << "'.\n";
        exit(307);
    }

    void InvalidLabelReferenceCharacter(const char c) {
        cerr << "ERR 308 InvalidLabelCharacter [Parse Error]: Cannot parse label reference with starting character '"
             << c << "'. Labels must start with an alphanumeric character" << err_line;
        exit(308);
    }

    void InvalidLabelReferenceCharacter(const string &c) {
        cerr << "ERR 307 InvalidLabelCharacter [Parse Error]: Cannot parse label reference with numeric tokens '" << c
             << "'. Labels must start with an alphanumeric character" << err_line;
        cerr << ">>> Consider, did you perhaps mean to declare a numeric token? Consider changing '" << c << "' to '0d"
             << c << "'.\n";
        cerr << ">>> Consider, did you perhaps mean to reference a memory location? Consider changing '" << c
             << "' to '[" << c << "]'.\n";
        exit(308);
    }

    void DataSizeMismatch(const string &reg_1, Register r1, const string &reg_2, Register r2) {
        auto size1 = Tknstringify::getDataSizeFromToken(r1);
        auto size2 = Tknstringify::getDataSizeFromToken(r2);
        cerr
                << "ERR 400 DataSizeMismatch [Data Error]: Cannot perform operations on mismatched registers where register '"
                << reg_1 << "' has size " << size1 << " bits while register '" << reg_2 << "' has size " << size2
                << " bits" err_line2;
        exit(400);
    }

    void RegisterParameterMismatch(const string &instruction, const string &register_name, Register provided,
                                   Register required) {
        auto provided_ = Tknstringify::getDataSizeFromToken(provided);
        auto required_ = Tknstringify::getDataSizeFromToken(required);
        cerr << "ERR 401 RegisterSizeMismatch [Data Error]: Cannot perform operations on mismatched registers where '"
             << register_name << "' has register size " << provided_ << " bits while instruction '" << instruction
             << "' needs " << required_ << " bits" << err_line2;
        exit(401);
    }

    void ReferenceInvalidData(const string &mem_label) {
        cerr << "ERR 401 ReferenceInvalidSize [Data Error]: Cannot take the values of register '" << mem_label
             << "' as an address, as the register '" << mem_label << "' is 8-bit, and addresses are 16-bit values"
             << err_line;
        exit(401);
    }


    void UnsupportedRegisterAddressExtraction(const string &reg){
    cerr << "ERR 600 Unsupported Feature [Feature Error]: Cannot extract the addresses of register '" << reg << "', as register address extraction is still unsupported in this build of the chainc: " << __ver__ << err_line;
    exit(600);
    }


}

#include "errorhelper.h"

#endif //CHAIN_EXCEPTIONS_H
