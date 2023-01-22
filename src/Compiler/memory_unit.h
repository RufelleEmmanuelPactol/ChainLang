//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_MEMORY_UNIT_H
#define CHAINC_MEMORY_UNIT_H
#include "math.h"
#include <array>
class Memory
{
    static const size_t mem_cap = pow(2, 16);
    char ** heap;

    // registers
    char * ac;
    char * acx;
    char * acy;
    char * r;
    char * rx;
    char * ry;
    char * ar;
    char * pc;
    bool flag;

    void set(char * arr){
        for (int i=0; i<16; i++){
            arr[i] = '0';
        }
    }

    static auto regalloc(){
        return new char[8];
    }

public:
    Memory(){


        ac = regalloc();
        r = regalloc();
        pc = regalloc();
        ar = regalloc();


        heap = new char*[mem_cap];
        for (int i=0; i<mem_cap; i++){
            heap[i] = new char[mem_cap];
            set(heap[i]);
        }

        set(ac);
        set(r);
        set(pc);
        set(ar);
        flag = false;

        acx = ac;
        acy = ac + 8;
        rx = r;
        ry = r + 8;


    }

    auto memory(){
        return heap;
    }

    void display(){
        for (int i=0; i<mem_cap; i++){
            std::cout << i << " > ";
            for (int j=0; j<=7; j++){
                std::cout << heap[i][j] << " ";
            } std::cout << std::endl;
        }
    }

    ~Memory(){
        for (int i=0; i<mem_cap; i++){
            delete heap[i];
        } delete heap;
    }
};


#endif //CHAINC_MEMORY_UNIT_H
