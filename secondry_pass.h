#ifndef SECONDRY_PASS_H
#define SECONDRY_PASS_H

#include "help_functions.h"


/******************************************************************************
The function receives a pointer to a file name, a pointer to the top of the list of labels, a pointer to the top of the list of encodings, 
the number of instruction lines, the number of instruction lines and a pointer to the top of the data encoding list.
The function opens the file that contains this name with the extension am and makes a second pass. 
At the end the function creates files with the extension ob, ent and ext.
*******************************************************************************/
void second(char* file_name, labelTable* head, instructionsTable* insteruction_head, int last_IC, int last_DC, dataTable* data_head);


/******************************************************************************
The function receives every 3 bits and converts them to a number in base 10 (the maximum number will be 7)
*******************************************************************************/
int three_bit_binary_to_decimal(const char *three_bit_binary);


/******************************************************************************
The function accepts a number in base 2 with 15 bits and returns an array in length 5 that contains the octal number
*******************************************************************************/
int *binary_15bit_to_decimals(const char *binary_15bit);
#endif
