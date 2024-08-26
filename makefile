run: main.o help_functions.o data.o primary_pass.o instruction.o macro_manager.o macro_decoder.o secondry_pass.o label_manager.o
	gcc -g -ansi -pedantic -Wall main.o help_functions.o data.o primary_pass.o instruction.o macro_manager.o macro_decoder.o secondry_pass.o label_manager.o -o run
main.o: main.c macro_decoder.h
	gcc -c -ansi -pedantic -Wall main.c -o main.o
help_functions.o: help_functions.c help_functions.h
	gcc -c -ansi -pedantic -Wall help_functions.c -o help_functions.o
data.o: data.c data.h
	gcc -c -ansi -pedantic -Wall data.c -o data.o
primary_pass.o: primary_pass.c primary_pass.h
	gcc -c -ansi -pedantic -Wall primary_pass.c -o primary_pass.o
instruction.o: instruction.c instruction.h
	gcc -c -ansi -pedantic -Wall instruction.c -o instruction.o
macro_manager.o: macro_manager.c macro_manager.h
	gcc -c -ansi -pedantic -Wall macro_manager.c -o macro_manager.o
macro_decoder.o: macro_decoder.c macro_decoder.h
	gcc -c -ansi -pedantic -Wall macro_decoder.c -o macro_decoder.o
secondry_pass.o: secondry_pass.c secondry_pass.h
	gcc -c -ansi -pedantic -Wall secondry_pass.c -o secondry_pass.o
label_manager.o: label_manager.c label_manager.h
	gcc -c -ansi -pedantic -Wall label_manager.c -o label_manager.o

