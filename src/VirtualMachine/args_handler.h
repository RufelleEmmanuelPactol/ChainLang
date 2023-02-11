//
// Created by Rufelle on 10/02/2023.
//

#ifndef CHAINC_ARGS_HANDLER_H
#define CHAINC_ARGS_HANDLER_H

#include <vector>
#include <string>
#include "runtime.h"
namespace chain {
    void handle(const std::vector<std::string> &args) {
        if (args.size() == 1 ) {Runtime("out.bcc"); return;}
        Runtime(args.at(1));
    }
}


#endif //CHAINC_ARGS_HANDLER_H
