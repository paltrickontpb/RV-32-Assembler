#ifndef _RV32_UTILS_H_
#define _RV32_UTILS_H_

#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>
#include <bitset>

#define NULL_VAR -1
#define ERR_VAR -2
#define ARG_ERROR -3

class ErrorHandler{
    public:
        ErrorHandler();
        int setError(int ecode);
        void printError();  
    private:
        int errorCode;

        // Associative Map Structure for Errorcode responses
        std::map<int, std::string> errorMap {
            {0, "No Errors"},
            {1, "Logical Error"},
            {11, "No args (less than 2 argc size)"},
            {12, "Wrong number of args (More than 1 file argument)"},
            {13, "Extension doesn't match .asm"},
            {14, "File does not exist (Or not opening due to permissions error)"}
        };
        
};

void rv32_asm_init();

#endif