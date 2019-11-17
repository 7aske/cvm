//
// Created by nik on 11/13/19.
//

#ifndef CVM_OPCODE_H
#define CVM_OPCODE_H

#pragma once

#include <stdint.h>

typedef enum opcodes {
	// Pop two values of the stack and push their sum to the stack.
			ADD = 0x00,
	// Pop two values of the stack and push the result of logical AND operation to the stack.
			AND = 0x20,
	// Call external procedure TO BE IMPLEMENTED
			CALL = 0x9A,
	// Decrement the value on the top of the stack by 1.
			DEC = 0x48,
	// Pop two values of the stack and push the result of their division to the stack.
			DIV = 0xF6,
	// Halt the machine stopping execution.
			HLT = 0xF4,
	// Increment the value on the top of the stack by 1.
			INC = 0x40,
	// Preform jump operation if the top two values of the stack are equal. Stack is unchanged after comparison.
			JE = 0x74,
	// Preform jump operation if the top value is greater than the second. Stack is unchanged after comparison.
			JG = 0x7F,
	// Preform jump operation if the top value is greater or equal to the second. Stack is unchanged after comparison.
			JGE = 0x7D,
	// Preform jump operation if the top value is less than the second. Stack is unchanged after comparison.
			JL = 0x7C,
	// Preform jump operation if the top value is less or equal to the second. Stack is unchanged after comparison.
			JLE = 0x7E,
	// Preform jump operation if the top value is zero. Stack is unchanged after comparison.
			JZ = 0x76,
	// Preform jump operation to the address value specified as the parameter.
			JMP = 0xE9,
	// Move the value from one memory location to the other TO BE IMPLEMENTED
			MOV = 0xA0,
	//Pop two values of the stack and push the result of their multiplication to the stack.
			MUL = 0x6B,
	// No operation
			NOP = 0x90,
	// Preform logical NOT on the top value of the stack
			NOT = 0xF7,
	// Preform logical OR on the top value of the stack
			OR = 0x08,
	// Discard the top value of the stack
			POP = 0x07,
	// Push the value specified as the parameter to the stack.
			PUSH = 0x06,
	// Return from procedure NOT YET IMPLEMENTED
			RET = 0xCA,
	// Preform logical SHIFT LEFT on the top two values of the stack
			SHL = 0xD0,
	// Preform logical SHIFT RIGHT on the top two values of the stack
			SHR = 0xD1,
	// Pop two values of the stack and push the result of their subtraction to the stack.
			SUB = 0x28,
	// Push the result of comparison of top two values of the stack. Stack is unchanged after comparison.
			TEST = 0x84,
	// Preform logical XOR on the top two values of the stack
			XOR = 0x30,
	// Print the top value to the console in decimal form. Stack is unchanged.
			PUT = 0xFA,
	// Print the top value to the console in character form. Stack is unchanged.
			PUTC = 0xFB,
	// Store the top value of the stack to the data stack. Data stack pointer is incremented.
			STOR = 0xFC,
	// Load top value of the data stack and push it to the stack. Data stack pointer is decremented.
			LOAD = 0xFD,
	// Swap top two values of the stack.
			SWAP = 0x56,
	// Push the copy of the top value to the stack.
			DUP = 0xE8,
} opcode_e;


// Return the byte value as opcode.
static opcode_e decode(uint8_t* code) {
	opcode_e opcode = *code;
	return opcode;
}

// Return next 4 bytes of the code memory. Actual memory pointer is not changed.
extern uint32_t next_32(uint8_t* code) {
	int32_t val = 0;
	val |= *code << 24;
	code++;
	val |= *code << 16;
	code++;
	val |= *code << 8;
	code++;
	val |= *code;
	return val;
}

// String parsing of opcodes for debugging
extern char* mnemonic(opcode_e opcode) {
	switch (opcode) {
		case ADD:
			return "ADD";
		case AND:
			return "AND";
		case CALL:
			return "CALL";
		case DEC:
			return "DEC";
		case DIV:
			return "DIV";
		case HLT:
			return "HLT";
		case INC:
			return "INC";
		case JMP:
			return "JMP";
		case MOV:
			return "MOV";
		case NOP:
			return "NOP";
		case OR:
			return "OR";
		case POP:
			return "POP";
		case PUSH:
			return "PUSH";
		case SUB:
			return "SUB";
		case TEST:
			return "TEST";
		case XOR:
			return "XOR";
		case NOT:
			return "NOT";
		case SHL:
			return "SHL";
		case SHR:
			return "SHR";
		case PUT:
			return "PUT";
		case PUTC:
			return "PUTC";
		case JE:
			return "JE";
		case JZ:
			return "JZ";
		case JG:
			return "JG";
		case JGE:
			return "JGE";
		case JL:
			return "JL";
		case JLE:
			return "JLE";
		case MUL:
			return "MUL";
		case RET:
			return "RET";
		case STOR:
			return "STOR";
		case LOAD:
			return "LOAD";
		case DUP:
			return "DUP";
		case SWAP:
			return "SWAP";
		default:
			return "";
	}
}

#endif //CVM_OPCODE_H

// WAIT = 0x9B,                 // /*Wait until not busy*/
// XCHG = 0x86,                 // 0x87 0x91 0x97 /*Exchange data*/
// XLAT = 0xD7,                 // /*Table look-up translation*/
// AAA = 0x37,                  // /*ASCII adjust AL after addition*/
// AAD = 0xD5,                  // /*ASCII adjust AX before division*/
// AAM = 0xD4,                  // /*ASCII adjust AX after multiplication*/
// AAS = 0x3F,                  // /*ASCII adjust AL after subtraction*/
// ADC = 0x10,                  // 0x15 0x80 0x83 /*Add with carry*/
// CBW = 0x98,                  // /*Convert byte to word*/
// CLC = 0xF8,                  // /*Clear carry flag*/
// CLD = 0xFC,                  // /*Clear direction flag*/
// CLI = 0xFA,                  // /*Clear interrupt flag*/
// CMC = 0xF5,                  // /*Complement carry flag*/
// CMP = 0x38,                  // 0x3D 0x80 0x83 /*Compare operands*/
// CMPSB = 0xA6,                // /*Compare bytes in memory*/
// CMPSW = 0xA7,                // /*Compare words*/
// CWD = 0x99,                  // /*Convert word to doubleword*/
// DAA = 0x27,                  // /*Decimal adjust AL after addition*/
// DAS = 0x2F,                  // /*Decimal adjust AL after subtraction*/
// IDIV = 0xF7,                  // 0xF7 /*Signed divide*/
// IMUL = 0x69,                  	// 0x6B 0xF6 0xF7 0x0F /*Signed multiply*/
// IN = 0xE4,                   // 0xE5 0xEC 0xED /*Input from port*/
// INT = 0xCC,                  // 0xCD /*Call to interrupt*/
// INTO = 0xCE,                 // /*Call to interrupt if overflow*/
// IRET = 0xCF,                 // /*Return from interrupt*/
// JA = 0x77, 						// Jump short if above (CF=0 and ZF=0).
// JAE = 0x73, 					// Jump short if above or equal (CF=0).
// JB = 0x72, 						// Jump short if below (CF=1).
// JBE = 0x76, 					// Jump short if below or equal (CF=1 or ZF=1).
// JC = 0x72, 					// Jump short if carry (CF=1).
// JCXZ = 0xE3, 				// Jump short if CX register is 0.
// JECXZ = 0xE3, 				// Jump short if ECX register is 0.
// JNA = 0x76, 					// Jump short if not above (CF=1 or ZF=1).
// JNAE = 0x72, 				// Jump short if not above or equal (CF=1).
// JNB = 0x73, 					// Jump short if not below (CF=0).
// JNBE = 0x77, 				// Jump short if not below or equal (CF=0 and ZF=0).
// JNC = 0x73, 					// Jump short if not carry (CF=0).
// JNE = 0x75, 					// Jump short if not equal (ZF=0).
// JNG = 0x7E, 					// Jump short if not greater (ZF=1 or SF<>OF).
// JNGE = 0x7C, 				// Jump short if not greater or equal (SF<>OF).
// JNL = 0x7D, 					// Jump short if not less (SF=OF).
// JNLE = 0x7F, 				// Jump short if not less or equal (ZF=0 and SF=OF).
// JNO = 0x71, 					// Jump short if not overflow (OF=0).
// JNP = 0x7B, 					// Jump short if not parity (PF=0).
// JNS = 0x79, 					// Jump short if not sign (SF=0).
// JNZ = 0x75, 					// Jump short if not zero (ZF=0).
// JO = 0x70, 					// Jump short if overflow (OF=1).
// JP = 0x7A, 					// Jump short if parity (PF=1).
// JPE = 0x7A, 					// Jump short if parity even (PF=1).
// JPO = 0x7B, 					// Jump short if parity odd (PF=0).
// JS = 0x78, 					// Jump short if sign (SF=1).
// LAHF = 0x9F,                 // /*Load FLAGS into AH register*/
// LDS = 0xC5,                  // /*Load pointer using DS*/
// LEA = 0x8D,                  // /*Load Effective Address*/
// LES = 0xC4,                  // /*Load ES with pointer*/
// LOCK = 0xF0,                 // /*Assert BUS LOCK# signal*/
// LODSB = 0xAC,                // /*Load string byte*/
// LODSW = 0xAD,                // /*Load string word*/
// LOOP = 0xE0,                 // 0xE2 /*Loop control*/
// MOVSB = 0xA4,                // /*Move byte from string to string*/
// MOVSW = 0xA5,                // /*Move word from string to string*/
// NEG = 0xF7,                  	// 0xF7 /*Two's complement negation*/
// OUT = 0xE6,                  // 0xE7 0xEE 0xEF /*Output to port*/
// POPF = 0x9D,                 // /*Pop FLAGS register from stack*/
// PUSHF = 0x9C,                // /*Push FLAGS onto stack*/
// RCL = 0xC0,                  // 0xC1 0xD0 0xD3 /*Rotate left (with carry)*/
// RCR = 0xC0,                  // 0xC1 0xD0 0xD3 /*Rotate right (with carry)*/
// REPxx = 0xF2,                // 0xF3 /*Repeat MOVS/STOS/CMPS/LODS/SCAS*/
// RETN = 0xC2,                    // 0xC3 /*Return from near procedure*/
// RETF = 0xCA,                    // 0xCB /*Return from far procedure*/
// ROL = 0xC0,                  // 0xC1 0xD0 0xD3 /*Rotate left*/
// ROR = 0xC0,                  // 0xC1 0xD0 0xD3 /*Rotate right*/
// SAHF = 0x9E,                 // /*Store AH into FLAGS*/
// SAL = 0xC0,                  	// 0xC1 0xD0 0xD3 /*Shift Arithmetically left (signed shift left)*/
// SAR = 0xC1,                  	// 0xC1 0xD0 0xD3 /*Shift Arithmetically right (signed shift right)*/
// SBB = 0x18,                  	// 0x1D 0x80 0x83 /*Subtraction with borrow*/
// SCASB = 0xAE,                // /*Compare byte string*/
// SCASW = 0xAF,                // /*Compare word string*/
// STC = 0xF9,                  // /*Set carry flag*/
// STD = 0xFD,                  // /*Set direction flag*/
// STI = 0xFB,                  // /*Set interrupt flag*/
// STOSB = 0xAA,                // /*Store byte in string*/
// STOSW = 0xAB,                // /*Store word in string*/
// JCXZ = 0xE3,                 // /*Jump if CX is zero*/
// ESC = 0xD8,                  // 0xDF /*Used with floating-point unit*/