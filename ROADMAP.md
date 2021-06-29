## Road-map for development of project

1. ~~Setup Basic Project folder layout with a Makefile~~
2. ~~Add all make directives/commands~~
3. ~~Pass file as ARG in C++ using argv, argc and check file extension~~
4. ~~Readfile, assert its existence and copy to memory buffer (Line by line using a string vector)~~
5. ~~Add error handler object in utils~~
6. ~~Create associative mapping for error codes~~
7. ~~Create associative mapping for opcodes, funct7, funct3 and instructionTypes~~
8. ~~Add Line parsing object with required variables like address~~
9. ~~Read each line and segment it into Label, Command and Comment using Regular Expression~~
10. ~~Pass Each label with address into an associative map~~
11. ~~Increment address with each command~~
12. ~~Segment command into function and args~~
13. Pass Address to each label instance in second pass
14. ~~Map all ASM functions to get binary format, and convert args into binary using registerAliasMap~~
15. ~~Create 32bit long binary lines and return those from parser function~~
16. Map Assembler directives into the process
17. Create testbenches during make file operation

**Note**: Strikethrough lines are ones that have been completed. New steps will be added as and when required.