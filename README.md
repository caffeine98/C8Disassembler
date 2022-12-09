# C8Disassembler
A simple disassembler for the CHIP-8.
The program will take in the name of a CHIP-8 ROM file via command line argument, and print out the disassembly contents, including program counter, opcodees as well as an equivalent C psudocode if applicable

# Usage
You can build using the Visual Studio solution. Alternatively you could pluck the source files and build manually using your favourite compiler. There are no external dependencies in this project.
```
./C8Disassembler.exe <CHIP8_ROM>.ch8
```

# References used
- http://emulator101.com/
- https://en.wikipedia.org/wiki/CHIP-8
