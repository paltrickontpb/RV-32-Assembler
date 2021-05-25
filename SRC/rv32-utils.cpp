#include "rv32-utils.h"
using namespace std;

void rv32_asm_init(){
    cout << "================================================\n";
    cout << "        RISC-V 32I Base Integer Assembler       \n";
    cout << "================================================\n";
    cout << "               By : Paltrickontpb               \n";
    cout << "================================================\n";
}

ErrorHandler::ErrorHandler(){
    errorCode = 0;
}

int ErrorHandler::assignError(int ecode){
    errorCode = ecode;
    return 0;
}

void ErrorHandler::printError(){
    if(errorCode == 0) return;
    else cout << "Error\n";
}