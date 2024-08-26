#ifndef MACRO_MANAGER_H
#define MACRO_MANAGER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*Typedef for the linked list each cell in the list has a macro property*/
typedef struct macro
{
    char* macroName; /*Pointer to the macro name*/
    char* macroValue; /*Pointer to the macro value*/
    struct macro* nextMacro; /*Pointer to the next macro*/
}macroTable;


/******************************************************************************
The function accepts a pointer to a macro name.
The function creates a cell type variable in a linked list of macros, initializes the macro name according to the received parameter and the macro value to be NULL.
The function returns a pointer to the new macro it created.
*******************************************************************************/
macroTable* createMacro(char* macroName);

/******************************************************************************
The function receives a pointer to the top of the linked macro list and a pointer to the macro name.
The function calls the createMacro operation which creates a new macro and then adds the new macro to the end of the linked list.
*******************************************************************************/
void addMacro(macroTable** macrotbl, char* macroName);

/******************************************************************************
The function frees the memory of the linked list
*******************************************************************************/
void freeTable(macroTable* macrotbl);

/******************************************************************************
The function receives a pointer to the top of the linked macro list, a pointer to the string line it wants to add to the macro value 
and a character that represents whether the macro value is empty or full.
The function adds the received string line as a parameter to the last macro value in the list.
*******************************************************************************/
void setValue(macroTable* macrotbl, char* value, char c);

/******************************************************************************
The function receives a pointer to the top of the linked list.
The function prints the list.
*******************************************************************************/
void printlist_macro(macroTable* head);

#endif

