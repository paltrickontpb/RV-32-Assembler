#ifndef _RV32_UTILS_H_
#define _RV32_UTILS_H_

#include <iostream>

class ErrorHandler{
    public:
        ErrorHandler();
        int assignError(int ecode);
        void printError();  
    private:
        int errorCode;
};

void rv32_asm_init();

#endif