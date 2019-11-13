//
// Created by nik on 11/13/19.
//

#ifndef CVM_INSTR_H
#define CVM_INSTR_H

#pragma once

#include <stdint.h>

#define OPCODE_MASK 0xFFFF0000
#define P1_MASK     0x0000FF00
#define P2_MASK     0x000000FF

#define NOP    0x0000
#define HALT   0x0001
#define PUSH   0x0002
#define POP    0x0003
#define ADD    0x0004
#define SUB    0x0005
#define MUL    0x0006
#define DIV    0x0007
#define PRT    0x0008
#define PRTC   0x0009
#define EQ     0x000a
#define NE     0x000b
#define LT     0x000c
#define GT     0x000d
#define JMP    0x000e
#define JEQ    0x000f
#define JNE    0x0010
#define JLS    0x0011
#define JGT    0x0012
#define LOAD   0x0013
#define STOR   0x0014


typedef struct instruction {
	uint16_t opcode;
	uint16_t param;
} instr_t;


extern instr_t decode(uint32_t** code) {
	uint16_t opcode = (**code) >> 16u;
	instr_t instr;
	instr.opcode = opcode;
	instr.param = (uint16_t) **code;
	(*code)++;
	return instr;
}


#endif //CVM_INSTR_H
