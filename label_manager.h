#ifndef LABEL_MANAGER_H
#define LABEL_MANAGER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*Typedef for the linked list Each cell in the list has a label property*/
typedef struct label
{
    char* labelName; /*Pointer to the label name*/
    unsigned int labelAddress;/*A pointer to the label address*/
    int labelType; /*Pointer to label type (instruction/prompt)*/
    int externLabel; /*Pointer to label type (external/internal)*/
    struct label* nextLabel; /*Pointer to the next label*/
}labelTable;

/*Variables that represent the type of label (prompt/instruction)*/
enum type { instruction, prompt, unknown };
/*Variables that represent the type of label (external/internal)*/
enum ext { start, external, internal };


/******************************************************************************
The function accepts a pointer to a label name, label address and label type.
The function creates a cell type variable in a linked list of labels and initializes the attributes according to the received parameters.
The function returns a pointer to the new label it created.
*******************************************************************************/
labelTable* createLabel(char* name, unsigned int address, int lblType);

/******************************************************************************
The function receives a pointer to the top of the linked list of labels, a pointer to label name, label address and label type.
The function calls the createLabel operation which creates a new label and then adds the new label to the end of the linked list.
*******************************************************************************/
void addLabel(labelTable** labeltbl, char* name, unsigned int address, int lblType);

/******************************************************************************
The function frees the memory of the linked list.
*******************************************************************************/
void freeLabelTable(labelTable* labeltbl);

/******************************************************************************
The function receives a pointer to the top of the linked list of labels and a value it wants to add to the address of the labels.
The function adds the value received as a parameter to all the addresses of the prompt type labels.
*******************************************************************************/
void  setAddress(labelTable* labeltbl, int ic);

/******************************************************************************
The function receives a pointer to the top of the linked list, a pointer to the name of the label and a number representing the label type (external/internal).
The function locates the label with the name received as a parameter 
and updates the type of this label to be according to the type of label received as a parameter.
*******************************************************************************/
void  setExtern(labelTable* labeltbl, char* name, int a);

/******************************************************************************
The function receives a pointer to the head of the linked list and a pointer to the name of the label.
The function locates the label with the name received as a parameter and returns 1 if this label is of external type, otherwise returns 0.
*******************************************************************************/
int is_extern(labelTable* head, char* label);

/******************************************************************************
The function receives a pointer to the head of the linked list and a pointer to a label name.
The function returns 1 if a label with this name exists in the list, otherwise returns 0.
*******************************************************************************/
int find_label(labelTable* head, char* label);

/******************************************************************************
The function receives a pointer to the head of the linked list and a pointer to a label name.
The function locates the label whose name is the same as the name received as a parameter and returns the address of the label.
*******************************************************************************/
int find_adress_label(labelTable* head, char* label);

/******************************************************************************
The function receives a pointer to the top of the linked list.
The function prints the list.
*******************************************************************************/
void printlist(labelTable* head);

#endif

