## Assembler Project
Overview
The Assembler Project is a tool designed to simplify the process of assembling code written in a custom assembly-like language. This project offers features for encoding instructions, handling parameters, and more.

## Features
Instruction Encoding: Efficiently encode assembly instructions with a custom format. The encoding process supports a 15-bit instruction set where specific bits are designated for fixed patterns, addressing methods, and opcodes.

Custom Assembly Language: Work with a custom assembly language that allows you to define and manipulate instructions and operands tailored to your needs.

Parameter Handling: Handle various types of parameters, including immediate values, register-based operands, and memory addresses, all while adhering to a defined bit pattern.

Debugging and Error Handling: Robust error handling and debugging support to ensure accurate instruction processing and to facilitate troubleshooting during development.

**Key Files**
 ```run ```: The compiled assembler executable
 ```makefile ```: Build configuration for the project
## Build the Project

To build the project, use the provided Makefile:
```bash
make
```

This will compile all the necessary files and create the shevy.as executable.

## Running the Project
To run the project, use the following command:
```bash
./run file1 file2 ... fileN 
```
Important Note on File Names:

When specifying input files, omit the .as suffix. The assembler will automatically add .as to the input file names. For example, to assemble a file named program.as, you should execute:

Input Files
Input files should be in .as format and must include valid assembly code that adheres to the specified language syntax.

## Output Files
For each input file, the assembler produces the following output files:

 ```.am ``` file: Contains the input file after macro expansion.
 ```.ob ``` file: The object file that includes the compiled machine code.
 ```.ent ``` file: Lists the entry points defined in the assembly code (if any).
 ```.ext ``` file: Details external references used in the assembly code (if any).
Examples of these output files can be found in the valid_inputs_examples/ directory.

## Binary Translation Process
During the assembly process, each instruction in the source code is converted into binary machine code through the following steps:

Instruction Encoding: Each instruction is transformed into binary, with both the operation code (opcode) and operands encoded based on the chosen addressing mode (e.g., immediate, direct, or indirect).

Label Resolution: Operands that are labels are replaced with their respective memory addresses from the symbol table. External references are noted and marked in the binary output.

A, R, E Fields: Each binary word includes A, R, and E fields to facilitate proper linkage and loading of the machine code.

## Error Handling
The assembler includes comprehensive error checking to identify and report issues such as syntax errors, undefined symbols, and other problems that arise during the assembly process.

## Memory Management
This project showcases advanced memory management techniques in C, including:

Efficient allocation and deallocation of memory
Effective use of dynamic memory allocation
Prevention of memory leaks through meticulous resource management
Optimization of data structures to reduce memory usage

