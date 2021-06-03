#include "rv32-parse.h"
using namespace std;

rv32Parser::rv32Parser(){
    lineNumber = 0;
    instAddress = 0;
}

std::string rv32Parser::parseLine(std::string asmLine){
    // Flags
    bool incrementAddress = false;
    // Logic
    std::string outBuf = "";
    std::regex initEx("([^/\r\n]*:)?([^/\r\n]*)?(//[^/\r\n]*)?"); //(Group 1: Address Label)
    std::smatch groups; //(Group 2: Asm Command)(Group 3: Comment to be ignored)
    
    regex_search(asmLine, groups, initEx);

    std::string label = groups.str(1);
    std::string asmCommand = groups.str(2);
    std::string Comment = groups.str(3); // Not exactly necessary

    if(label.size()>0) {
        label = label.substr(0, label.size()-1);
        cout << "Label Found : " << label << endl;
        labelMap.insert({label, instAddress});
    }
    
    if(asmCommand.size()>1) {
        cout << "Command found : " << asmCommand << endl;
        incrementAddress = true;
    }

    if(Comment.size()>1) {
        cout << "Comment found : " << Comment << endl;
    }

    // Variable Update
    if(incrementAddress){
        cout << "Address : " << instAddress << endl;
        instAddress+=32; // Only if instruction exists (Line is not empty or has only a comment)
    } 
    lineNumber++;
    return outBuf; //Return the binary output of parsed line
}