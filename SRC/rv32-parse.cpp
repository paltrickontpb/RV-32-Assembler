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

void rv32Parser::reset_LineAddress(){
    lineNumber = 0;
    instAddress = 0;
}

void rv32Parser::setAddress(int addr){
    instAddress = addr;
}

unsigned int rv32Parser::parseLine(std::string asmLine, int passNum){
    // Flags
    bool incrementAddress = false;
    bool assemblerDirective = false;
    bool isCommand = false;
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
            cout << "Label Found : " << label << " at location " << instAddress << endl;
            labelMap.insert({label, instAddress});
        }
    
        // Check for Commands
        if(asmCommand.size()>1) {
            isCommand = true;
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
            instAddress+=4; // Only if instruction exists (Line is not empty or has only a comment)
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
                if (instTypeMap.count(funcArgs[0]) == 0) return ERR_VAR;
                char instType = instTypeMap.find(funcArgs[0])->second;
                std::string opCode = opcodeMap.find(funcArgs[0])->second;
                std::string funct3 ,funct7;            
                int pcrel_13;

                outBuf |= stoi(opCode, 0, 2);

                switch (instType){
                    case 'R': funct3 = funct3Map.find(funcArgs[0])->second;
                              funct7 = funct7Map.find(funcArgs[0])->second;
                              outBuf |= (stoi(funct3, 0, 2) << 12);
                              outBuf |= (stoi(funct7, 0, 2) << 25);
                              if(funcArgs.size() < 4) return ARG_ERROR;
                              outBuf |= ((registerAliasMap.find(funcArgs[1])->second) << 7); // assigning rd
                              outBuf |= ((registerAliasMap.find(funcArgs[2])->second) << 15); // assigning rs1
                              outBuf |= ((registerAliasMap.find(funcArgs[3])->second) << 20); // assigning rs2
                              break;
                    case 'I': funct3 = funct3Map.find(funcArgs[0])->second;
                              outBuf |= (stoi(funct3, 0, 2) << 12);
                              //if(funcArgs[0]=="srli" || funcArgs[0]=="slli" || funcArgs[0]=="srai") {funct7 = funct7Map.find(funcArgs[0])->second; outBuf |= (stoi(funct7, 0, 2) << 25);}
                              //Define all types of I instructions
                              
                              break;
                    case 'S': funct3 = funct3Map.find(funcArgs[0])->second;
                              outBuf |= (stoi(funct3, 0, 2) << 12);
                              outBuf |= ((registerAliasMap.find(funcArgs[1])->second) << 20); //rs2
                              // imm(rs1) segregation
                              //cout << funcArgs.size() << endl;
                              if(funcArgs.size()==3){
                                  replace(funcArgs[2].begin(), funcArgs[2].end(), '(', ' ');
                                  replace(funcArgs[2].begin(), funcArgs[2].end(), ')', ' ');
                                  std::vector<std::string> immrs1;
                                  std::string tempstring = "";
                                  for (char z: funcArgs[2]){
                                      if(!isSpace(z)) tempstring += z;
                                      else {
                                        immrs1.push_back(tempstring);
                                        tempstring = "";
                                    }
                                  }
                                  std::bitset<5> immediateVal1(stoi(immrs1[0], 0, 10));
                                  std::bitset<7> immediateVal2(stoi(immrs1[0], 0, 10) >> 5);
                                  outBuf |= (immediateVal1.to_ulong() << 7);
                                  outBuf |= (immediateVal2.to_ulong() << 25);
                                  outBuf |= ((registerAliasMap.find(immrs1[1])->second) << 15); 
                              }
                              // Else throw error pointing why spaces are bad code styling
                              break;
                    case 'U': outBuf |= ((registerAliasMap.find(funcArgs[1])->second) << 7); //rd
                              if ((funcArgs[2][0] == '0' && funcArgs[2][1] == 'x') || funcArgs[2][funcArgs[2].size()-1] == 'h') {
                                  outBuf |= stoi(funcArgs[2], 0, 16) << 12; //hex
                              } else {
                                  outBuf |= stoi(funcArgs[2], 0, 10) << 12; //decimal
                              }
                              break;
                    case 'B': funct3 = funct3Map.find(funcArgs[0])->second;
                              outBuf |= (stoi(funct3, 0, 2) << 12);
                              outBuf |= ((registerAliasMap.find(funcArgs[1])->second) << 15); // assigning rs1
                              outBuf |= ((registerAliasMap.find(funcArgs[2])->second) << 20); // assigning rs2
                              //define pcrel13
                              pcrel_13 = labelMap.find(funcArgs[3])->second;
                              pcrel_13 -=  instAddress;
                              if(true) {
                                  std::bitset<13> immVal(pcrel_13);
                                  std::bitset<5> imm5rd(0);
                                  imm5rd.set(0, immVal[11]);
                                  for(int r=1; r<5; r++) imm5rd.set(r, immVal[r]);
                                  std::bitset<7> imm7imm(0);
                                  for(int r=5; r<11; r++) imm7imm.set(r-5, immVal[r]);
                                  imm7imm.set(6, immVal[12]);
                                  outBuf |= (imm5rd.to_ulong() << 7);
                                  outBuf |= (imm7imm.to_ulong() << 25);
                              }
                              break;
                    case 'J': outBuf |= ((registerAliasMap.find(funcArgs[1])->second) << 7); // assigning rd
                              //Define pcrel21
                              break;
                    default : cout << "Unexpected Error. Check instruction type map for wrong entries (other than r, i, s, b, u & j).";
                }
            }
            
            if(funcArgs[0]=="ecall") outBuf |= stoi("1110011", 0, 2); 
            else if (funcArgs[0]=="ebreak") { outBuf |= stoi("1110011", 0, 2); outBuf |= (1<<20); }
            
            // Assembler directive handler (We will handle Assembler Directives much later)
            //if(funcArgs[0][0] == '.') assemblerDirective = true;
            if (funcArgs[0][0] == '.') assemblerDirective = true;
            if(!assemblerDirective) {incrementAddress = true; isCommand = true;}
            
            std::string binary = std::bitset<32>(outBuf).to_string(); //to binary
            std::cout<< funcArgs[0] << " : " << binary<<"\n";  

            if(incrementAddress){
           // cout << "Address : " << instAddress << endl;
            instAddress+=4; // Only if instruction exists (Line is not empty or has only a comment)
            } 
            lineNumber++;
        }
    }

    if (isCommand) return outBuf; //Return the binary output of parsed line
    else return NULL_VAR;
}

