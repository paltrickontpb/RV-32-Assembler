#include "rv32-utils.h"
#include "rv32-parse.h"
using namespace std;

int main(int argc, char **argv){
    // Initializing Variables and Screen
    system("clear");
    ErrorHandler errorHandler;
    std::vector<std::string> fileBuffer;
    std::vector<unsigned int> outBuffer;

    // Start Init
    rv32_asm_init();
    errorHandler.printError();

    // Check Args Validity
    switch(argc){
        case 0:
        case 1:
            errorHandler.setError(11);
            errorHandler.printError();
            return 0;
            break;
        case 2:
            break;
        default:
            errorHandler.setError(12);
            errorHandler.printError();
            return 0;
    }
    
    // Start file preprocessing
    string filename = argv[1];
    cout << "Input File name: " << filename << endl;
    std::string fileExt = "";
    for (int i=4; i>=1 ; i-- ) fileExt += filename[filename.size() - i]; // Find Extension from filename
    if (fileExt != ".asm"){
        errorHandler.setError(13);
        errorHandler.printError();
        return 0;
    }
    
    // Load File to Memory 
    ifstream file(filename);
    if(!file){
        errorHandler.setError(14);
        errorHandler.printError();
        return 0;
    }
    string tempBuf;
    while(getline(file, tempBuf)) fileBuffer.push_back(tempBuf);
    file.close(); // ASM file now exists in vector fileBuffer

    // Parse Each Line Using Parser class (Not yet created)
    //for (auto i: fileBuffer) cout << i <<endl;
    rv32Parser Parser;
    
    // First Pass
    for (auto i: fileBuffer){
        Parser.parseLine(i,1);
    }
    
    Parser.reset_LineAddress();

    // Second Pass
    for (auto j: fileBuffer){
        int tmp = Parser.parseLine(j,2);
        cout << tmp << endl;
        if (tmp != NULL_VAR) outBuffer.push_back(tmp);
    }

    //for (auto i: outBuffer) std::cout << i << std::endl;
    ofstream outFile("out.bin", ios::out | ios::binary);
    if(!outFile) {
      cout << "Cannot open file!" << endl;
      return 1;
   }
    
    for (auto i: outBuffer) {
        cout<< i << endl; 
        outFile.write( reinterpret_cast<const char*>(&i), sizeof(i) ) ;
    }
    outFile.close();
    // Write 32bit to file, Ignore Nulls and Pass Error to Error Handler
    return 0;
}