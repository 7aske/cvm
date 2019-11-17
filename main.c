#include <stdlib.h>


// Enable VM_TRACE to see the stack and opcode values per instruction cycle
// #define VM_TRACE 1
// #define TRACE_CHAR 1

#include "opcode.h"
#include "vm.h"


int main() {
	uint8_t code[] = {
			// Fibonacci numbers

			// Store first two fib numbers(1, 1) to data stack.
			PUSH, 0x00, 0x00, 0x00, 0x01,
			STOR,
			PUSH, 0x00, 0x00, 0x00, 0x01,
			STOR,

			// Push iterator and condition to the stack
			PUSH, 0x00, 0x00, 0x00, 0x10,
			PUSH, 0x00, 0x00, 0x00, 0x00,

			// Load last two fibonacci numbers and push them back to data stack
			LOAD,
			DUP,
			LOAD,
			ADD,
			PUT,
			SWAP,
			STOR,
			STOR,

			// Increment the iterator and jump back if it is less than the condition
			INC,
			JL, 0x00, 0x00, 0x00, 0x16,
			NOP, NOP, NOP,
			// end Fibonacci numbers

			// \0 terminated "Hello World"
			PUSH, 0x00, 0x00, 0x00, 0x00, // \0
			PUSH, 0x00, 0x00, 0x00, 0x0a, // \n
			PUSH, 0x00, 0x00, 0x00, 0x21, // !
			PUSH, 0x00, 0x00, 0x00, 0x64, // d
			PUSH, 0x00, 0x00, 0x00, 0x6c, // l
			PUSH, 0x00, 0x00, 0x00, 0x72, // r
			PUSH, 0x00, 0x00, 0x00, 0x6f, // o
			PUSH, 0x00, 0x00, 0x00, 0x57, // W
			PUSH, 0x00, 0x00, 0x00, 0x20, // \s
			PUSH, 0x00, 0x00, 0x00, 0x6f, // o
			PUSH, 0x00, 0x00, 0x00, 0x6c, // l
			PUSH, 0x00, 0x00, 0x00, 0x6c, // l
			PUSH, 0x00, 0x00, 0x00, 0x65, // e
			PUSH, 0x00, 0x00, 0x00, 0x48, // H

			// \0 Used to compare if we had reach the end of the string
			PUSH, 0x00, 0x00, 0x00, 0x00,

			// Store /0 to use for comparison after printing next character
			STOR,

			// Print char and remove it from the stack
			PUTC,
			POP,

			// Load /0 and preform comparison
			LOAD,
			JL, 0x00, 0x00, 0x00, 0x72,

			NOP, NOP, NOP,
			HLT,
	};

	uint8_t* codeptr = malloc(sizeof(code));
	memcpy(codeptr, code, sizeof(code));
	VM* vm = vm_new(codeptr, sizeof(code) / sizeof(uint8_t));
	vm_run(vm);

	return 0;
}