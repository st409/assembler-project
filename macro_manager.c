#include "macro_manager.h"

macroTable* createMacro(char* name)
{

    macroTable* macro = malloc(sizeof(macroTable));
    if (!macro) /*No space found in memory*/
    {
        return NULL;
    }

    macro->macroName = (char*)malloc(strlen(name) + 1);
    if ((macro->macroName) == NULL)/*Checks if the assignment was successful*/
    {
        printf("no allocation");
        exit(0);
    }

    strcpy(macro->macroName, name);
    macro->macroValue = NULL;
    macro->nextMacro = NULL;
    return macro; 
}


void addMacro(macroTable** macrotbl, char* macroName)
{
    macroTable* macro = createMacro(macroName);
    if (*macrotbl != NULL)
    {
        macroTable* current = *macrotbl;
        while (current->nextMacro != NULL)
        {
            current = current->nextMacro;
        }
        current->nextMacro = macro;
    }
    else
    {
        *macrotbl = macro;
    }
}


void freeTable(macroTable* macrotbl)
{
    free(macrotbl->macroName);
    free(macrotbl->macroValue);
    free(macrotbl);
}

void  setValue(macroTable* macrotbl, char* value, char c)
{
    macroTable* temp = macrotbl;
    char* temp2;
    while ((temp->nextMacro) != NULL)
    {
        temp = temp->nextMacro;
    }
    if (c == 'y')
    {
        temp->macroValue = (char*)malloc(strlen(value) + 1);
        if ((temp->macroValue) == NULL)/*Checks if the assignment was successful*/
        {
            printf("no allocation");
            exit(0);
        }

        strcpy(temp->macroValue, value);
        /*temp->macroValue=value;*/
    }
    else
    {
        temp2 = (char*)realloc((temp->macroValue), strlen(value) + 1000000);
        if (temp2 == NULL)/*Checks if the assignment was successful*/
        {
            printf("no allocation");
            free(temp->macroValue);
            exit(0);
        }
        temp->macroValue = temp2;

        /*strcat(temp->macroValue, "\n");*/
        strcat(temp->macroValue, value);

    }

}

void printlist_macro(macroTable* head)
{
    macroTable* temp = head;
    while (temp != NULL)
    {
        printf("NAME IS : %s\n", temp->macroName);
        printf("VALUE IS : %s\n\n", temp->macroValue);
        temp = temp->nextMacro;
    }
}
