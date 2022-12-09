#define _CRT_SECURE_NO_WARNINGS

#include "Disassembler.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Usage: ./%s <CHIP8_ROM>.ch8\n", "C8Disassembler.exe");
		return EXIT_FAILURE;
	}

	FILE* file = fopen(argv[1], "rb");
	printf("%s\n", argv[1]);
	printf("");
	if (!file) {
		fprintf(stderr, "Error opening ROM file\n");
		return EXIT_FAILURE;
	}

	fseek(file, 0L, SEEK_END);
	int fSize = ftell(file);
	fseek(file, 0L, SEEK_SET);

	char* buffer = (char*)malloc(fSize + 0x200);
	fread(buffer + 0x200, fSize, 1, file);
	fclose(file);

	int pc = 0x200;
	int num_of_lines = 0;
	printf("PC \tcode[0] code[1] Opcode \t\tC-Pseudo\n");

	while (pc < (fSize + 0x200)) {
		DisassembleChip8(buffer, pc);
		pc += 2;
		printf("\n");
		++num_of_lines;
	}

	printf("\nTotal number of lines: %d\n", num_of_lines);

	return EXIT_SUCCESS;
}