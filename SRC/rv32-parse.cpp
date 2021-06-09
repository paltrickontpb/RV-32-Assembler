#include "rv32-parse.h"
using namespace std;

bool isSpace(unsigned char c) {
    return (c == ' ' || c == '\n' || c == '\r' ||
        c == '\t' || c == '\v' || c == '\f');
}

rv32Parser::rv32Parser(){
    lineNumber = 0;
    instAddress = 0;
}

unsigned int rv32Parser::parseLine(std::string asmLine, int passNum){
    // Flags
    bool incrementAddress = false;
    bool assemblerDirective = false;
    // Logic
    unsigned int outBuf = 0;
    std::regex initEx("([^/\r\n]*:)?([^/#\t\r\n]*)?(#[^/\r\n]*)?"); //(Group 1: Address Label)
    std::smatch groups; //(Group 2: Asm Command)(Group 3: Comment to be ignored)
    
    regex_search(asmLine, groups, initEx);

    std::string label = groups.str(1);
    std::string asmCommand = groups.str(2);
    std::string Comment = groups.str(3); // Not exactly necessary

    // First Pass Logic
    if(passNum == 1) {
        // Check for Labels
        if(label.size()>0) {
            label = label.substr(0, label.size()-1);
            //cout << "Label Found : " << label << endl;
            labelMap.insert({label, instAddress});
        }
    
        // Check for Commands
        if(asmCommand.size()>1) {
            replace(asmCommand.begin(), asmCommand.end(), ',', ' '); asmCommand += " ";
            std::vector<std::string> funcArgs;
            std::string tempString = "";
            for (char y: asmCommand){
                if(!isSpace(y)) tempString += y;
                else {
                    if(tempString.size()>1) funcArgs.push_back(tempString);
                    tempString = "";
                }
            }
            //cout << "Command found : ";
            //for(std::string j : funcArgs) cout << j << " ";
            //cout << endl;

            // Assembler directive handler (We will handle Assembler Directives much later)
            //if(funcArgs[0][0] == '.') assemblerDirective = true;
            if(!assemblerDirective) incrementAddress = true;

            
        }

        if(Comment.size()>1) {
            //cout << "Comment found : " << Comment << endl;
        }

        // Variable Update
        if(incrementAddress){
           // cout << "Address : " << instAddress << endl;
            instAddress+=32; // Only if instruction exists (Line is not empty or has only a comment)
        } 
        lineNumber++;
    }
    
    // Second Pass Logic
    if(passNum == 2){
        /* Check whether address is pushed into vector
        if(label.size()>0) {
            label = label.substr(0, label.size()-1);
            cout << "Label Found : " << label << endl;
            cout << "Address from first Pass: " << labelMap.find(label)->second <<endl;
        } */

        // Parse Commands

        if(asmCommand.size()>1) {
            replace(asmCommand.begin(), asmCommand.end(), ',', ' '); asmCommand += " ";
            std::vector<std::string> funcArgs;
            std::string tempString = "";
            for (char y: asmCommand){
                if(!isSpace(y)) tempString += y;
                else {
                    if(tempString.size()>1) funcArgs.push_back(tempString);
                    tempString = "";
                }
            }
            
            // Command segregation
            if (funcArgs[0][0] != '.' && funcArgs[0][1] != '.' && funcArgs[0] != "ecall" && funcArgs[0] != "ebreak"){
                char instType = instTypeMap.find(funcArgs[0])->second;
                std::string opCode = opcodeMap.find(funcArgs[0])->second;
                std::string funct3 ,funct7;            

                outBuf |= stoi(opCode, 0, 2);

                switch (instType){
                    case 'R': funct3 = funct3Map.find(funcArgs[0])->second;
                              funct7 = funct7Map.find(funcArgs[0])->second;
                              outBuf |= (stoi(funct3, 0, 2) << 12);
                              outBuf |= (stoi(funct7, 0, 2) << 25);
                              // define rd, rs1, rs2
                              break;
                    case 'I': funct3 = funct3Map.find(funcArgs[0])->second;
                              outBuf |= (stoi(funct3, 0, 2) << 12);
                              if(funcArgs[0]=="srli" || funcArgs[0]=="slli" || funcArgs[0]=="srai") {funct7 = funct7Map.find(funcArgs[0])->second; outBuf |= (stoi(funct7, 0, 2) << 25);}
                              //Define all types of I instructions
                              break;
                    case 'S': funct3 = funct3Map.find(funcArgs[0])->second;
                              outBuf |= (stoi(funct3, 0, 2) << 12);
                              // Define rs2, rs1, imm
                              break;
                    case 'U': //define imm and rd
                              break;
                    case 'B': funct3 = funct3Map.find(funcArgs[0])->second;
                              outBuf |= (stoi(funct3, 0, 2) << 12);
                              //define rs1, rs2, pcrel_to_imm
                              break;
                    case 'J': funct3 = funct3Map.find(funcArgs[0])->second;
                              outBuf |= (stoi(funct3, 0, 2) << 12);
                              //define imm and rd
                              break;
                    default : cout << "RIP FAM";
                }
            }
            
            if(funcArgs[0]=="ecall") outBuf |= stoi("1110011", 0, 2); 
            else if (funcArgs[0]=="ebreak") { outBuf |= stoi("1110011", 0, 2); outBuf |= (1<<20); }
            
            // Assembler directive handler (We will handle Assembler Directives much later)
            //if(funcArgs[0][0] == '.') assemblerDirective = true;
            if(!assemblerDirective) incrementAddress = true;

            
        }

        std::string binary = std::bitset<32>(outBuf).to_string(); //to binary
        std::cout<<binary<<"\n";

    }

    return outBuf; //Return the binary output of parsed line
}

