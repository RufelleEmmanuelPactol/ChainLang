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
    bool ** heap;

    // registers
    bool * ac;
    bool * acx;
    bool * acy;
    bool * r;
    bool * rx;
    bool * ry;
    bool * ar;
    bool * pc;
    bool flag;

    void set(bool * arr){
        for (int i=0; i<16; i++){
            arr[i] = false;
        }
    }

    auto regalloc(){
        return new bool[8];
    }

public:
    Memory(){


        ac = regalloc();
        r = regalloc();
        pc = regalloc();
        ar = regalloc();


        heap = new bool*[mem_cap];
        for (int i=0; i<mem_cap; i++){
            heap[i] = new bool[mem_cap];
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
            for (int j=0; j<7; j++){
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
