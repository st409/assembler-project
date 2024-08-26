#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define WORD_LEN 15 /*A constant that represents the length of the coding word*/


/*Typedef for the linked list Each cell in the list has a codeword property*/
typedef struct instructions
{
    char instructionsCode[WORD_LEN]; /*An array of size 15 that holds the code word*/
    struct instructions* nextInstructions; /*Pointer to the next codeword*/
}instructionsTable;

/******************************************************************************
The function receives an array of size 15 that contains the coding word.
The function creates a cell type variable in a linked list of the encodings, 
initializes the encoding attribute according to the received parameter and the pointer attribute to the next cell in the list to be NULL.
The function returns a pointer to the new encoding cell it created.
*******************************************************************************/
instructionsTable* createinstructions(char code[WORD_LEN]);

/******************************************************************************
The function receives a pointer to the top of the linked encoding list and a code word.
The function calls the createinstructions operation which creates a new encoding word and then adds the new encoding to the end of the linked list.
*******************************************************************************/
void addInstructions(instructionsTable** instructionstbl, char *code);

/******************************************************************************
The function frees the memory of the linked list
*******************************************************************************/
void freeInstructionsTable(instructionsTable* instructionstbl);

/******************************************************************************
The function receives a pointer to the top of the linked list.
The function returns the number of cells in the list.
*******************************************************************************/
int num_of_cells(instructionsTable* head);

/******************************************************************************
The function receives a pointer to the top of the linked list of encodings, an array that holds the encoding word 
and a variable that marks the location of the cell where you want to update the encoding word.
The function locates the cell in the list according to the received back parameter 
and then updates the coding word of this cell to be the coding word received as a parameter.
*******************************************************************************/
void setInstructions(instructionsTable* head, char code[WORD_LEN], int back);

/******************************************************************************
The function receives a pointer to the top of the linked list.
The function prints the list.
*******************************************************************************/
void printlist_instructions(instructionsTable* head);

#endif

