//
// Created by nik on 11/13/19.
//

#ifndef CVM_VM_H
#define CVM_VM_H

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// #include "../../uni/cs103/structs/stack.h"
#include "instr.h"

#define STACK_SIZE 256
#define DATA_SIZE 256

#define TRACE 1

typedef struct vm {
	uint32_t* code;
	uint32_t stack[STACK_SIZE];
	uint32_t data[DATA_SIZE];
	//registers
	uint32_t* ip;
	uint32_t* sp; //stack top
	uint32_t* fp;
} VM;

extern VM* vm_new(uint32_t* code, uint32_t size) {
	VM* newvm = calloc(1, sizeof(VM));
	newvm->code = calloc(size, sizeof(uint32_t));
	memcpy(newvm->code, code, size * sizeof(uint32_t));
	newvm->ip = newvm->code;
	newvm->sp = newvm->stack - 1;
	newvm->fp = newvm->stack - 1;
}

extern void vm_run(VM* vm) {
	uint32_t val1;
	uint32_t val2;
	while (1) {
		instr_t instr = decode(&vm->ip);
		if (TRACE)
			printf("%0.4x %0.4x ", instr.opcode, instr.param);
		switch (instr.opcode) {
			case NOP:
				break;
			case HALT:
				return;
			case PUSH:
				*(++vm->sp) = instr.param;
				if (TRACE)
					printf("PUSH %d", instr.param);
				break;
			case POP:
				break;
			case ADD:
				val1 = *(vm->sp--);
				val2 = *(vm->sp--);
				*(++vm->sp) = val1 + val2;
				break;
			case SUB:
				val1 = *(vm->sp--);
				val2 = *(vm->sp--);
				*(++vm->sp) = val1 - val2;
				break;
			case MUL:
				val1 = *(vm->sp--);
				val2 = *(vm->sp--);
				*(++vm->sp) = val1 * val2;
				break;
			case DIV:
				val1 = *(vm->sp--);
				val2 = *(vm->sp--);
				*(++vm->sp) = val1 / val2;
				break;
			case PRT:
				val1 = *(vm->sp);
				vm->sp--;
				printf("%s%3d", TRACE ? "PUT " : "", val1);
				break;
			case PRTC:
				val1 = *(vm->sp);
				vm->sp--;
				printf("%s%3c", TRACE ? "PUTC " : "", val1);
				break;
			case EQ:
				val1 = *(vm->sp--);
				val2 = *(vm->sp--);
				*(++vm->sp) = val1 == val2;
				break;
			case NE:
				val1 = *(vm->sp--);
				val2 = *(vm->sp--);
				*(++vm->sp) = val1 != val2;
				break;
			case LOAD:
				val1 = instr.param; // data ddr
				*(++vm->sp) = vm->data[val1];
				if (TRACE)
					printf("LOAD %3d %3d", val1);
				break;
			case STOR:
				val1 = *(vm->sp); // value
				vm->sp--;
				val2 = instr.param; // data addr
				vm->data[val2] = val1;
				if (TRACE)
					printf("STOR %3d %3d", val2, val1);
				break;
		}
		if (TRACE)
			printf("\n");
	}
}

void execute(VM* vm, instr_t instr) {

}

#endif //CVM_VM_H
