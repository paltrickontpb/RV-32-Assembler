#include "rv32-utils.h"
using namespace std;

int main(){
    // Initializing Variables and Screen
    system("clear");
    ErrorHandler errorHandler;

    // Start Init
    rv32_asm_init();
    errorHandler.printError();
    return 0;
}