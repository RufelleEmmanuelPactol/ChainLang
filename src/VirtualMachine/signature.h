//
// Created by Rufelle on 02/04/2023.
//

#ifndef CHAINC_SIGNATURE_H
#define CHAINC_SIGNATURE_H
#include <string>


namespace signature
{
    using std::string;
    const string EMPTY = "00000000";
    const string NOOP = "0000";
    const string REGISTER8 = "0001";
    const string REGISTER16 = "0010";
    const string ADDRESS = "0011";
    const string POINTER = "0100";

}

namespace sgTKN
{
    const int EMPTY = 1;
    const int NOOP = 2;
    const int REGISTER8 = 3;
    const int REGISTER16 = 4;
    const int ADDRESS = 5;
    const int POINTER = 6;

}




#endif //CHAINC_SIGNATURE_H
