#ifndef _RV32_UTILS_H_
#define _RV32_UTILS_H_

#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>

class ErrorHandler{
    public:
        ErrorHandler();
        int setError(int ecode);
        void printError();  
    private:
        int errorCode;
};

void rv32_asm_init();

#endif