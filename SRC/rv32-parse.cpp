#include "rv32-parse.h"
using namespace std;

rv32Parser::rv32Parser(){
    lineNumber = 0;
    instAddress = 0;
}

std::string rv32Parser::parseLine(std::string){
    // Logic
    
    // Variable Update
    instAddress+=4;
    lineNumber++;
    return ""; //Return the binary output of parsed line
}