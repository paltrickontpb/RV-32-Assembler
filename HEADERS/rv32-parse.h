#ifndef _RV32_PARSE_H_
#define _RV32_PARSE_H_

#include "rv32-utils.h"

class rv32Parser{
    public:
        rv32Parser();
        std::string parseLine(std::string); //return hex or binary string
    private:
        int lineNumber;
        int instAddress;
        //Map containing structures
};

#endif