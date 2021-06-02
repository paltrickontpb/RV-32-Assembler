# Makefile
cc = g++
PWD = .
SRC = ${PWD}/SRC
BUILD = ${PWD}/BUILD
HEADERS = ${PWD}/HEADERS
CFLAGS = -Wall -I${HEADERS}

buildandrun: build run

build:
	mkdir -p ${BUILD}
	$(cc) ${CFLAGS} ${SRC}/*.cpp -o ${BUILD}/rv32-asm

.PHONY: clean
clean:
	rm -rf ${BUILD}

.PHONY: run
run:
	${BUILD}/rv32-asm abc.asm
