//
// Created by Rufelle on 13/01/2023.
//

#ifndef CINDER_VECTORIZE_H
#define CINDER_VECTORIZE_H
#include <vector>
#include <string>
namespace dive{
    auto vectorize (int argc, char ** argv){
        std::vector<std::string> ret;
        for (int i=0; i<argc; i++){
            ret.emplace_back(argv[i]);
        }
        return ret;
    }

}


#endif //CINDER_VECTORIZE_H
