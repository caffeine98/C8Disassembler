#include "Disassemblerr.h"

#include <stdio.h>
#include <stdint.h>

void DisassembleChip8(char* buffer, int pc) {
	uint8_t* code = &buffer[pc];
	uint8_t firstNibble = code[0] >> 4;
	uint8_t secondNibble = code[0] & 0xF;

	printf("%04x \t%02x \t%02x \t", pc, code[0], code[1]);
	switch (firstNibble) {
	case 0x0:
		//// Note: no need to decode 0NNN instruction
		switch ((code[1] & 0x0F)) {
		case 0x0:
			printf("opcode 00E0");
			printf("\tdisp_clear();");
			break;
		case 0xE:
			printf("opcode 00EE");
			printf("\treturn;");
			break;
		}
		break;

	case 0x1:
		printf("opcode 1NNN");
		printf("\tgoto 0x%X%X", secondNibble, code[1]);
		break;

	case 0x2:
		printf("opcode 2NNN");
		printf("\t*(0x%X%X)()", secondNibble, code[1]);
		break;

	case 0x3:
		printf("opcode 3XNN");
		printf("\tif (V%X == 0x%X)", secondNibble, code[1]);
		break;

	case 0x4:
		printf("opcode 4XNN");
		printf("\tif (V%X != 0x%X)", secondNibble, code[1]);
		break;

	case 0x5:
		printf("opcode 5XY0");
		printf("\tif (V%X == V%X)", secondNibble, code[1] >> 4);
		break;

	case 0x6:
		printf("opcode 6XNN");
		printf("\tV%X == 0x%X", secondNibble, code[1]);
		break;

	case 0x7:
		printf("opcode 7XNN");
		printf("\tV%X += 0x%X", secondNibble, code[1]);
		break;

	case 0x8:
		switch (code[1] & 0x0F) {
		case 0x0:
			printf("opcode 8XY0");
			printf("\tV%X = V%X", secondNibble, code[1] >> 4);
			break;
		case 0x1:
			printf("opcode 8XY1");
			printf("\tV%X |= V%X", secondNibble, code[1] >> 4);
			break;
		case 0x2:
			printf("opcode 8XY2");
			printf("\tV%X &= V%X", secondNibble, code[1] >> 4);
			break;
		case 0x3:
			printf("opcode 8XY3");
			printf("\tV%X ^= V%X", secondNibble, code[1] >> 4);
			break;
		case 0x4:
			printf("opcode 8XY4");
			printf("\tV%X += V%X", secondNibble, code[1] >> 4);
			break;
		case 0x5:
			printf("opcode 8XY5");
			printf("\tV%X -= V%X", secondNibble, code[1] >> 4);
			break;
		case 0x6:
			printf("opcode 8XY6");
			printf("\tV%X >>= 1", secondNibble);
			break;
		case 0x7:
			printf("opcode 8XY7");
			printf("\tV%X = V%X - V%X", secondNibble, (code[1] >> 4), secondNibble);
			break;
		case 0xE:
			printf("opcode 8XYE");
			printf("\tV%X <<= 1", secondNibble);
			break;
		}
		break;

	case 0x9:
		printf("opcode 9XY0");
		printf("\tif (V%X != V%X)", secondNibble, code[1] >> 4);
		break;

	case 0xA:
		printf("opcode ANNN");
		printf("\tI = 0x%X%X", secondNibble, code[1]);
		break;

	case 0xB:
		printf("opcode BNNN");
		printf("\tPC = V0 + 0x%X%X", secondNibble, code[1]);
		break;

	case 0xC:
		printf("opcode CXNN");
		printf("\tV%x = rand() & 0x%X", secondNibble, code[1]);
		break;

	case 0xD:
		printf("opcode DXYN");
		printf("\tdraw(V%X, V%X, 0x%X)", secondNibble, code[1] >> 4, code[1] & 0x0F);
		break;

	case 0xE:
		switch (code[1]) {
		case 0x9E:
			printf("opcode EX9E");
			printf("\tif (key() == V%X)", secondNibble);
			break;
		case 0xA1:
			printf("opcode EXA1");
			printf("\tif (key() != V%X)", secondNibble);
			break;
		}
		break;

	case 0xF:
		switch (code[1]) {
		case 0x07:
			printf("opcode FX07");
			printf("\tV%X = get_delay()", secondNibble);
			break;
		case 0x0A:
			printf("opcode FX0A");
			printf("\tV%X = get_key()", secondNibble);
			break;
		case 0x15:
			printf("opcode FX15");
			printf("\tset_delay_timer(V%X)", secondNibble);
			break;
		case 0x18:
			printf("opcode FX18");
			printf("\tset_sound_timer(V%X)", secondNibble);
			break;
		case 0x1E:
			printf("opcode FX1E");
			printf("\tI += V%X", secondNibble);
			break;
		case 0x29:
			printf("opcode FX29");
			printf("\tI = sprite_address[V%X]", secondNibble);
			break;
		case 0x33:
			printf("opcode FX33");
			printf("\tset_BCD(V%X)", secondNibble);
			break;
		case 0x55:
			printf("opcode FX55");
			printf("\treg_dump(V%X, &I)", secondNibble);
			break;
		case 0x65:
			printf("opcode FX65");
			printf("\treg_load(V%X, &I)", secondNibble);
			break;
		}
		break;

	default: printf("NOP"); break;
	
	}
}