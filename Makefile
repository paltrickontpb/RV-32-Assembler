# Makefile
cc = g++
PWD = /home/protox/projects/rv32-asm
SRC = ${PWD}/SRC
BUILD = ${PWD}/BUILD
HEADERS = ${PWD}/HEADERS
CFLAGS = -Wall -I${HEADERS}

build:
	mkdir -p ${BUILD}
	$(cc) ${CFLAGS} ${SRC}/*.cpp -o ${BUILD}/rv32-asm

.PHONY: clean
clean:
	rm -rf ${BUILD}/*

.PHONY: run
run:
	${BUILD}/rv32-asm abc.asm