
#include "macro_decoder.h"

void macro_retirement(FILE* as_file, char* as_name)
{
    FILE* am_file;
    macroTable* head = NULL;
    macroTable* temp;
    int i, count_line = 0, flag_error = 0, cheak_error = 0;
    int count = 0, printed = 0;
    char line[LINE_LEN];
    char in_macro = 0;
    char first_line_macro = 'y'; /*If the macro value is empty then the variable is equal to y, because the first line must be inserted into it, otherwise the variable is equal to n*/
    char* help_line;
    char* help_name;
    char* am_name = (char*)malloc((strlen(as_name) * sizeof(char)) + 1);/*Dynamically assigning a string*/
    char* func[NUM_OF_FUNC] = { "mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","red","prn","jsr","rts","stop" };
    char* regist[NUM_OF_REGIST] = { "r0", "r1","r2","r3","r4","r5","r6","r7" };
    if (am_name == NULL)/*Checks if the assignment was successful*/
    {
        printf("no allocation");
        exit(0);
    }
    strcpy(am_name, as_name);/*Copying the source file name to the am file name*/
    am_name[strlen(am_name) - 1] = 'm'; /*Update the file extension to be .am*/
    if ((am_file = fopen(am_name, "w")) == NULL)/*Checks if the file was opened successfully*/
    {
        fprintf(stderr, "Cannot open file %s\n", am_name);
        exit(0);
    }


    while (fgets(line, LINE_LEN, as_file) != NULL)/*Reading line by line from the source file*/
    {
        char name[LINE_LEN]={'\0'};
        if(flag_error!=0) /*Checking whether there was an error in the source file*/
           cheak_error=FIND_ERROR;
        flag_error=0;
        count_line++;
        help_line = line;
        while (isspace(*help_line))
        {
            ++help_line;
        }
        if (in_macro == 0) /*The current line is not inside a macro statement*/
        {
            printed = 0;
            if (!(strncmp(help_line, "macr", MACR_LEN)) && (isspace(*(help_line + MACR_LEN)))) /*We found the word macr, entering into a macro statement*/
            {
                in_macro = 1; /*Update on the status of inside macro*/
                help_line += MACR_LEN; /*Advancing the pointer that reads the line from the source file to be after the word macr*/
                while (isspace(*help_line))
                {
                    ++help_line;
                }
                help_name = help_line;/*Points to the beginning of the macro name*/
                count = 0;
                while (isalpha(*help_line) || isdigit(*help_line) || *help_line == '_')/*Receiving the name of the macro, by reading all the characters that
                                                                                        are count or a letter up to a white character*/
                {
                    ++help_line;
                    count++;
                }
                strncpy(help_name, help_line-count, count); /*Inserting the macro name into the help_name variable*/
                while(isspace(*(help_line)))
                      help_line++;
                if((*(help_line)!='\0')) /*Checking that after the macro name there are only white characters until the end of the line*/
                     flag_error = printError(5, count_line);
                for(i=0;i<16;i++)
                  if(!strncmp(help_name,func[i],strlen(func[i])))/*Checking that the macro name is not a function name*/
                  {
                      flag_error=printError(19,count_line);
                      break;
                  }

                for(i=0;i<8;i++)
                  if(!strncmp(help_name,regist[i],strlen(regist[i])))/*Checking that the macro name is not the name of a register*/
                  {
                      flag_error=printError(20,count_line);
                      break;
                  }
                strncpy(name,help_name,count); /*The macro name is valid, so we will put it in the name variable*/
                addMacro(&head, name); /*Adding the macro to the linked list of macros*/
                first_line_macro = 'y'; /*You need to add its value to the macro, now the value is empty, so we will initialize the variable first_line_macro to 
                                         be yes.*/
            }
            else /*The line is neither a line within a macro nor the beginning of a macro statement*/
            {
                temp = head; /*A variable that will point to the top of the macro list*/
                while ((temp) != NULL) /*Go through the entire linked list*/
                {
                    if (!strncmp(help_line, temp->macroName, strlen(temp->macroName)))/*Checking whether the line is the name of a macro and then the macro should
                                                                                        be undone*/
                    {
                        help_line += strlen(temp->macroName);
                        fprintf(am_file, "%s", temp->macroValue); /*Writing the macro value instead of the macro name*/
                        printed++; /*An update found in the name of a macro and we interpreted it*/
                        break;
                    }
                    else
                        temp = temp->nextMacro;
                }
                if (printed == 0)  /*If the line was not the name of a macro, copy the line as it is to the am file*/
                    fprintf(am_file, "%s", help_line);
            }
        }
        else /*The line is inside a macro*/
        {
            if (!strncmp(help_line, "endmacr", ENDMACR_LEN) && isspace(*(help_line + ENDMACR_LEN))) /*Checking whether the line is a macro termination statement*/
            {
                in_macro = 0; /*Update that are no longer inside a macro*/
                first_line_macro = 'y'; /*Preparing the first_line_macro variable for the next macro*/
                help_line+=ENDMACR_LEN;
                while(isspace(*(help_line)))
                      help_line++;
                if(*(help_line)!='\0') /*Checking that after the end of the macro, endmcr there are only white characters until the end of the line*/
                     flag_error = printError(5, count_line);
            }
            else /*The line is inside a macro*/
            {
                setValue(head, help_line, first_line_macro); /*You add the line to the macro value we are currently in*/
                if (first_line_macro == 'y') /*If this line was the first line in the macro, update the first_line_macro variable to equal no*/
                    first_line_macro = 'n';
            }
        }
    }
    if(flag_error!=0) /*Checking whether there were errors in the source file*/
           cheak_error=FIND_ERROR;

    free(am_name); /*Release the filename variable from memory*/
    free(head); /*Freeing the macro list from memory*/
    fclose(am_file); /*Closing the am file created by this function*/
    fclose(as_file); /*Closing the source file*/

   if(cheak_error==0) /*If there were no errors in the source file, then send the created am file to the first pass function*/
    first(as_name);
}
