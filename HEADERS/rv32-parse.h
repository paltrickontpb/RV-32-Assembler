#ifndef _RV32_PARSE_H_
#define _RV32_PARSE_H_

#include "rv32-utils.h"

class rv32Parser{
    public:
        rv32Parser();
        std::string parseLine(std::string); //return hex or binary string(tbd)
    private:
        int lineNumber;
        int instAddress;

        //Map containing R,I,S,B,U,J Instruction Types
        std::map<std::string, char> instType{
            // R Instructions
            {"add", 'R'},
            {"sub", 'R'},
            {"xor", 'R'},
            {"or", 'R'},
            {"and", 'R'},
            {"sll", 'R'},
            {"srl", 'R'},
            {"sra", 'R'},
            {"slt", 'R'},
            {"sltu", 'R'},
            // I instructions
            {"addi", 'I'},
            {"xori", 'I'},
            {"ori", 'I'},
            {"andi", 'I'},
            {"slli", 'I'},
            {"srli", 'I'},
            {"srai", 'I'},
            {"slti", 'I'},
            {"sltiu", 'I'},
            {"lb", 'I'},
            {"lh", 'I'},
            {"lw", 'I'},
            {"lbu", 'I'},
            {"lhu", 'I'},
            // S Instructions
            {"sb", 'S'},
            {"sh", 'S'},
            {"sw", 'S'},
            // B instructions
            {"beq", 'B'},
            {"bne", 'B'},
            {"blt", 'B'},
            {"bge", 'B'},
            {"bltu", 'B'},
            {"bgeu", 'B'},
            // J Instructions
            {"jal", 'J'},
            {"jalr", 'I'}, //Follows I type, rather than J type
            // U instructions
            {"lui", 'U'},
            {"auipc", 'U'}
        };

        std::map<std::string, std::string> opcodeMap{
            {"add", "0110011"},
            {"sub", "0110011"},
            {"xor", "0110011"},
            {"or", "0110011"},
            {"and", "0110011"},
            {"sll", "0110011"},
            {"srl", "0110011"},
            {"sra", "0110011"},
            {"slt", "0110011"},
            {"sltu", "0110011"},
            // I instructions
            {"addi", "0010011"},
            {"xori", "0010011"},
            {"ori", "0010011"},
            {"andi", "0010011"},
            {"slli", "0010011"},
            {"srli", "0010011"},
            {"srai", "0010011"},
            {"slti", "0010011"},
            {"sltiu", "0010011"},
            {"lb", "0000011"},
            {"lh", "0000011"},
            {"lw", "0000011"},
            {"lbu", "0000011"},
            {"lhu", "0000011"},
            // S Instructions
            {"sb", "0100011"},
            {"sh", "0100011"},
            {"sw", "0100011"},
            // B instructions
            {"beq", "1100011"},
            {"bne", "1100011"},
            {"blt", "1100011"},
            {"bge", "1100011"},
            {"bltu", "1100011"},
            {"bgeu", "1100011"},
            // J Instructions
            {"jal", "1101111"},
            {"jalr", "1100111"},
            // U instructions
            {"lui", "0110111"},
            {"auipc", "0010111"}
        };

        std::map<std::string, std::string> funct3Map{
            {"add", "000"},
            {"sub", "000"},
            {"xor", "100"},
            {"or", "110"},
            {"and", "111"},
            {"sll", "001"},
            {"srl", "101"},
            {"sra", "101"},
            {"slt", "010"},
            {"sltu", "011"},
            // I instructions
            {"addi", "000"},
            {"xori", "100"},
            {"ori", "110"},
            {"andi", "111"},
            {"slli", "001"},
            {"srli", "101"},
            {"srai", "101"},
            {"slti", "010"},
            {"sltiu", "011"},
            {"lb", "000"},
            {"lh", "001"},
            {"lw", "010"},
            {"lbu", "100"},
            {"lhu", "101"},
            // S Instructions
            {"sb", "000"},
            {"sh", "001"},
            {"sw", "010"},
            // B instructions
            {"beq", "000"},
            {"bne", "001"},
            {"blt", "100"},
            {"bge", "101"},
            {"bltu", "110"},
            {"bgeu", "111"},
            // J Instructions
            {"jalr", "000"}
        };

        std::map<std::string, std::string> funct7Map{
            {"add", "0000000"},
            {"sub", "0100000"},
            {"xor", "0000000"},
            {"or", "0000000"},
            {"and", "0000000"},
            {"sll", "0000000"},
            {"srl", "0000000"},
            {"sra", "0100000"},
            {"slt", "0000000"},
            {"sltu", "0000000"}
        };
};

#endif