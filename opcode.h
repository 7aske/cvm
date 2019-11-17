//
// Created by nik on 11/13/19.
//

#ifndef CVM_OPCODE_H
#define CVM_OPCODE_H

#pragma once

#include <stdint.h>


typedef enum opcodes {
	// AAA = 0x37,                  // /*ASCII adjust AL after addition*/
	// AAD = 0xD5,                  // /*ASCII adjust AX before division*/
	// AAM = 0xD4,                  // /*ASCII adjust AX after multiplication*/
	// AAS = 0x3F,                  // /*ASCII adjust AL after subtraction*/
	// ADC = 0x10,                  // 0x15 0x80 0x83 /*Add with carry*/
			ADD = 0x00,                    // 0x05 0x80 0x83 /*Add*/
	AND = 0x20,                    // 0x25 0x80 0x83 /*Logical AND*/
	CALL = 0x9A,                    // 0xE8 0xFF 0xFF /*Call procedure*/
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
			DEC = 0x48,                    // 0x4F 0xFE 0xFF /*Decrement by 1*/
	DIV = 0xF6,                    // 0xF7 /*Unsigned divide*/
	// ESC = 0xD8,                  // 0xDF /*Used with floating-point unit*/
			HLT = 0xF4,                    // /*Enter halt state*/
	// IDIV = 0xF7,                  // 0xF7 /*Signed divide*/
	// IMUL = 0x69,                  	// 0x6B 0xF6 0xF7 0x0F /*Signed multiply*/
	// IN = 0xE4,                   // 0xE5 0xEC 0xED /*Input from port*/
			INC = 0x40,                    // 0x47 0xFE 0xFF /*Increment by 1*/
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
			JE = 0x74,                        // Jump short if equal (ZF=1).
	JG = 0x7F,                        // Jump short if greater (ZF=0 and SF=OF).
	JGE = 0x7D,                    // Jump short if greater or equal (SF=OF).
	JL = 0x7C,                        // Jump short if less (SF<>OF).
	JLE = 0x7E,                    // Jump short if less or equal (ZF=1 or SF<>OF).
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
			JZ = 0x74,                        // Jump short if zero (ZF = 1).
	// JCXZ = 0xE3,                 // /*Jump if CX is zero*/
			JMP = 0xE9,                    // 0xEB 0xFF 0xFF /*Jump*/
	DUP = 0xE8,                    // 0xEB 0xFF 0xFF /*Jump*/
	// LAHF = 0x9F,                 // /*Load FLAGS into AH register*/
	// LDS = 0xC5,                  // /*Load pointer using DS*/
	// LEA = 0x8D,                  // /*Load Effective Address*/
	// LES = 0xC4,                  // /*Load ES with pointer*/
	// LOCK = 0xF0,                 // /*Assert BUS LOCK# signal*/
	// LODSB = 0xAC,                // /*Load string byte*/
	// LODSW = 0xAD,                // /*Load string word*/
	// LOOP = 0xE0,                 // 0xE2 /*Loop control*/
			MOV = 0xA0,                    // 0xA3 /*Move*/
	// MOVSB = 0xA4,                // /*Move byte from string to string*/
	// MOVSW = 0xA5,                // /*Move word from string to string*/
			MUL = 0x6B,                    // 0xF7 /*Unsigned multiply*/
	// NEG = 0xF7,                  	// 0xF7 /*Two's complement negation*/
			NOP = 0x90,                    // /*No operation*/
	NOT = 0xF7,                    // 0xF7 /*Negate the operand, logical NOT*/
	OR = 0x08,                    // 0x0D 0x80 0x83 /*Logical OR*/
	// OUT = 0xE6,                  // 0xE7 0xEE 0xEF /*Output to port*/
			POP = 0x07,                    // 0x0F 0x17 0x1F 0x58 0x5F 0x8F /*Pop data from stack*/
	// POPF = 0x9D,                 // /*Pop FLAGS register from stack*/
			PUSH = 0x06,                    // 0x0E 0x16 0x1E 0x50 0x57 0x68 0x6A 0xFF /*Push data onto stack*/
	// PUSHF = 0x9C,                // /*Push FLAGS onto stack*/
	// RCL = 0xC0,                  // 0xC1 0xD0 0xD3 /*Rotate left (with carry)*/
	// RCR = 0xC0,                  // 0xC1 0xD0 0xD3 /*Rotate right (with carry)*/
	// REPxx = 0xF2,                // 0xF3 /*Repeat MOVS/STOS/CMPS/LODS/SCAS*/
			RET = 0xCA,                            /*,//Return from procedure*/
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
			SHL = 0xD0,                    // 0xC1 0xD0 0xD3 /*Shift left (unsigned shift left)*/
	SHR = 0xD1,                    // 0xC1 0xD0 0xD3 /*Shift right (unsigned shift right)*/
	// STC = 0xF9,                  // /*Set carry flag*/
	// STD = 0xFD,                  // /*Set direction flag*/
	// STI = 0xFB,                  // /*Set interrupt flag*/
	// STOSB = 0xAA,                // /*Store byte in string*/
	// STOSW = 0xAB,                // /*Store word in string*/
			SUB = 0x28,                    // 0x2D 0x80 0x83 /*Subtraction*/
	TEST = 0x84,                    // 0x84 0xA8 0xA9 0xF6 0xF7 /*Logical compare (AND)*/
	// WAIT = 0x9B,                 // /*Wait until not busy*/
	// XCHG = 0x86,                 // 0x87 0x91 0x97 /*Exchange data*/
	// XLAT = 0xD7,                 // /*Table look-up translation*/
			XOR = 0x30,                    // 0x35 0x80 0x83 /*Exclusive OR*/
	PUT = 0xFA,
	PUTC = 0xFB,
	STOR = 0xFC,
	LOAD = 0xFD,
	SWAP = 0x56

} opcode_t;


static opcode_t decode(uint8_t* code) {
	opcode_t opcode = *code;
	return opcode;
}

#include <stdio.h>

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

extern char* mnemonic(opcode_t opcode) {
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
