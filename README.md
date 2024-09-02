# Assembler Project Overview

## Features

- **Macro Handling:** Efficiently processes and replaces macros within source code.
- **Dual-Pass Assembly:** Performs assembly in two distinct stages to ensure accuracy.
- **Extensive Testing:** Comprehensive testing to validate the correctness of the assembly process.
- **Flexible Addressing:** Supports various addressing methods for instruction operands.
- **Output Files:** Produces object files (.ob), entry files (.ent), and external reference files (.ext).
- **Error Reporting:** Detects and reports issues encountered during assembly.
- **Advanced Memory Management:** Uses sophisticated techniques in C for managing memory effectively.

## Project Organization
. ├── src/ # Source code files │ ├── assembler/ # Main assembler implementation │ ├── processing/ # Code for handling the assembly process │ └── validation/ # Code for validating and error-checking ├── examples/ # Example input files │ ├── valid/ # Examples of correctly formatted input files │ └── invalid/ # Examples of incorrectly formatted input files ├── include/ # Header files and definitions └── build/ # Build artifacts and outputs


## Key Files

- `assembler.exe`: The executable file for running the assembler.
- `makefile`: Build script for compiling the project.

## Building the Project

To compile the project, run:

```bash
make
This command will compile the source code and produce the assembler.exe executable.

Running the Assembler
Execute the assembler with:

./assembler <file1> <file2> ... <fileN>
Note on File Extensions:
Do not include the .as suffix when specifying input files. The assembler will automatically append .as to the filenames. For example, to assemble a file named program.as, use:

./assembler program
Input Files
Input files should end with a .as extension and follow the assembly language syntax rules. Valid and invalid input file examples can be found in the examples/valid/ and examples/invalid/ directories.

Output Files
For each input file, the assembler generates:

.am file: The file after macro processing.
.ob file: Contains the binary machine code generated from the assembly code.
.ent file: Lists entry points defined in the assembly code (if applicable).
.ext file: Details external symbols referenced in the assembly code (if applicable).
Examples of these output files are located in the examples/valid/ directory.

Assembly Process
The assembly process involves:

Binary Encoding: Converts each instruction into binary code, encoding opcodes and operands based on the addressing mode used (e.g., immediate, direct, indirect).
Symbol Resolution: Replaces labels with memory addresses from the symbol table and marks external references appropriately.
Field Encoding: Each instruction word includes specific fields relevant for linking and loading stages.
Error Handling
The assembler includes robust error checking to identify and report syntax errors, undefined symbols, and other issues. Error examples for incorrect inputs are available in the examples/invalid/ directory.

Memory Management
The project illustrates advanced memory management techniques in C:

Efficient allocation and deallocation of memory
Effective dynamic memory use
Prevention of memory leaks through careful management
Optimized data structures to reduce memory footprint
