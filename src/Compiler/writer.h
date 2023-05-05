//
// Created by Rufelle on 09/02/2023.
//

#ifndef CHAINC_WRITER_H
#define CHAINC_WRITER_H
#include "../extern/divefile.h"
#include "compiler_macros.h"

class Writer{
    dive::FileWriter wr;


public:
    Writer(dive::FileWriter & wr){
        this->wr = wr;
        write();
        wr.get()->close();
    }

    void write(){
        wr.writeLine(preprocessor.get_flags());
        wr.writeLine(memory.get_start() + '\n');
        for (int i=0; i<memory.MEM_CAP(); i++){
            auto string = memory.getBitString(i, 8);
            transpose(string);
            wr.writeLine(string);
        }
    }

    void transpose(string & bin)
    {
        if (!constants.COMPILE_MODE_BINARY) {
            bin.push_back('\n');
            return;
        }
        auto k = constants.binToDec(bin);
        bin = k;
    }
};

#endif //CHAINC_WRITER_H
