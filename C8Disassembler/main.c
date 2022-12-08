#define _CRT_SECURE_NO_WARNINGS

#include "Disassemblerr.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
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

	printf("pc \tcode[0] code[1] Opcode \t\tC-Pseudo\n");

	while (pc < (fSize + 0x200)) {
		DisassembleChip8(buffer, pc);
		pc += 2;
		printf("\n");
	}

	return EXIT_SUCCESS;
}