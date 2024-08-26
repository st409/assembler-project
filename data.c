#include "data.h"

dataTable* createdata(char code[WORD_LEN])
{
    dataTable* data = malloc(sizeof(dataTable)); /* Allocate memory space for a new dataTable node */

    if (!data) /* Check if memory allocation failed */
    {
        return NULL; /* Return NULL if memory allocation failed */
    }

    strcpy(data->dataCode, code); /* Copy the code into the new dataTable node */
    data->nextData = NULL; /* Initialize the nextData pointer to NULL */
    return data;
}

void addData(dataTable** datatbl, char code[WORD_LEN])
{
    dataTable* data = createdata(code); /* Create a new dataTable node with the given code */

    if (*datatbl != NULL)
    {
        dataTable* current = *datatbl;

        /* goes to the end of the linked list */
        while (current->nextData != NULL)
        {
            current = current->nextData;
        }

        current->nextData = data; /* Append the new node to the end of the list */
    }
    else
    {
        *datatbl = data; /* Set the head of the list to the new node if the list is empty */
    }
}

void freeDataTable(dataTable* datatbl)
{
    free(datatbl); /* Free the memory allocated for the dataTable node */
}

void printlist_data(dataTable* head)
{
    dataTable* temp = head;

    printf("*********************this is printlist_data********************\n\n");

    /*print each dataTable node in the list */
    while (temp != NULL)
    {
        printf("CODE IS : %s\n", temp->dataCode);
        temp = temp->nextData;
    }

    printf("\n\n\n");
}

