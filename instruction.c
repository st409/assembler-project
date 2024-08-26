#include "instruction.h"

instructionsTable* createinstructions(char code[WORD_LEN])
{
    instructionsTable* instructions = malloc(sizeof(instructionsTable)); /* Allocate memory for a new instructionsTable node */

    if (!instructions) /* Check if memory allocation failed */
    {
        return NULL; /* Return NULL if memory allocation failed */
    }

    strcpy(instructions->instructionsCode, code); /* Copy the code into the new instructionsTable node */
    instructions->nextInstructions = NULL; /* Initialize the nextInstructions pointer to NULL */
    return instructions;
}

void addInstructions(instructionsTable** instructionstbl, char code[WORD_LEN])
{
    instructionsTable* instructions = createinstructions(code); /* Create a new instructionsTable node with the given code */

    if (*instructionstbl != NULL)
    {
        instructionsTable* current = *instructionstbl;

        /* goes to the end of the linked list */
        while (current->nextInstructions != NULL)
        {
            current = current->nextInstructions;
        }

        current->nextInstructions = instructions; /* Append the new node to the end of the list */
    }
    else
    {
        *instructionstbl = instructions; /* Set the head of the list to the new node if the list is empty */
    }
}

void freeInstructionsTable(instructionsTable* instructionstbl)
{
    free(instructionstbl); /* Free the memory allocated for the instructionsTable node */
}

int num_of_cells(instructionsTable* head)
{
    int i = 0;
    instructionsTable* temp = head;

    /* Count the number of nodes in the linked list */
    while (temp != NULL)
    {
        i++;
        temp = temp->nextInstructions;
    }

    return i; /* Return the count of nodes */
}

void setInstructions(instructionsTable* head, char code[WORD_LEN], int back)
{
    int i = 0;
    instructionsTable* temp = head;

    /* goes to the node at the specified position from the end */
    while (i < back)
    {
        i++;
        temp = temp->nextInstructions;
    }

    strcpy(temp->instructionsCode, code); /* Set the code for the specified node */
}

void printlist_instructions(instructionsTable* head)
{
    instructionsTable* temp = head;

    printf("*********************this is printlist_instructions********************\n\n");

    /* print each instructionsTable node in the list */
    while (temp != NULL)
    {
        printf("CODE IS : %s\n", temp->instructionsCode);
        temp = temp->nextInstructions;
    }

    printf("\n\n\n");
}

