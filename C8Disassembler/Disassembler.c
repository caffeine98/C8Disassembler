#include "Disassemblerr.h"

#include <stdio.h>
#include <stdint.h>

void DisassembleChip8(char* buffer, int pc) {
	uint8_t* code = &buffer[pc];
	uint8_t firstNibble = code[0] >> 4;

	printf("%04x \t%02x \t%02x \t", pc, code[0], code[1]);
	switch (firstNibble) {
	case 0x0:
		//// Note: no need to decode 0NNN instruction
		switch ((code[1] & 0x0F)) {
		case 0x0:
			printf("opcode 00E0");
			break;
		case 0xE:
			printf("opcode 00EE");
			break;
		}
		break;

	case 0x1:
		printf("opcode 1NNN");
		printf("\tGOTO NNN");
		break;

	case 0x2:
		printf("opcode 2NNN");
		break;

	case 0x3:
		printf("opcode 3XNN");
		break;

	case 0x4:
		printf("opcode 4XNN");
		break;

	case 0x5:
		printf("opcode 5XY0");
		break;

	case 0x6:
		printf("opcode 6XNN");
		break;

	case 0x7:
		printf("opcode 7XNN");
		break;

	case 0x8:
		switch (code[1] & 0x0F) {
		case 0x0:
			printf("opcode 8XY0");
			break;
		case 0x1:
			printf("opcode 8XY1");
			break;
		case 0x2:
			printf("opcode 8XY2");
			break;
		case 0x3:
			printf("opcode 8XY3");
			break;
		case 0x4:
			printf("opcode 8XY4");
			break;
		case 0x5:
			printf("opcode 8XY5");
			break;
		case 0x6:
			printf("opcode 8XY6");
			break;
		case 0x7:
			printf("opcode 8XY7");
			break;
		case 0xE:
			printf("opcode 8XYE");
			break;
		}
		break;

	case 0x9:
		printf("opcode 9XY0");
		break;

	case 0xA:
		printf("opcode ANNN");
		break;

	case 0xB:
		printf("opcode BNNN");
		break;

	case 0xC:
		printf("opcode CXNN");
		break;

	case 0xD:
		printf("opcode DXYN");
		break;

	case 0xE:
		switch (code[1] & 0x00FF) {
		case 0x9E:
			printf("opcode EX9E");
			break;
		case 0xA1:
			printf("opcode EXA1");
			break;
		}
		break;

	case 0xF:
		switch (code[1] & 0x00FF) {
		case 0x07:
			printf("opcode FX07");
			break;
		case 0x0A:
			printf("opcode FX0A");
			break;
		case 0x15:
			printf("opcode FX15");
			break;
		case 0x18:
			printf("opcode FX18");
			break;
		case 0x1E:
			printf("opcode FX1E");
			break;
		case 0x29:
			printf("opcode FX29");
			break;
		case 0x33:
			printf("opcode FX33");
			break;
		case 0x55:
			printf("opcode FX55");
			break;
		case 0x65:
			printf("opcode FX65");
			break;
		}
		break;

	default: printf("NOP"); break;
	
	}
}