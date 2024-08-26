#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "data.h"
#include "instruction.h"
#include "label_manager.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BYTE 8
#define LABEL_LENGTH 31  	/*the vaild length of label*/
#define NUM_OF_FUNC 16   	/*the number of function that exit */
#define NUM_OF_REGIST 8 	/*the number of register that exit */
#define LINE_LEN 82      	/*the vaild length of line*/
#define DATA_LEN 4       	/*the length of the word data*/
#define STRING_LEN 6     	/*the length of the word string*/
#define ENTRY_LEN 5      	/*the length of the word entry*/
#define EXTERN_LEN 6     	/*the length of the word extern*/
#define REGISTER_LEN 3   	/*the max length of register*/
#define WORD_LEN 15      	/*The length of a binary coded word*/
#define ENDMACR_LEN 7     	/*the length of the word endmacr*/
#define MACR_LEN 4        	/*the length of the word macr*/
#define MIN_DATA_NUMBER -16384   /*The largest number that can be coded in 15 bits in a binary base*/
#define MAX_DATA_NUMBER 16384    /*The smallest number that can be coded in 15 bits in a binary base*/
#define MIN_NUMBER -2048        /*The largest number that can be coded in 12 bits in a binary base*/
#define MAX_NUMBER 2047         /*The largest number that can be coded in 12 bits in a binary base*/
#define START_IC 100            /*The initial value of the IC*/
#define START_DC 0              /*The initial value of the DC*/
#define NUM_MOV 0               /*The opcode of mov*/
#define NUM_CMP 1               /*The opcode of cmp*/
#define NUM_LEA 4               /*The opcode of lea*/
#define NUM_NOT 6               /*The opcode of not*/
#define NUM_JMP 9               /*The opcode of jmp*/
#define NUM_BNE 10              /*The opcode of bne*/
#define NUM_PRN 12              /*The opcode of prn*/
#define NUM_JSR 13              /*The opcode of jsr*/
#define NUM_RTS 14              /*The opcode of rts*/
#define NUM_STOP 15             /*The opcode of stop*/
#define FIND_ERROR 100          /*flag of error */
#define FIRST_LINE_NUMBER 100   /*The minimum number of lines of code that can be*/
#define MAX_NAME_FILE 20        /*The maximum length of the file*/
#define MAX_CODE_LINE 4096       /*Maximum possible lines of code*/


/******************************************************************************
The function receives a pointer to the captured command line .
The function replaces all tab characters in the line with spaces.
*******************************************************************************/
void replace_tab_in_space(char command_line[]);


/******************************************************************************
The function receives a pointer to the captured command line .
The function checks that there are no 2 consecutive commas,
 if there are the function returns 1 otherwise the function returns 0
*******************************************************************************/
int two_comma(char command_line_help []);



/*******************************************************************************************
The function receives a pointer to the label and line where the program is currently located
The function checks that the size of the label is not larger than 31,
 that it contains only letters and numbers, and that it starts with a letter.
********************************************************************************************/
int legal_label(char cp[LABEL_LENGTH],int count_line);




/******************************************************************************
The function receives a name and a pointer to an array of function names.
 And the function checks if the name exists in the array.
If so the function returns 1 otherwise it returns 0
*******************************************************************************/
int find_name_func(char* name, char* func[NUM_OF_FUNC]);







/******************************************************************************
The function receives a name and a pointer to an array of function names. 
And the function checks if the name exists in the array
If so the function returns the position of the name in the array
*******************************************************************************/
int find_index_func(char* name, char* func[NUM_OF_FUNC]);







/************************************************************************************
The function receives a pointer and checks if there is a command line in front of it, 
if so the function returns 1 otherwise the function returns 0
************************************************************************************/
int is_directive_command(char* cp);






/******************************************************************************************************************************
The function receives a number and a pointer to the list of instructions
The function converts the number to a binary code and stores it in a string of length 15
The function then adds the code to the list of instructions
*******************************************************************************************************************************/
void binary(short binar, instructionsTable** insteruction_head);





/******************************************************************************************************************************
The function receives a number and a pointer to the data list
The function converts the number to a binary code and stores it in a string of length 15
The function then adds the code to the data list
*******************************************************************************************************************************/
void binary_data(short binar, dataTable** data_head);





/******************************************************************************************************************************
The function receives a function number and 2 parameters
and points to a linked list of instructions
The function identifies for each parameter whether it is a register number or a label 
and sends it to a function that encodes it accordingly .
At this point if the function found a label it will encode it with question marks.
*******************************************************************************************************************************/

void tow_parameter(int str1, char str2[], char str3[], instructionsTable** insteruction_head);





/******************************************************************************************************************************
The function receives a string and a pointer to the data function.
The function sends to a function that encodes each character in the string and adds it to the data table
*******************************************************************************************************************************/
void string_code(char* string, dataTable** data_head);





/******************************************************************************************************************************
The function receives a function number and a parameter and points to a linked list of instructions
The function identifies for the parameter whether it is a register number or a label
and sends it to the function that encodes it accordingly and then adds it to the linked list of instructions
At this point if the function found a label it will encode it with question marks
*******************************************************************************************************************************/
void one_parameter(int str1, char str2[], instructionsTable** insteruction_head);




/******************************************************************************************************************************
The function receives an array of numbers, the length of the array and a pointer to the data function.
The function sends to a function that encodes each number in the array and adds it to the data table.
*******************************************************************************************************************************/
void data_code(int arr[], int length, dataTable** data_head);




/******************************************************************************************************************************
The function receives a function number and a pointer to a linked list of instructions 
and sends it to a function that encodes it accordingly and then adds it to the linked list of instructions
*******************************************************************************************************************************/
void zero_parameter(int str1, instructionsTable** insteruction_head);





/******************************************************************************************************************************
The function receives a pointer to a number, a number,length of the number. and a line number.
 The function checks whether the number is valid, that is, whether it is an integer. 
If so, the function will return 1, otherwise the function will return 0.
*******************************************************************************************************************************/
int Invaild_number_of_data(char cp[], int number, int count_line);




/******************************************************************************************************************************
The function receives a label name, a pointer to the symbol table, a line number, and a pointer to the instruction table
The function checks if the label exists, otherwise an error will be printed  and return 0  
Otherwise you will update the address of the label in the instruction table according to the symbol table and return 1
*******************************************************************************************************************************/
int update_adress_label(char label_name[NUM_OF_FUNC], labelTable* head, int count_line, instructionsTable** insteruction_head, int L);




/******************************************************************************************************************************
The function receives a label name, a pointer to the symbol table, a line number, and a pointer to the instruction table
The function checks if the label exists, otherwise it will print an error and return 0 Otherwise return 1
*******************************************************************************************************************************/
int is_exist_label(char label_name[NUM_OF_FUNC], labelTable* head, int count_line);



/******************************************************************************************************************************
The function receives a number that it will convert to binary
In addition, it receives a pointer to the linked list of instructions
and a number that represents a place in the list where the function wants to update the binary code of a certain word
*******************************************************************************************************************************/
void set_binary(short binar, instructionsTable** insteruction_head, int back);



/******************************************************************************************************************************
The function receives a line number and a pointer to the number which is the second parameter in the jump. 
The function finds the number and sends it to a function that checks if the number is valid
If so the function will return 1 otherwise the function will return 0.
*******************************************************************************************************************************/
int find_number_kfiza(char* cp, int count_line);




/******************************************************************************************************************************
The function receives a line number and a pointer to the number that is the first parameter before the comma. 
The function finds the pointer to the number and sends it to the function that checks if the number is valid
If so the function will return 1 otherwise the function will return 0
*******************************************************************************************************************************/
int find_number_before_comma(char* cp, int count_line);




/******************************************************************************************************************************
The function receives a line number and a pointer to the number which is the second parameter found before the end of the line. 
The function finds the pointer to the number and sends it to the function that checks if the number is valid
If so the function will return 1 otherwise the function will return 0
*******************************************************************************************************************************/
int find_number(char* cp, int count_line);




/******************************************************************************************************************************
The function receives a line number and a pointer to the label which is the second parameter at the end of the line.
 The function finds the pointer to the label and sends it to the function that checks whether the label is valid
If so the function will return 1 otherwise the function will return 0
*******************************************************************************************************************************/
int find_end_label(char* cp, int count_line);




/******************************************************************************************************************************
The function receives a line number and a pointer to the label which is the first parameter that is before a comma. 
The function finds the pointer to the label and sends it to the function that checks whether the label is valid
If so the function will return 1 otherwise the function will return 0
*******************************************************************************************************************************/
int find_label_before_comma(char* cp, int count_line);



/******************************************************************************************************************************
The function accepts a pointer to a label ,length of a label and a line number
The function checks if the label is valid, if so the function returns 1, otherwise it returns 0
*******************************************************************************************************************************/
int Invaild_label(char cp[], int length, int count_line);



/******************************************************************************************************************************
The function receives a pointer to a number, a number,length of the number. and a line number.
 The function checks whether the number is valid, that is, whether it is an integer. 
If so, the function will return 1, otherwise the function will return 0.
*******************************************************************************************************************************/
int Invaild_number(char cp[], int number, int length, int count_line);





/******************************************************************************
The function receives a line number and a number representing the error.
The function prints the appropriate error.
*******************************************************************************/
int printError(int error, int count_line);


#endif
