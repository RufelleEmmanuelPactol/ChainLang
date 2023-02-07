//
// Created by Rufelle on 18/01/2023.
//

#ifndef CHAINC_MEMORY_UNIT_H
#define CHAINC_MEMORY_UNIT_H
#include "math.h"
#include <array>
#include <cstring>
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
    size_t ar;
    size_t pc;
    bool flag;
    char * pc_char;
    char * ar_char;

    void set(char * arr){
        for (int i=0; i<16; i++){
            arr[i] = '0';
        }
    }

    char * regalloc(){
        auto * a = new char[8];
        if (a == NULL){
            regalloc();
        } return a;
    }

public:
    Memory(){



        r = regalloc();
        ac = regalloc();
        pc_char = regalloc();
        ar_char = regalloc();

        pc = 0;
        ar = 0;


        heap = new char*[mem_cap];
        for (int i=0; i<mem_cap; i++){
            heap[i] = new char[mem_cap];
            set(heap[i]);
        }

        set(r);
        set(ac);
        set(pc_char);
        set(ar_char);
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

    void display(size_t a, size_t b){
        for (int i=a; i<=b; i++){
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
public:
    auto& AR(){
        return ar;
    }

    auto& PC(){
        return pc;
    }

    auto HEAP (){
        return heap;
    }


    auto write (size_t address, const std::string & cpy){
        for (int i=0; i<8; i++){
           auto temp  = cpy[i];
            heap[address][i] = temp;
        }
    }

    auto inc (){
        pc++;
        ar++;
    }

    auto toBIN16(std::string num){

    }
};


#endif //CHAINC_MEMORY_UNIT_H
