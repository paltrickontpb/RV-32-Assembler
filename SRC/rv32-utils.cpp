#include "rv32-utils.h"
using namespace std;

void rv32_asm_init(){
    cout << "================================================\n";
    cout << "        RISC-V 32I Base Integer Assembler       \n";
    cout << "================================================\n";
    cout << "               By : Paltrickontpb               \n";
    cout << "================================================\n";
    cout << endl;
}

ErrorHandler::ErrorHandler(){
    errorCode = 0;
}

int ErrorHandler::setError(int ecode){
    errorCode = ecode;
    return 0;
}

void ErrorHandler::printError(){
    /* Error List to be added with MAP later on
    Code            Reason/Explaination
    0               No Error
    1 - 10          Not Assigned for now
    11              Wrong number of args, No args (less than 2 argc size)
    12              Wrong number of args, more than 1 file argument
    13              Extension doesn't match .asm
    14              File does not exist (Or not opening due to perms error)
    */

    if(errorCode == 0) return;
    
    cout << "Error Code: " << errorCode << endl;
    cout << "Reason: " << errorMap.find(errorCode)->second <<endl;
}
