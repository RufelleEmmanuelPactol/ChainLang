//
// Created by Rufelle on 17/01/2023.
//



#ifndef CHAIN_EXCEPTIONS_H
#define CHAIN_EXCEPTIONS_H
#include "tokens.h"
#include "tknstringify.h"
#include "../extern/diveColors.h"
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
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 021C NoPathProvided [CompilerCall]: No path specified after invoking instance of command ["
             << command << "].\n";
        colorize::end_state();
            exit(021);
    }

    void InvalidCommandSequence(strvector_p commands) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 022C InvalidCommandSequence [CompilerCall]: Invalid seqeuence of commands '";
        bool first = true;
        for (auto &i: commands) {
            if (first) {
                first = false;
                continue;
            }
            colorize::in_this_state_color_is(color::yellow);
        cout << i << " ";
        }
        colorize::in_this_state_color_is(color::yellow);
        cout << "'\n";
        colorize::end_state();
            exit(022);
    }

    void FileNotFoundException(const string &file) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 022C FileNotFound [CompilerCall]: The path '" << file
             << "' is not found within the specified directory.\n";
        colorize::end_state();
            exit(022);
    }

    void InvalidFileExtension (const string & file, const string & extension) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 023C InvalidFileExtension [CompilerCall]: The file '" << file
        << "' with extension '" << extension << "' is not valid.\n Please use the appropriate .ch files for compilation.\n";
        colorize::end_state();
            exit(023);
    }





    void DanglingCommaException(const string &m_line) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR121 DanglingCommaDeclaration [Syntax]: Dangling comma found at line " << line << ".\n"
             << "In line:  " << m_line << endl;
        colorize::end_state();
            exit(121);
    }

    void DanglingQuoteException(const string &m_line) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR122 DanglingQuoteDeclaration [Syntax]: Dangling double quote found at line " << line << ".\n"
             << "In line:  " << m_line << endl;
        colorize::end_state();
            exit(122);
    }

    void StrayQuoteException(const string &m_line) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR123 StrayQuoteDeclaration [Syntax]: Stray double quote found at line " << line << ".\n"
             << "In line:   " << m_line << endl;
        colorize::end_state();
            exit(123);
    }

    void StrayLabelDeclaration(const string &m_line) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR124 StrayLabelDeclaration [Syntax]: Stray label declaration found at line " << line << ".\n"
             << "In line:   " << m_line << endl;
        colorize::end_state();
            exit(124);
    }

    void NullMemoryLocation(const string &m_line) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR125 NullMemoryLocation [Syntax]: Null memory location specified found at line " << line
             << ".\nIn line:" << m_line << endl;
        colorize::end_state();
            exit(125);
    }

    void StrayBracketDeclaration(const string &m_line) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR126 StrayBracketDeclaration [Syntax]: Declaration of stray opening bracket found at line " << line
             << ".\nIn line " << line << ": '" << m_line << "'.\n";
        colorize::end_state();
            exit(126);
    }

    void DanglingOpeningBracket(const string &m_line) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR127 DanglingOpeningBracket [Syntax]: Unresolved opening bracket found at line " << line
             << ".\nIn line " << line << ": '" << m_line << "'.\n";
        colorize::end_state();
            exit(127);
    }

    void StrayClosingDeclaration(const string &m_line) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR127 StrayClosingDeclaration [Syntax]: Declaration of stray closing bracket found at line " << line
             << ".\nIn line " << line << ": '" << m_line << "'.\n";
        colorize::end_state();
            exit(127);
    }

    void StrayNumericDeclaration(const string &m_line, char type) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR128 StrayNumericDeclaration [Syntax]: Declaration of stray numeric token '0" << type
             << "' t found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        colorize::end_state();
            exit(128);
    }

    void InvalidNumericToken(const string &m_line, char invalid) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR129 InvalidNumericToken [Syntax]: Invalid numeric token found with unqualified character '"
             << invalid << "' found at line " << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        colorize::end_state();
            exit(129);
    }

    void NullNumericToken(const string &m_line) {
        colorize::in_this_state_color_is(color::yellow);
                cout << "ERR130 NullNumericToken  [Syntax]: Invalid numeric token found with unqualified NULL numeric declaration found at line "
                << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        colorize::end_state();
            exit(130);
    }

    void IllegalTokenFound(const string &m_line, const string &&type) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR131 IllegalToken [Syntax]: Illegal token '" << type << "' found at line " << line << ".\nIn line "
             << line << ": '" << m_line << "'.\n";
        colorize::end_state();
            exit(131);
    }

    void NoEndDetectedToken (const std::string & file_name){
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR132 [NoEndToken]: In module/path '" << file_name << "' no end directive found. Please refactor your code to include the end directive.";
        colorize::end_state();
            exit(132);
    }

    void RepeatLabelException(const string &label) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR201 RepeatLabel [Variables]: Redeclaration of label '" << label << "' found in line " << line
             << ".\nIn line " << line << ": '" << m_line << "'.\n";
        colorize::end_state();
            exit(201);
    }

    void NoSuchLabelException(const string &label) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 202 NoSuchLabel [Variables]: Cannot find instance of label '" << label << "' found in line "
             << line << ".\nIn line " << line << ": '" << m_line << "'.\n";
        colorize::end_state();
            exit(202);
    }

    void InvalidToken(const string &token) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 300 InvalidToken [ParseError]: Token '" << token
             << "' invalid due to unknown instance, found in line " << line << ".\nIn line " << line << ": '" << m_line
             << "'.\n";
        colorize::end_state();
            exit(300);
    }

    void UnexpectedInstanceOfOperator(const string &m_operator) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 301 UnexpectedOperator [Parse Error]: Unexpected instance of operator '" << m_operator << "'"
             << err_line;
        colorize::end_state();
            exit(301);
    }

    void ParameterMismatch(const token &m_operator, size_t count) {
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 302 ParameterMismatch [Parse Error]: Cannot find parameter match of operator '" << m_operator.name
             << "', which needs " << m_operator.operand_count << " operator(s) to work, where " << count
             << " operator(s) was / were provided" << err_line;
        colorize::end_state();
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
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << ", " << type2 << ", " << type3 << ", " << type4
             << ", " << type5 << "' to work, where '" << other << "' was provided" << err_line;
        colorize::in_this_state_color_is(color::yellow);
        cout << ">>> Consider changing: '" << opname << "' to matching data type which can be '" << type1 << "', '"
             << type2 << "', '" << type3 << "', '" << type4 << "', or '" << type5 << "'." << endl;
        colorize::end_state();
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
        colorize::in_this_state_color_is(color::yellow);
        cout << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << ", " << type2 << ", " << type3 << ", " << type4
             << "' to work, where '" << other << "' was provided" << err_line;
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider changing: '" << opname << "' to matching data type which can be '" << type1 << "', '"
             << type2 << "', '" << type3 << "', or '" << type4 << "'." << endl;
        colorize::end_state();
            exit(303);
    }

    void
    ParameterDataMismatch(const string &m_operator, Datatype type_1, Datatype type_2, Datatype type_3, Datatype _other,
                          const string &opname) {
        string type1 = Tknstringify::getDatatypeFromToken(type_1);
        string type2 = Tknstringify::getDatatypeFromToken(type_2);
        string type3 = Tknstringify::getDatatypeFromToken(type_3);
        string other = Tknstringify::getDatatypeFromToken(_other);
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << ", " << type2 << ", " << type3
             << "' to work, where '" << other << "' was provided" << err_line;
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider changing: '" << opname << "' to matching data type which can be '" << type1 << "', '"
             << type2 << "', or '" << type3 << "'." << endl;
        colorize::end_state();
            exit(303);
    }

    void ParameterDataMismatch(const string &m_operator, Datatype type_1, Datatype type_2, Datatype _other,
                               const string &opname) {
        string type1 = Tknstringify::getDatatypeFromToken(type_1);
        string type2 = Tknstringify::getDatatypeFromToken(type_2);
        string other = Tknstringify::getDatatypeFromToken(_other);
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << ", " << type2 << "' to work, where '" << other
             << "' was provided" << err_line;
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider changing: '" << opname << "' to matching data type which can be '" << type1 << "', or '"
             << type2 << "'." << endl;
        colorize::end_state();
            exit(303);
    }

    void ParameterDataMismatch(const string &m_operator, Datatype type_1, Datatype _other, const string &opname) {
        string type1 = Tknstringify::getDatatypeFromToken(type_1);
        string other = Tknstringify::getDatatypeFromToken(_other);
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 303 ParameterDataTypeMismatch [Parse Error]: Cannot find parameter match of operator '"
             << m_operator << "', which needs data type '" << type1 << "' to work, where '" << other << "' was provided"
             << err_line;
        if (type_1 == num && _other == str && m_operator == "dw") {
            colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider changing: '" << m_operator
                 << "' to appropriate alloc directive for strings, which is 'db'." << endl;
            colorize::end_state();
            exit(303);
        }
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider changing: '" << opname << "' to matching data type which is '" << type1 << "'." << endl;
        colorize::end_state();
            exit(303);
    }

    void CannotResolveOperands(const std::vector<token> tokens) {
        colorize::in_this_state_color_is(color::yellow);
                    cout << "ERR 304 IllegalOperandInstance [Parse Error]: Cannot resolve operand token stream, unable to operate on tokens ";
        for (auto &i: tokens) {
            colorize::in_this_state_color_is(color::yellow);
                    cout << "'" << i.name << "' ";
        }
        colorize::in_this_state_color_is(color::yellow);
                    cout << "because valid operators were not found. To resolve, check for missing operators or missing commas"
                  << err_line;
        chainhelp::resolveOperands(tokens);
        chainhelp::findOperands(tokens);
        colorize::end_state();
            exit(304);
    }

    void InvalidLabelTokenDeclaration(const string &label_name, const vector<token> &line_tokens) {
        colorize::in_this_state_color_is(color::yellow);
                    cout << "ERR 305 IllegalLabelDeclaration [Parse Error]: Cannot resolve token declaration of label '"
                  << label_name
                  << "'. Labels must be either be declared alone or must be placed in the beginning of a line. Postfix labels are not allowed"
                  << err_line;
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider the following syntax instead: '" << label_name << ":";
        string output;
        for (auto &j: line_tokens) {
            if (j.datatype != label) {
                output.append(" " + j.name + ",");
            }
        }
        output[output.size() - 1] = '\'';
        output.append(".");
        colorize::in_this_state_color_is(color::yellow);
            cout << output;
        colorize::end_state();
            exit(305);
    }

    void InvalidMemLocDeclaration(const string &str) {
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 306 InvalidMemoryLocationDeclaration [Parse Error]: Cannot resolve the declaration of token '["
             << str << "]'. Check for a missing comma" << err_line;
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider changing token: '[" << str << "]' to token '[" << str << "],'";
        colorize::end_state();
            exit(306);
    }

    void InvalidLabelCharacter(const char c) {
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 307 InvalidLabelCharacter [Parse Error]: Cannot parse label with starting character '" << c
             << "'. Labels must start with a numeric character" << err_line;
        colorize::end_state();
            exit(307);
    }

    void InvalidLabelCharacter(const string &c) {
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 307 InvalidLabelCharacter [Parse Error]: Cannot parse label with numeric tokens '" << c
             << "'. Labels must start with a numeric character" << err_line;
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider, did you perhaps mean to declare a numeric token? Consider changing '" << c << "' to '0d"
             << c << "'.\n";
        colorize::end_state();
            exit(307);
    }

    void InvalidLabelReferenceCharacter(const char c) {
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 308 InvalidLabelCharacter [Parse Error]: Cannot parse label reference with starting character '"
             << c << "'. Labels must start with an alphanumeric character" << err_line;
        colorize::end_state();
            exit(308);
    }

    void InvalidLabelReferenceCharacter(const string &c) {
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 307 InvalidLabelCharacter [Parse Error]: Cannot parse label reference with numeric tokens '" << c
             << "'. Labels must start with an alphanumeric character" << err_line;
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider, did you perhaps mean to declare a numeric token? Consider changing '" << c << "' to '0d"
             << c << "'.\n";
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider, did you perhaps mean to reference a memory location? Consider changing '" << c
             << "' to '[" << c << "]'.\n";
        colorize::end_state();
            exit(308);
    }

    void LabelRegisterCollision (const std::string & str) {
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 308 LabelRegisterCollision [Parse Error]: Cannot declare label '" << str << "' with the same name of register '" << str << "'" << err_line;
        colorize::end_state();
            exit(308);
    }


    void DataSizeMismatch(const string &reg_1, Register r1, const string &reg_2, Register r2) {
        auto size1 = Tknstringify::getDataSizeFromToken(r1);
        auto size2 = Tknstringify::getDataSizeFromToken(r2);
        colorize::in_this_state_color_is(color::yellow);
            cout
                << "ERR 400 DataSizeMismatch [Data Error]: Cannot perform operations on mismatched registers where register '"
                << reg_1 << "' has size " << size1 << " bits while register '" << reg_2 << "' has size " << size2
                << " bits" err_line2;
        colorize::end_state();
            exit(400);
    }

    void RegisterParameterMismatch(const string &instruction, const string &register_name, Register provided,
                                   Register required) {
        auto provided_ = Tknstringify::getDataSizeFromToken(provided);
        auto required_ = Tknstringify::getDataSizeFromToken(required);
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 401 RegisterSizeMismatch [Data Error]: Cannot perform operations on mismatched registers where '"
             << register_name << "' has register size " << provided_ << " bits while instruction '" << instruction
             << "' needs " << required_ << " bits" << err_line2;
        colorize::end_state();
            exit(401);
    }

    void ReferenceInvalidData(const string &mem_label) {
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 401 ReferenceInvalidSize [Data Error]: Cannot take the values of register '" << mem_label
             << "' as an address, as the register '" << mem_label << "' is 8-bit, and addresses are 16-bit values"
             << err_line;
        colorize::end_state();
            exit(401);
    }

    void NumericOverflow(int num, size_t insert_value){
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 402 NumericOverflow [Data Error]: Value overflow found at line"
                " " << line << " where max value is " << num << " and inserted value is " << insert_value << err_line;
        colorize::in_this_state_color_is(color::yellow);
            cout << ">>> Consider, reducing the size of the value used.\n";
        colorize::end_state();
            exit(402);
    }

    void InvalidIncrement (){
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 403 InvalidIncrement [Data Error]: Cannot increment the flag register" << err_line;
        colorize::end_state();
            exit(403);
    }

    void IteratorMismatch (const string & op, Datatype a, Datatype b){
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 404 IteratorMismatch [Data Error]: Cannot iterate through mismatched data types '" << Tknstringify::getDatatypeFromToken(a) << "' and '" << Tknstringify::getDatatypeFromToken(b) << "' where these two must match upon invoking of command '" << op << "'" << err_line;
        colorize::end_state();
            exit(404);
    }

    void PreprocessorDirectiveError(const std::string & dir){
        colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 501 UnrecognizedPreprocessorDirective [Preprocessor]: The preprocessor directive '" << dir << "' is unrecognized" << err_line;
        colorize::end_state();
            exit(501);
    }


    void UnsupportedRegisterAddressExtraction(const string &reg){
    colorize::in_this_state_color_is(color::yellow);
            cout << "ERR 600 Unsupported Feature [Feature Error]: Cannot extract the addresses of register '" << reg << "', as register address extraction is still unsupported in this build of the chainc: " << __ver__ << err_line;
    colorize::end_state();
            exit(600);
    }




}

#undef err_line
#undef err_line2

#include "errorhelper.h"

#endif //CHAIN_EXCEPTIONS_H
