#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define WORD_LEN 15 /*A constant that represents the length of the coding word*/

/*Typedef for the linked list each cell in the list has a data codeword property */
typedef struct data
{
    char dataCode[WORD_LEN]; /*An array of size 15 that holds the data codeword word*/
    struct data* nextData; /*Pointer to the next data codeword*/
}dataTable;

/******************************************************************************
The function receives an array of size 15 containing the code word of the data.
The function creates a cell type variable in a linked list of the data encoding,
Initializes the coding attribute according to the received parameter and the pointer attribute to the next cell in the list which will be NULL.
The function returns a pointer to the new encoding cell it created.
*******************************************************************************/
dataTable* createdata(char* code);

/******************************************************************************
The function receives a pointer to the head of the linked data encoding list and a code word.
The function calls the createdata operation which creates a new encoding and then adds the new encoding to the end of the linked list.
*******************************************************************************/
void addData(dataTable** datatbl, char* code);

/******************************************************************************
The function frees the memory of the linked list
*******************************************************************************/
void freeDataTable(dataTable* datatbl);

/******************************************************************************
The function receives a pointer to the top of the linked list.
The function prints the list.
*******************************************************************************/
void printlist_data(dataTable* head);

#endif

