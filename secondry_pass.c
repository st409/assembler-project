#include "secondry_pass.h"


void second(char* file_name, labelTable* head, instructionsTable* insteruction_head, int last_IC, int last_DC, dataTable* data_head)
{
    int number_func, flag = 0, count_line = 0, flag_label = 0;
    labelTable* temp = head;  /*A pointer to the symbol table*/
    instructionsTable* temp_insteruction = insteruction_head; /*Pointer to the instruction table*/
    dataTable* temp_data = data_head; /*A pointer to the data table*/
    char* func[NUM_OF_FUNC] = { "mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","red","prn","jsr","rts","stop" };
    char line[LINE_LEN];
    char help_line[LINE_LEN];
    FILE* am_file;
    FILE* ob_file;
    FILE* ext_file;
    FILE* ent_file;
    char* am_name = (char*)malloc((strlen(file_name) * sizeof(char)) + 1);/*Dynamically assigning a string*/
    char* ob_name = (char*)malloc((strlen(file_name) * sizeof(char)) + 1);/*Dynamically assigning a string*/
    char* ext_name = (char*)malloc((strlen(file_name) * sizeof(char)) + 2);/*Dynamically assigning a string*/
    char* ent_name = (char*)malloc((strlen(file_name) * sizeof(char)) + 2);/*Dynamically assigning a string*/
    int IC = -1, i = 0;
    int flag_error = 0;  /*If there are mistakes count the number of mistakes otherwise enter 0*/
    int cheak_error = 0;
    int pos, pos1;
    int *decimal_array = (int*) malloc(5 * sizeof(int));

    if (am_name == NULL)/*Checks if the assignment was successful*/
    {
        printf("no allocation");
        exit(0);
    }
    strcpy(am_name, file_name); /*Copying the name of the source file to the am_name variable*/
    am_name[strlen(am_name) - 1] = 'm'; /*Changing the suffix from as to am*/
    if ((am_file = fopen(am_name, "r+")) == NULL)/*Checks if the file was opened successfully*/
    {
        fprintf(stderr, "Cannot open file %s\n", am_name);
        exit(0);
    }

    if (ob_name == NULL)/*Checks if the assignment was successful*/
    {
        printf("no allocation");
        exit(0);
    }
    strcpy(ob_name, file_name); /*Copying the name of the source file to the ob_name variable*/
    ob_name[strlen(am_name) - 2] = 'o';/*Changing the suffix from as to ob*/
    ob_name[strlen(am_name) - 1] = 'b';
    if ((ob_file = fopen(ob_name, "w")) == NULL)/*Checks if the file was opened successfully*/
    {
        fprintf(stderr, "Cannot open file %s\n", ob_name);
        exit(0);
    }

    if (ext_name == NULL)/*Checks if the assignment was successful*/
    {
        printf("no allocation");
        exit(0);
    }
    strncpy(ext_name, file_name, strlen(file_name)); /*Copying the name of the source file to the ext_name variable*/
    ext_name[strlen(file_name) - 2] = 'e'; /*Changing the suffix from as to ext*/
    ext_name[strlen(file_name) - 1] = 'x';
    ext_name[strlen(file_name)] = 't';
    ext_name[strlen(file_name) + 1] = '\0';
    if ((ext_file = fopen(ext_name, "w")) == NULL)/*Checks if the file was opened successfully*/
    {
        fprintf(stderr, "Cannot open file %s\n", ext_name);
        exit(0);
    }

    if (ent_name == NULL)/*Checks if the assignment was successful*/
    {
        printf("no allocation");
        exit(0);
    }
    strncpy(ent_name, file_name, strlen(file_name)); /*Copying the name of the source file to the ent_name variable*/
    ent_name[strlen(file_name) - 2] = 'e';/*Changing the suffix from as to ent*/
    ent_name[strlen(file_name) - 1] = 'n';
    ent_name[strlen(file_name)] = 't';
    ent_name[strlen(file_name) + 1] = '\0';
    if ((ent_file = fopen(ent_name, "w")) == NULL)/*Checks if the file was opened successfully*/
    {
        fprintf(stderr, "Cannot open file %s\n", ent_name);
        exit(0);
    }

    while (fgets(line, LINE_LEN, am_file) != NULL)
    {
        char label_name[LABEL_LENGTH] = { "\0" };
	char help1_label_name[LABEL_LENGTH] = { "\0" };
        char help_label_name[LABEL_LENGTH] = { "\0" };
        char second_name[LABEL_LENGTH] = { "\0" };
        char* cp;
        int count_register = 0;   /*Count the number of registers when there are 2 parameters*/
        int count_len_label = 0;   /*Count the length of the label*/
        if (flag_error != 0)
            cheak_error = FIND_ERROR;
        flag_error = 0;
        flag_label = 0; /*Its value is 1 if a label other than 0 is detected*/
        count_line++;  /*Count the number of rows*/
        replace_tab_in_space(line);
        if (*line != ';')
        {
            char* space = " ";
            char* colon = ":";
            strcpy(help_line, line);
            cp = strtok(help_line, space); /*Holds the pointer until a space*/
            if (is_directive_command(line) == 0 && find_name_func(cp, func) == 0) /*if it's label*/
            {
                strcpy(help_line, line);
                cp = strtok(help_line, colon);
                cp = cp + strlen(cp) + 1;
                flag_label = 1;
                while (isspace(*cp))
                    cp++;
            } /* end of if it's label*/
            if ((is_directive_command(cp) == 0 && find_name_func(cp, func) == 1) || (is_directive_command(cp) == 0 && flag_label == 1))
            { /*If you have reached the name of a function*/
                cp = strtok(cp, space);
                if (find_name_func(cp, func) == 0)
                {
                    if (cp[strlen(cp) - 1] == '\n')
                    {
                        cp[strlen(cp) - 1] = '\0';
                        if (find_name_func(cp, func) == 1)
                        {
                            flag = 1;
                        }
                    }
                }
                if (find_name_func(cp, func) == 1 || flag == 1)
                { /*If you did find the function name in the function array*/
                    IC++;
                    number_func = find_index_func(cp, func);
                    if (number_func == NUM_RTS || number_func == NUM_STOP) /*If it's a function that doesn't accept any parameters*/
                    {
                        cp = cp + strlen(cp) + 1;
                        while (isspace(*cp))
                            cp++;
                    }
                    else if (number_func >= NUM_MOV && number_func <= NUM_LEA)  /*If it is a function that accepts 2 parameters*/
                    {
                        if (number_func == NUM_LEA)  /*If it is function number 4*/
                        {  /* else 1*/
                            cp = cp + strlen(cp) + 1;
                            while (isspace(*cp))
                                cp++;
                            while (isalpha(*cp) || isdigit(*cp))
                            {
                                count_len_label++;
                                cp++;
                            }
                            strncpy(label_name, cp - count_len_label, count_len_label);/*put*/
                            IC++;
                            strcpy(help_label_name, label_name);
			    strcpy(help1_label_name, label_name);
                            if (update_adress_label(label_name, head, count_line, &insteruction_head, IC) == 1)   /*Checks that the label exists in the symbol table*/
                            {

                                if (is_extern(head, help_label_name)) /*Checks if the label is external*/
                                {
                                    setInstructions(insteruction_head, "000000000000001", IC);
                                     /*Writes the name of the label and its location to the file*/
                                    fprintf(ext_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER); 
                                }
				/*else if(is_intern(head, help_label_name))
			        {
                                     update_adress_label(help_label_name, head, count_line, &insteruction_head, IC);
                                     fprintf(ent_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                }*/
                                count_len_label = 0;

                                while (isspace(*cp))
                                    cp++;

                                cp++;
                                while (isspace(*cp))
                                    cp++;
                                if ((*cp) == 'r' && cp[1] >= '0' && cp[1] <= '7' && !isdigit(cp[2])) /*If it is a register*/
                                {
                                    cp += 2;
                                    while (isspace(*cp))
                                        cp++;
                                    IC++;
                                } 
				else if ((*cp) == '*' && cp[1] == 'r' && cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3])) /*If it is a register*/
                                {
                                    cp += 3;
                                    while (isspace(*cp))
                                        cp++;
                                    IC++;
                                } 
				
                                else  /*if it is label*/
                                {
                                    while (isalpha(*cp) || isdigit(*cp))
                                    {
                                        count_len_label++;
                                        cp++;
                                    }
                                    strncpy(label_name, cp - count_len_label, count_len_label);/*put*/
                                    IC++;
                                    strcpy(help_label_name, label_name);
				    strcpy(help1_label_name, label_name);
                                    if (update_adress_label(label_name, head, count_line, &insteruction_head, IC) == 1)
                                    {

                                        if (is_extern(head, help_label_name))
                                        {
                                            setInstructions(insteruction_head, "000000000000001", IC);
                                            fprintf(ext_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                        }
					/*else if(is_intern(head, help_label_name))
				        {
                                             update_adress_label(help_label_name, head, count_line, &insteruction_head, IC);
                                             fprintf(ent_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                        }*/
                                        count_len_label = 0;
                                    }
                                }
                                while (isspace(*cp))
                                    cp++;
                            } /*end of update_adress_label*/
                            else
                                flag_error++;
                        } /* end of else 1 */
/***************************************************************************************************************/
                        else /*if you dont func 4*/
                        {
                            int flag_number = 0;
                            cp = cp + strlen(cp) + 1;
                            while (isspace(*cp))
                                cp++;
                            if ((*(cp) == '#' && isdigit(cp[1]))) /*if it's a number*/
                            {
                                cp++; 
                                while (isdigit(*cp))
                                    cp++;
                                IC++;

                            }
                            else if (*(cp) == '#' && (cp[1] == '-' || cp[1] == '+') && isdigit(cp[2])) /*if it's a number*/
                            {
                                cp += 2;
                                while (isdigit(*cp))
                                    cp++;
                                IC++;
                            }
                            else  if ((*cp) == 'r' && cp[1] >= '0' && cp[1] <= '7' && !isdigit(cp[2])) /*if it's a register*/
                            {
                                cp += 2;
                                count_register++;
                                IC++;
                            }
		            else if ((*cp) == '*' && cp[1] == 'r' && cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3])) /*If it is a register*/
                            {
                                cp += 3;
                                count_register++;
                                IC++;
                            } 
                            else /*if it's a label*/
                            {
                                while (isalpha(*cp) || isdigit(*cp))
                                {
                                    count_len_label++;
                                    cp++;
                                }
                                strncpy(label_name, cp - count_len_label, count_len_label);
                                IC++;
                                strcpy(help_label_name, label_name);
				strcpy(help1_label_name, label_name);
                                if (update_adress_label(label_name, head, count_line, &insteruction_head, IC) == 1)
                                {
                                    if (is_extern(head, help_label_name))
                                    {
                                        setInstructions(insteruction_head, "000000000000001", IC);
                                        fprintf(ext_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                    }
				    /*else if(is_intern(head, help_label_name))
				    {
                                        update_adress_label(help_label_name, head, count_line, &insteruction_head, IC);
                                        fprintf(ent_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                    }*/
                                    count_len_label = 0;
                                }
                                else
                                    flag_error++;
                            }
                            if (flag_error == 0)
                            {
                                while (isspace(*cp))
                                    cp++;
                                cp++;
                                while (isspace(*cp))
                                    cp++;

                                if (number_func == 1)
                                {
                                    /* int flag_number=0;*/
                                    if (*(cp) == '#' && isdigit(cp[1])) /*if it's a number*/
                                    {
                                        cp++;
                                        while (isdigit(*cp))
                                            cp++;
                                        flag_number = 1;
                                        IC++;
                                    }
                                    else if (*(cp) == '#' && (cp[1] == '-' || cp[1] == '+') && isdigit(cp[2])) /*if it's a number*/
                                    {
                                        cp += 2;
                                        while (isdigit(*cp))
                                            cp++;
                                        flag_number = 1;
                                        IC++;
                                    }

                                } 
                                if ((*cp) == 'r' && cp[1] >= '0' && cp[1] <= '7' && flag_number == 0 && !isdigit(cp[2])) /*if it's a rgister*/
                                {
                                    strncpy(second_name, cp, 2);
                                    cp += 2;
                                    count_register++;
                                    while (isspace(*cp))
                                        cp++;

                                    if (count_register != 2)
                                        IC++;
                                }
				else if ((*cp) == '*' && cp[1] == 'r' && cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3])) /*If it is a register*/
                                {
				    strncpy(second_name, cp, REGISTER_LEN);
                                    cp += 3;
				    count_register++;
                                    while (isspace(*cp))
                                        cp++;
				    if (count_register != 2)
                                        IC++;
                                } 
                                else if (flag_number == 0) /*if it's a label*/
                                {
                                    while (((isalpha(*cp) || isdigit(*cp))) && flag_number == 0)
                                    {
                                        cp++;
                                        count_len_label++;
                                    }
                                    strncpy(label_name, cp - count_len_label, count_len_label);
                                    IC++;
                                    strcpy(help_label_name, label_name);
				    strcpy(help1_label_name, label_name);
                                    if (update_adress_label(label_name, head, count_line, &insteruction_head, IC) == 1)
                                    {
                                        
                                        if (is_extern(head, help_label_name))
                                        {
                                            setInstructions(insteruction_head, "000000000000001", IC);
                                            fprintf(ext_file, "%s\t%d\n",help1_label_name ,IC + FIRST_LINE_NUMBER);
                                        }
					/*else if(is_intern(head, help_label_name))
				        {
                                         update_adress_label(help_label_name, head, count_line, &insteruction_head, IC);
                                        fprintf(ent_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                        }*/
                                        count_len_label = 0;
                                    }
                                    else
                                        flag_error++;
                                }
                                while (isspace(*cp))
                                    cp++;
                            }/*end of flag_error*/
                        }
                    }

                    else/*if it is one parameter */
                    {
                        if (number_func == NUM_JMP || number_func == NUM_BNE || number_func == NUM_JSR)/*if it is jump*/
                        {
                            cp = cp + strlen(cp) + 1;
                            while (isspace(*cp))
                                cp++;
                            if ((*cp) == 'r' && cp[1] >= '0' && cp[1] <= '7' && !isdigit(cp[2])) /*if it's a register*/
                            {
                                cp = cp + 2;
                                while (isspace(*cp))
                                    cp++;
                                IC++;
                            } /*if it register*/
			    else if ((*cp) == '*' && cp[1] == 'r' && cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3])) /*If it is a *register*/
                            {
			        cp = cp + 3;
                                while (isspace(*cp))
                                    cp++;
                                IC++;
                             } 
                            else  /*if it's a label*/
                            {
                                while (((isalpha(*cp) || isdigit(*cp))) /*&& flag_number == 0*/)
                                {
                                    cp++;
                                    count_len_label++;
                                }
                                strncpy(label_name, cp - count_len_label, count_len_label);
                                IC++;
                                strcpy(help_label_name, label_name);
				strcpy(help1_label_name, label_name);
                                if (update_adress_label(label_name, head, count_line, &insteruction_head, IC) == 1)
                                {

                                    if (is_extern(head, help_label_name))
                                    {
                                         setInstructions(insteruction_head, "000000000000001", IC);
                                        fprintf(ext_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                    }
				    /*else if(is_intern(head, help_label_name))
				    {
                                         update_adress_label(help_label_name, head, count_line, &insteruction_head, IC);
                                        fprintf(ent_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                    }*/
                                    else
                                    {

                                        while (isspace(*cp))
                                            cp++;
                                    }
				count_len_label = 0;
                                }/*end of something*/
                                else
                                    flag_error++;
                            }   /*end else */
                        }  /*if (number_func == 9 || number_func == 10 || number_func == 13)*/

                        else /* if it is not jump */
                        {
                            int flag_number = 0;
                            cp = cp + strlen(cp) + 1;
                            while (isspace(*cp))
                                cp++;
                            if (number_func == NUM_PRN)
                            {
                                if (*(cp) == '#' && isdigit(cp[1])) /*if it's a number*/
                                {
                                    cp++;
                                    while (isdigit(*cp))
                                        cp++;
                                    flag_number = 1;
                                    IC++;
                                }
                                else if (*(cp) == '#' && (cp[1] == '-' || cp[1] == '+') && isdigit(cp[2])) /*if it's a number*/
                                {
                                    cp += 2;
                                    while (isdigit(*cp))
                                        cp++;
                                    flag_number = 1;
                                    IC++;
                                } /*****/

                            }  /*new*/ /*end if it 12*/
                            if ((*cp) == 'r' && cp[1] >= '0' && cp[1] <= '7' && flag_number == 0 && !isdigit(cp[2])) /*if it's a register*/
                            {
                                cp += 2;
                                while (isspace(*cp))
                                    cp++;
                                IC++;
                            }
			    else if ((*cp) == '*' && cp[1] == 'r' && cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3])) /*If it is a *register*/
                            {
			        cp += 3;
                                while (isspace(*cp))
                                    cp++;
                                IC++;
                             } 
                           else if (flag_number == 0) /*if it's a label*/
                            { 
                                while (((isalpha(*cp) || isdigit(*cp))) && flag_number == 0)
                                {
                                    cp++;
                                    count_len_label++;
                                }
                                strncpy(label_name, cp - count_len_label, count_len_label);/*put*/
                                IC++;
                                strcpy(help_label_name, label_name);
				strcpy(help1_label_name, label_name);
                                if (update_adress_label(label_name, head, count_line, &insteruction_head, IC) == 1)
                                {

                                    if (is_extern(head, help_label_name))
                                    {
                                         setInstructions(insteruction_head, "000000000000001", IC);
                                        fprintf(ext_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                    }
				   /* else if(is_intern(head, help_label_name))
				    {
                                        update_adress_label(help_label_name, head, count_line, &insteruction_head, IC);
                                        fprintf(ent_file, "%s\t%d\n", help1_label_name, IC + FIRST_LINE_NUMBER);
                                    }*/
                                    count_len_label = 0;
                                }
                                else
                                    flag_error++;
                            }
                            while (isspace(*cp))
                                cp++;
                        }/* end  if it is not jump */
                    }  /*if it is one parameter */
                }  /* end of if (find_name_func(cp, func) == 1 || flag == 1)*/
            }  /* (is_directive_command(cp) == 0 && find_name_func(cp, func) == 1) */
            else
            {
                if (!strncmp(cp + 1, "entry", ENTRY_LEN))
                {
                    int count_len_label = 0;
                    cp = cp + 7;
                    if (flag_label == 0 && *(cp - 1) != '\0') /*If there is no space after  .entry*/
                        flag_error = printError(21, count_line); 
                    else if (flag_label == 1 && *(cp - 1) != ' ')  /*If there is no space after  .entry*/
                        flag_error = printError(21, count_line);
                    while (isspace(*cp))
                        cp++;
                    while (isalpha(*cp) || isdigit(*cp))
                    {
                        count_len_label++;
                        cp++;
                    }
                    strncpy(label_name, cp - count_len_label, count_len_label);

                    if (is_exist_label(label_name, head, count_line) && flag_error == 0) 
                    {
                        setExtern(head, label_name, 2);
                        while (isspace(*cp))
                            cp++;
                        if ((*cp) != '\0')
                            flag_error = printError(5, count_line);
                    }
                    else
                        flag_error++;
                }
            }/* end  if (is_directive_command(cp) ==1) */
        }    /* end of if (*line != ';')*/
    } /* end of while*/
   

    if (flag_error != 0) /*Checking whether there was an error in the last line of the file*/
        cheak_error = FIND_ERROR;
    if (cheak_error == 0 && (last_IC + last_DC) <= MAX_CODE_LINE) /*If there were no errors in the source file and the number of encoding words does not exceed 4096*/
    {
        while (temp != NULL) /*Go through the entire list of labels*/
        {
            if (temp->externLabel == internal) /*Checking whether the label type is internal*/
            {
                /*Printing the name of the label and its address to the ent file*/
                fprintf(ent_file, "%s ", temp->labelName); 
                fprintf(ent_file, "%d\n", temp->labelAddress);
            }
            temp = temp->nextLabel;
        }

        fprintf(ob_file, "    %d %d\n", last_IC - FIRST_LINE_NUMBER, last_DC); /*IC and DC printing to the ob file*/

        for (i = FIRST_LINE_NUMBER; i < last_IC; i++) /*Go over the lines of coding*/
        {
            int j = 0;
            fprintf(ob_file, "0%d\t", i); /*Printing 4 decimal digits in each address*/
                /*Printing the coding word in the unique base 5*/
              
              decimal_array  = (int*)binary_15bit_to_decimals(temp_insteruction->instructionsCode);
              for(j=0; j<5;  j++)
		fprintf(ob_file,"%d", decimal_array[j]);

            fprintf(ob_file, "\n");
            temp_insteruction = temp_insteruction->nextInstructions;
        }
        for (i = last_IC; i < last_IC + last_DC; i++)/*Go over the coding words of the data*/
        {
            int j = 0;
            fprintf(ob_file, "0%d\t", i); /*Printing 4 decimal digits in each address*/
            decimal_array  = (int*)binary_15bit_to_decimals(temp_data->dataCode);
              for(j=0; j<5;  j++)
		fprintf(ob_file,"%d", decimal_array[j]);
            fprintf(ob_file, "\n");
            temp_data = temp_data->nextData;
        }
        rewind(ext_file); 
        pos = ftell(ext_file);/*Pointer to the beginning of the ext file*/
        fseek(ext_file, 0, SEEK_END);
        pos1 = ftell(ext_file); /*Pointer to the end of the ext file*/
        if (pos == pos1) /*Checking if the ext file is empty*/
            remove(ext_name); /*Deleting the ext file*/

        rewind(ent_file);
        pos = ftell(ent_file);/*Pointer to the beginning of the ent file*/
        fseek(ent_file, 0, SEEK_END);
        pos1 = ftell(ent_file);/*Pointer to the end of the ent file*/
        if (pos == pos1) /*Checking if the ent file is empty*/
            remove(ent_name);/*Deleting the ent file*/
    }
    else
    {
        if ((last_IC + last_DC) > MAX_CODE_LINE) /*There are more than 4096 lines of code*/
            printError(22, count_line);
        /*Deleting the files that were supposed to be created*/
        remove(ob_name);
        remove(ext_name);
        remove(ent_name);
    }

    /*Freeing the filenames from memory*/
    free(am_name);
    free(ob_name);
    free(ext_name);
    free(ent_name);

    /*Freeing the linked lists from memory*/
    freeInstructionsTable(insteruction_head);
    freeDataTable(data_head);
    freeLabelTable(head);

    /*Close the opened files*/
    fclose(am_file);
    fclose(ob_file);
    fclose(ext_file);
    fclose(ent_file);


}/* end of second*/

int three_bit_binary_to_decimal(const char *three_bit_binary)
{
    int decimal = 0;
    int i;
    for (i = 0; i < 3; ++i) 
    {
        if (three_bit_binary[2 - i] == '1') 
	{
               decimal +=  1 << i;
        }
    }
    
    return decimal;
}

int *binary_15bit_to_decimals(const char *binary_15bit)
{
    int i;
    int *decimal_array1 = (int*) malloc(5 * sizeof(int));
    if (decimal_array1 == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    for (i = 0; i < 5; ++i) 
    {
        char three_bit_binary[3]; /*for 3 bits*/
        strncpy(three_bit_binary, &binary_15bit[i * 3], 3);
        decimal_array1[i] = three_bit_binary_to_decimal(three_bit_binary);
    }
 return decimal_array1;
}

