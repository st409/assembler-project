#include "label_manager.h"

labelTable* createLabel(char* name, unsigned int address, int lblType)
{
    labelTable* label = malloc(sizeof(labelTable)); /* Allocate memory space for a new label */

    if (!label) /* Check if memory allocation failed */
    {
        exit(0); /* Exit program if memory allocation failed */
    }

    label->labelName = (char*)malloc(strlen(name) + 1); /* Allocate memory for the label name */
    if (label->labelName == NULL)
    {
        printf("no allocation");
        exit(0); /* Exit program if memory allocation for the label name failed */
    }

    strcpy(label->labelName, name); /* Copy the label name into the allocated space */
    label->labelAddress = address;
    label->labelType = lblType; 
    label->externLabel = start;
    label->nextLabel = NULL;
    return label; 
}

void addLabel(labelTable** labeltbl, char* name, unsigned int address, int lblType)
{
    labelTable* label = createLabel(name, address, lblType); /* Create a new label */

    if (*labeltbl != NULL)
    {
        labelTable* current = *labeltbl;

        /* goes to the end of the linked list */
        while (current->nextLabel != NULL)
        {
            current = current->nextLabel;
        }

        current->nextLabel = label; /* Append the new label to the end of the list */
    }
    else
    {
        *labeltbl = label; /* Set the head of the list to the new label if the list is empty */
    }
}

void freeLabelTable(labelTable* labeltbl)
{
    free(labeltbl->labelName); /* Free the memory allocated for the label name */
    free(labeltbl); /* Free the memory allocated for the labelTable node */
}

void setAddress(labelTable* labeltbl, int ic)
{
    labelTable* temp = labeltbl;

    /* goes the list and update the address for labels of type 'prompt' */
    while (temp != NULL)
    {
        if (temp->labelType == prompt)
        {
            temp->labelAddress = temp->labelAddress + ic; /* Adjust the label address */
        }
        temp = temp->nextLabel;
    }
}

void setExtern(labelTable* labeltbl, char* name, int a)
{
    labelTable* temp = labeltbl;

    /* Find the label and set its externLabel field */
    while (temp != NULL)
    {
        if (!strcmp(temp->labelName, name))
        {
            if (a == 1)
                temp->externLabel = external; /* Set externLabel to 'external' */
            else if (a == 2)
                temp->externLabel = internal; /* Set externLabel to 'internal' */
            break;
        }
        temp = temp->nextLabel;
    }
}

int is_extern(labelTable* head, char* label)
{
    labelTable* temp = head;

    /* Check if the label is of type 'external' */
    while (temp != NULL)
    {
        if (!strcmp(temp->labelName, label))
        {
            if (temp->externLabel == external)
                return 1; /* Return 1 if the label is external */
        }
        temp = temp->nextLabel;
    }
    return 0; /* Return 0 if the label is not external */
}

int find_label(labelTable* head, char* label)
{
    labelTable* temp = head;

    /* Check if the label exists */
    while (temp != NULL)
    {
        if (!strcmp(temp->labelName, label))
            return 1; /* Return 1 if the label is found */
        temp = temp->nextLabel;
    }
    return 0; /* Return 0 if the label is not found */
}

int find_adress_label(labelTable* head, char* label)
{
    int address;
    labelTable* temp = head;

    /* Find the address of the specified label */
    while (temp != NULL)
    {
        if (!strcmp(temp->labelName, label))
            address = temp->labelAddress; /* Set the address if the label is found */
        temp = temp->nextLabel;
    }
    return address; /* Return the address of the label */
}

void printlist(labelTable* head)
{
    labelTable* temp = head;

    /* Print each labelTable node in the list */
    while (temp != NULL)
    {
        printf("NAME IS : %s\n", temp->labelName);
        printf("ADDRESS IS : %d\n", temp->labelAddress);
        printf("TYPE IS : %d\n", temp->labelType);
        printf("EXTERN IS : %d\n\n", temp->externLabel);
        temp = temp->nextLabel;
    }
}

