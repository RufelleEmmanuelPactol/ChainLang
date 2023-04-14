//
// Created by Rufelle on 12/04/2023.
//

#ifndef CHAINC_DEBUG_H
#define CHAINC_DEBUG_H
#include "preprocessor.h"
#define debugf(...) if (preprocessor.isDebugging()) printf(__VA_ARGS__)


#endif //CHAINC_DEBUG_H
