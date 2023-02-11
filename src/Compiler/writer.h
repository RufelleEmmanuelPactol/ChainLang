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
        for (int i=0; i<memory.MEM_CAP(); i++){
            auto string = memory.getBitString(i, 8);
            wr.writeLine(string + '\n');
            wr.flush();
        }
    }
};

#endif //CHAINC_WRITER_H
