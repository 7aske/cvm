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
#include "opcode.h"

#define STACK_SIZE 256
#define DATA_SIZE 256


#ifndef VM_TRACE
#define VM_TRACE 0
#define PUTC_FMT "%c"
#else
#undef VM_TRACE
#define VM_TRACE 1
#define PUTC_FMT "%c\n"
#endif

#ifndef TRACE_CHAR
#define TRACE_CHAR 0
#define STACK_FMT " %d"
#else
#undef TRACE_CHAR
#define TRACE_CHAR 1
#define STACK_FMT " %c"
#endif

// Utility macros for pushing and popping of off the main stack
#define pop2(x) x->reg1 = *x->sp, x->sp--; x->reg2 = *x->sp, x->sp--
#define push2(x) *(++vm->sp) = vm->reg2; *(++vm->sp) = vm->reg1
#define push2r(x) *(++vm->sp) = vm->reg1; *(++vm->sp) = vm->reg2
#define pop(x) x->reg1 = *x->sp, x->sp--
#define push(x) *(++x->sp) = x->reg1

typedef struct vm {
	uint8_t* code;     // code memory
	int32_t code_size; // size of code memory in bytes
	int32_t* stack;    // main stack
	int32_t* data;     // data stack

	//registers
	uint8_t* ip;   // instruction pointer
	int32_t* sp;   // stack top
	int32_t* fp;   // frame pointer NOT USED
	int32_t reg1;  // first register
 	int32_t reg2;  // second register
} VM;


void print_stack(const uint32_t* base, const uint32_t* stack) {
	while (stack > base) {
		printf(STACK_FMT, *stack == 10 && TRACE_CHAR ? 32 : *stack);
		stack--;
	}
}

extern VM* vm_new(uint8_t* code, uint32_t size) {
	VM* newvm = calloc(1, sizeof(VM));
	uint8_t* codeptr = (uint8_t*) calloc(size, sizeof(uint8_t));
	int32_t* dataptr = (int32_t*) calloc(DATA_SIZE, sizeof(int32_t));
	newvm->code_size = size;
	newvm->stack = calloc(STACK_SIZE, sizeof(uint32_t));
	memcpy(codeptr, code, size * sizeof(uint8_t));
	newvm->code = codeptr;
	newvm->ip = codeptr;
	newvm->sp = newvm->stack - 1;
	newvm->fp = newvm->stack - 1;
	newvm->data = dataptr - 1;
}

static void print_code(VM* vm) {
	for (int i = 0; i < vm->code_size; ++i) {
		printf("0x%x ", vm->ip);
		printf("0x%x %s\n", vm->code + i, mnemonic(*(vm->code + i)));
	}
}

extern void vm_run(VM* vm) {
	if (VM_TRACE) {
		printf("%10s %6s %4s %5s\n", "Address", "Instr", "Opc", "Stack");
	}
	while (1) {
		// print_code(vm);
		opcode_e opcode = decode(vm->ip);
		vm->ip++;
		if (VM_TRACE) {
			printf("0x%x 0x%0.4x %4s", vm->ip - 1, vm->ip - vm->code - 1, mnemonic(opcode));
			print_stack(vm->fp, vm->sp);
			printf("\n");
		}
		switch (opcode) {
			case ADD:
			pop2(vm);
				*(++vm->sp) = vm->reg1 + vm->reg2;
				break;
			case AND:
			pop2(vm);
				*(++vm->sp) = vm->reg1 & vm->reg2;
				break;
			case CALL:
				break;
			case DEC:
				pop(vm);
				*(++vm->sp) = --vm->reg1;
				break;
			case DIV:
			pop2(vm);
				*(++vm->sp) = vm->reg1 / vm->reg2;
				break;
			case HLT:
				return;
			case INC:
				pop(vm);
				*(++vm->sp) = ++vm->reg1;
				break;
			case JMP:
				vm->reg1 = next_32(vm->ip);
				vm->ip += 4;
				vm->ip = vm->code + vm->reg1;
				break;
			case MOV:
				// TODO: MOV
				break;
			case NOP:
				break;
			case OR:
			pop2(vm);
				*(++vm->sp) = vm->reg1 | vm->reg2;
				break;
			case POP:
				vm->sp--;
				break;
			case PUSH:
				*(++vm->sp) = next_32(vm->ip);
				vm->ip += 4;
				break;
			case RET:
				break;
			case SUB:
			pop2(vm);
				*(++vm->sp) = vm->reg1 - vm->reg2;
				break;
			case TEST:
			pop2(vm);
				push2(vm);
				*(++vm->sp) = vm->reg1 == vm->reg2;
				break;
			case XOR:
			pop2(vm);
				*(++vm->sp) = vm->reg1 ^ vm->reg2;
				break;
			case NOT:
				pop(vm);
				*(++vm->sp) = ~vm->reg1;
				break;
			case SHL:
			pop2(vm);
				*(++vm->sp) = vm->reg1 << vm->reg2;
				break;
			case SHR:
			pop2(vm);
				*(++vm->sp) = vm->reg1 >> vm->reg2;
				break;
			case PUT:
				// pop(vm);

				printf("%d\n", *vm->sp);
				break;
			case PUTC:
				// pop(vm);
				printf(PUTC_FMT, *vm->sp);
				break;
			case MUL:
			pop2(vm);
				*(++vm->sp) = vm->reg1 + vm->reg2;
				break;
			case JE:
			pop2(vm);
				push2(vm);
				if (vm->reg1 == vm->reg2) {
					vm->reg2 = next_32(vm->ip);
					vm->ip += 4;
					vm->ip = vm->code + vm->reg2;
				} else {
					next_32(vm->ip);
					vm->ip += 4;
				}
				break;
			case JZ:
			pop2(vm);
				pop(vm);
				vm->reg2 = next_32(vm->ip);
				vm->ip += 4;
				if (vm->reg1 == 0) {
					vm->ip = vm->code + vm->reg2;
				}
				break;
			case JG:
			pop2(vm);
				push2(vm);
				if (vm->reg1 > vm->reg2) {
					vm->reg2 = next_32(vm->ip);
					vm->ip += 4;
					vm->ip = vm->code + vm->reg2;
				} else {
					next_32(vm->ip);
					vm->ip += 4;
				}
				break;
			case JGE:
			pop2(vm);
				push2(vm);
				if (vm->reg1 >= vm->reg2) {
					vm->reg2 = next_32(vm->ip);
					vm->ip += 4;
					vm->ip = vm->code + vm->reg2;
				} else {
					next_32(vm->ip);
					vm->ip += 4;
				}
				break;
			case JL:
			pop2(vm);
				push2(vm);
				if (vm->reg1 < vm->reg2) {
					vm->reg2 = next_32(vm->ip);
					vm->ip += 4;
					vm->ip = vm->code + vm->reg2;
				} else {
					next_32(vm->ip);
					vm->ip += 4;
				}
				break;
			case JLE:
			pop2(vm);
				push2(vm);
				if (vm->reg1 <= vm->reg2) {
					vm->reg2 = next_32(vm->ip);
					vm->ip += 4;
					vm->ip = vm->code + vm->reg2;
				} else {
					next_32(vm->ip);
					vm->ip += 4;
				}
				break;
			case STOR:
				pop(vm);
				*(++vm->data) = vm->reg1;
				break;
			case LOAD:
				vm->reg1 = *vm->data, vm->data--;
				push(vm);
				break;
			case DUP:
				pop(vm);
				vm->reg2 = vm->reg1;
				push2(vm);
				break;
			case SWAP:
			pop2(vm);
				push2r(vm);
				break;
			default:
				break;
		}
	}
}

#endif //CVM_VM_H
