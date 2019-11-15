#include <stdlib.h>

#define VM_TRACE
#define TRACE_CHAR

#include "opcode.h"
#include "vm.h"


int main() {
	uint8_t code[] = {
			PUSH, 0x00, 0x00, 0x00, 0x48,
			PUSH, 0x00, 0x00, 0x00, 0x65,
			PUSH, 0x00, 0x00, 0x00, 0x6c,
			PUSH, 0x00, 0x00, 0x00, 0x6c,
			PUSH, 0x00, 0x00, 0x00, 0x6f,
			PUSH, 0x00, 0x00, 0x00, 0x20,
			INC,
			PUSH, 0x00, 0x00, 0x00, 0x57,
			PUSH, 0x00, 0x00, 0x00, 0x6f,
			PUSH, 0x00, 0x00, 0x00, 0x72,
			PUSH, 0x00, 0x00, 0x00, 0x6c,
			PUSH, 0x00, 0x00, 0x00, 0x64,
			PUSH, 0x00, 0x00, 0x00, 0x0a,
			ADD,
			PUT,
			NOP,NOP,NOP,
			HLT,
	};
	// uint8_t code[] = {
	// 		PUSH, 0x00, 0x00, 0x00, 0x48,
	// 		PUSH, 0x00, 0x00, 0x00, 0x00,
	// 		AND,
	// 		HLT,
	// };

	uint8_t* codeptr = malloc(sizeof(code));
	memcpy(codeptr, code, sizeof(code));
	VM* vm = vm_new(codeptr, sizeof(code) / sizeof(uint8_t));
	vm_run(vm);

	return 0;
}