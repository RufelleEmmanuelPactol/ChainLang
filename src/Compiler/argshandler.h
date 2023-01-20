//
// Created by Rufelle on 17/01/2023.
//

#ifndef CHAIN_ARGSHANDLER_H
#define CHAIN_ARGSHANDLER_H
#include "exceptions.h"
#include "compiler.h"

namespace chain
{
    auto null_args (strvector_p args){

    }

    auto handle (strvector_p args){
        if (args.size()<=2){
            if (args.size()==2){
                NoPathProvidedException(args.at(1));
            }
            null_args(args);
            return;
        }

        // compiler call
        if (args.at(1)=="-c"){
            compiler(args.at(2));
        }


    }

}

#endif //CHAIN_ARGSHANDLER_H
