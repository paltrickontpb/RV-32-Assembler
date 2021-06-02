#include "rv32-parse.h"
using namespace std;

rv32Parser::rv32Parser(){
    lineNumber = 0;
    instAddress = 0;
}

std::string rv32Parser::parseLine(std::string asmLine){
    // Logic
    std::string outBuf = "";
    std::regex initEx("([^/\r\n]*:)?([^/\r\n]*)?(//[^/\r\n]*)?"); //(Group 1: Address Label)(Group 2: Asm Command)(Group 3: Comment to be ignored)
    
    

    // Variable Update
    instAddress+=4; // Only if instruction exists (Line is not empty or has only a comment)
    lineNumber++;
    return outBuf; //Return the binary output of parsed line
}