#include "primary_pass.h"

void first(char* file_name)
{
    labelTable* head = NULL;    /*A pointer to the symbol table*/
    instructionsTable* insteruction_head = NULL; /*Pointer to the instruction table*/
    dataTable* data_head = NULL;   /*A pointer to the data table*/
    int number_func, flag = 0, count_line = 0, flag_label = 0;
    int flag_error = 0;       /*If there are mistakes count the number of mistakes otherwise enter 0*/
    int cheak_error=0;        /*If there are mistakes enter 100 otherwise enter 0*/
    char* func[NUM_OF_FUNC] = {"mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","red","prn","jsr","rts","stop" };
    FILE* am_file;
    char line[LINE_LEN];
    char help_line[LINE_LEN];
    char* am_name = (char*)malloc((strlen(file_name) * sizeof(char)) + 1);/*Dynamically assigning a string*/
    int IC = START_IC;
    int DC = START_DC;
    int pos,pos1;
    int warning=0;         /*Count the number of times there is a comment line in the file*/
    if (am_name == NULL)/*Checks if the assignment was successful*/
    {
        printf("no allocation");
        exit(0);
    }
    strcpy(am_name, file_name);       
    am_name[strlen(am_name) - 1] = 'm';
    if ((am_file = fopen(am_name, "r+")) == NULL)/*Checks if the file was opened successfully*/
    {
        fprintf(stderr, "Cannot open file %s\n", file_name);
        exit(0);
    }
   rewind(am_file);
   pos=ftell(am_file);   /*The pointer to the beginning of the file*/
   fseek(am_file, 0, SEEK_END);
   pos1=ftell(am_file);  /*The pointer to the end of the file*/
   rewind(am_file);
   if(pos==pos1)   /*Checks if the file is empty*/
    {
	fprintf(stderr,"the file is empty\n ");
        exit(0);
    }
    while (fgets(line, LINE_LEN, am_file) != NULL)
    {
        
        char label_name[LABEL_LENGTH] = { "\0" }; /*Save the label  name*/        
	char first_name[LABEL_LENGTH] = { "\0" }; /*Save the first parameter*/
        char second_name[LABEL_LENGTH] = { "\0" };/*Save the second parameter*/
        char* cp;
        int count_register = 0;  /*Count the number of registers when there are 2 parameters*/
        if(flag_error!=0)    
           cheak_error=FIND_ERROR;  /*If ever an error is detected in the file straight updates the value of the cheak_error  to 100*/
        flag_error = 0;
        flag_label = 0;  /*Its value is 1 if a label other than 0 is detected*/
        count_line++;    /*Count the number of rows*/
        replace_tab_in_space(line);
        if (*line != ';')
        {
            char* space = " ";
            char* comma = ",";
            char* colon = ":";
            strcpy(help_line, line);
            cp = strtok(help_line, space);  /*Holds the pointer until a space*/
            if(two_comma(line)!=0)          /*Checks if there are two consecutive commas in the file*/
               flag_error = printError(18, count_line);
            else
            {
            if (is_directive_command(line) == 0 && find_name_func(cp, func) == 0)   /*If it is a label*/
            {
                if (strchr(help_line, ':') == NULL) /*If the label contains a colon*/
                    flag_error = printError(1, count_line);
                else
                {
                    strcpy(help_line, line);
                    cp = strtok(help_line, colon);  /*Keeps the pointer up to a colon*/
                    if (legal_label(cp,count_line) == 1)  /*If the label is valid*/
                    {
                        strcpy(label_name, cp);
                        cp = cp + strlen(cp) + 1;
                        if (*cp != ' ')
                            flag_error = printError(4, count_line); /*If there is no space after the colon*/
                        else
                        {
                            flag_label = 1;
                            while (isspace(*cp))
                                cp++;
                        } /* end of second else*/

                    }  /* end of if it's legal label*/
                    else 
                       flag_error++;

                }  /* end of main else*/

            } /* end of if it's label*/
            /*If you have reached the name of a function*/
            if ((is_directive_command(cp) == 0 && find_name_func(cp, func) == 1) || (is_directive_command(cp) == 0 && flag_label == 1)) 
            {
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
                    if (flag == 0)
                        flag_error = printError(3, count_line);
                }
                if (find_name_func(cp, func) == 1 || flag == 1)
                { /*If you did find the function name in the function array*/

                    number_func = find_index_func(cp, func);
                    if (number_func == NUM_RTS || number_func == NUM_STOP)  /*If it's a function that doesn't accept any parameters*/
                    {
                        cp = cp + strlen(cp) + 1;
                        while (isspace(*cp))
                            cp++;
                        if ((*cp) != '\0')   /*If there are no extra characters at the end of the line*/
                            flag_error = printError(5, count_line);
                        else
                        {
                            if (flag_label == 1)
                            {
                                if (find_label(head, label_name) == 0)
                                    addLabel(&head, label_name, IC, instruction); /*Adds the label to the symbol table*/
                                else
                                    flag_error = printError(15, count_line);
                            }
                            IC++;
                            zero_parameter(number_func, &insteruction_head);  /*Sends the encoding function 0 parameters*/
                        }
                    }/*(number_func == NUM_RTS || number_func == NUM_STOP)*/
                    
                    /*If it is a function that accepts 2 parameters*/
                    else if (number_func >= NUM_MOV && number_func <= NUM_LEA)
                    {

                        if (number_func == NUM_LEA)   /*If it is function number 4*/
                        {  /* else 1*/

                            cp = cp + strlen(cp) + 1;
                            
                                while (isspace(*cp))
                                    cp++;
                                if (*(cp) == '\0')  /*If the line is over*/
                                    flag_error = printError(7, count_line);  
                                else if (*(cp) == '#' )  /*if it's a number*/
                                    flag_error = printError(9, count_line);
                                else  if ((*cp) == 'r' && (cp[1] >= '0' && cp[1] <= '7') && !isdigit(cp[2]))  /*If it is a register*/
                                {
                                    flag_error = printError(2, count_line);
                                }
                                else if(((*cp) == '*' && cp[1] == 'r' &&  cp[2] >= '0' && cp[2] <= '7') && !isdigit(cp[3]))
			        {
                                    flag_error = printError(2, count_line);
                                 }
                                else /* else 3 -if it is label*/  
                                {
                                    if (find_label_before_comma(cp, count_line) != 0)  
                                    {
                                        while (isalpha(*cp) || isdigit(*cp))
                                            cp++;
                                        strcpy(first_name, "??");
                                    }
                                    else
                                        flag_error++;
                                    if (*(cp) == '\n') /*If the line is over*/
                                        flag_error = printError(7, count_line);
                                    else if (flag_error == 0)/* else 4*/
                                    {
                                        while (isspace(*cp))
                                            cp++;
                                        if (*(cp) != ',')  /*If a comma is missing*/
                                            flag_error = printError(8, count_line);
                                        else /* else 5*/
                                        {
                                            cp++;

                                            while (isspace(*cp))
                                                cp++;
                                            if (*(cp) == '\0') 
                                                flag_error = printError(7, count_line);
                                            else /* else 6*/
                                            {         /*If the second parameter is a register*/
                                                if ((*cp) == 'r' && cp[1] >= '0' && cp[1] <= '7' && !isdigit(cp[2]))
                                                {
                                                    strncpy(second_name, cp, REGISTER_LEN);
                                                    cp += 2;
                                                    while (isspace(*cp))
                                                        cp++;
                                                    if (*(cp) != '\0')
                                                        flag_error = printError(5, count_line);
                                                    else
                                                    {
                                                        if (flag_label == 1)
                                                        {
                                                            if (find_label(head, label_name) == 0)
                                                                addLabel(&head, label_name, IC, instruction);   /*Adds the label to the symbol table*/
                                                            else
                                                                flag_error = printError(15, count_line);
                                                        }
                                                        IC += 3;
                                                        tow_parameter(number_func, first_name, second_name, &insteruction_head);
                                                    }

                                                } 
						else if ((*cp) == '*' && cp[1] == 'r' &&  cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3]))
                                                {
                                                    strncpy(second_name, cp, 2);
                                                    cp += 3;
                                                    while (isspace(*cp))
                                                        cp++;
                                                    if (*(cp) != '\0')
                                                        flag_error = printError(5, count_line);
                                                    else
                                                    {
                                                        if (flag_label == 1)
                                                        {
                                                            if (find_label(head, label_name) == 0)
                                                                addLabel(&head, label_name, IC, instruction);   /*Adds the label to the symbol table*/
                                                            else
                                                                flag_error = printError(15, count_line);
                                                        }
                                                        IC += 3;
                                                        tow_parameter(number_func, first_name, second_name, &insteruction_head);
                                                    }
						}
                                                else if (*(cp) == '#')   /*If the second parameter is a number*/
                                                    flag_error = printError(9, count_line);
                                                else /* else 7*/
                                                {
                                                    if (find_end_label(cp, count_line) != 0)
                                                    {
                                                        while (isalpha(*cp) || isdigit(*cp))
                                                            cp++;
                                                        strcpy(first_name, "??");
                                                    }
                                                    else
                                                        flag_error++;
                                                    while (isspace(*cp))
                                                        cp++;
                                                    if (*(cp) != '\0')
                                                        flag_error = printError(5, count_line);
                                                    else if (flag_error == 0)
                                                    {
                                                        if (flag_label == 1)
                                                        {
                                                            if (find_label(head, label_name) == 0)
                                                                addLabel(&head, label_name, IC, instruction);  /*Adds the label to the symbol table*/
                                                            else
                                                                flag_error = printError(15, count_line);
                                                        }
                                                        IC += 3;
                                                        tow_parameter(number_func, first_name, second_name, &insteruction_head);
                                                    }
                                                } /* end of else  7*/
                                            }/* end of else  6*/
                                        } /* end of else  5*/
                                    } /* end of else  4*/
                                }/* end of else 3 */
                        } /* end of else 1 */
                        else /*if you dont func 4*/
                        {
                            cp = cp + strlen(cp) + 1;
                            while (isspace(*cp))
                                cp++;
                            if (*(cp) == '\0')
                                flag_error = printError(7, count_line);
                            else if ((*(cp) == '#' && isdigit(cp[1])))   /*If the first parameter is a number*/
                            {
                                int count_number = 0, count3 = 0;
                                cp++; 
                                count3 = find_number_before_comma(cp, count_line);   /*Checks if the number is whole in base 10*/
                                if (count3 != 0) 
                                {
                                    while (isdigit(*cp))
                                    {
                                        cp++;
                                        count_number++;
                                    }
                                    strncpy(first_name, cp - count_number - 1, count_number + 1);
                                }
                                else
                                    flag_error++;
                            }
                            else if (*(cp) == '#' && (cp[1] == '-' || cp[1] == '+') && isdigit(cp[2])) /*If the first parameter is a number*/
                            {

                                int count_number = 1, count3 = 0;
                                cp += 2;
                                count3 = find_number_before_comma(cp - 1, count_line);  /*Checks if the number is whole in base 10*/
                                if (count3 != 0)
                                {
                                    while (isdigit(*cp))
                                    {
                                        cp++;
                                        count_number++;
                                    }
                                    strncpy(first_name, cp - count_number - 1, count_number + 1);
                                }
                                else
                                    flag_error++;
                            }
                            else  if ((*cp) == 'r' && cp[1] >= '0' && cp[1] <= '7' && !isdigit(cp[2]))  /*If the first parameter is a register*/
                            {
                                strncpy(first_name, cp, 2);
                                cp += 2;
                                count_register++;
                            }
			    else if((*cp) == '*' && cp[1] == 'r' &&  cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3]))/*If the first parameter is a non direct register*/
			    {
                                strncpy(first_name, cp, REGISTER_LEN);
                                cp += 3;
                                count_register++;
                            }
                            else  /*If the first parameter is a label*/
                            {

                                if (find_label_before_comma(cp, count_line) != 0)  /*If the label is valid*/
                                {
                                    while (isalpha(*cp) || isdigit(*cp))
                                        cp++;
                                    strcpy(first_name, "??");
                                }
                                else
                                    flag_error++;
                            }
                            if (*(cp) == '\n')
                                flag_error = printError(7, count_line);
                            else  if (flag_error == 0)  
                            {

                                while (isspace(*cp))
                                    cp++;
                                if (*(cp) != ',' && flag_error == 0)    /*If a comma is missing*/
                                    flag_error = printError(8, count_line);
                                else if (flag_error == 0)
                                {
                                    int flag_number = 0; 
                                    cp++;
                                    while (isspace(*cp))
                                        cp++;
                                    if (*(cp) == '\0')
                                        flag_error = printError(7, count_line);
                                    else
                                    {
                                        if (number_func == NUM_CMP)   /*If it is function number 1*/
                                        {  

                                            if (*(cp) == '#' && isdigit(cp[1]))
                                            {   /*If the second parameter is a number*/
                                                int count_number = 0, count3 = 0;
                                                cp++;
                                                count3 = find_number(cp, count_line); /*Checks if the number is whole in base 10*/

                                                if (count3 != 0)
                                                {
                                                    while (isdigit(*cp))
                                                    {
                                                        cp++;
                                                        count_number++;
                                                    }
                                                    strncpy(second_name, cp - count_number - 1, count_number + 1);

                                                    flag_number = 1;
                                                    if (flag_label == 1)
                                                    {
                                                        if (find_label(head, label_name) == 0)
                                                        {
                                                            addLabel(&head, label_name, IC, instruction);
                                                        }
                                                        else
                                                        {
                                                            flag_error = printError(15, count_line);
                                                        }

                                                    }
                                                    IC += 3;
                                                    tow_parameter(number_func, first_name, second_name, &insteruction_head);
                                                }
                                                else
                                                    flag_error++;
                                            }
                                            else if (*(cp) == '#' && (cp[1] == '-' || cp[1] == '+') && isdigit(cp[2]))
                                            {  /*If the second parameter is a number*/
                                                int count_number = 1, count3 = 0;
                                                cp += 2;
                                                count3 = find_number(cp - 1, count_line); /*Checks if the number is whole in base 10*/
                                                if (count3 != 0)
                                                {

                                                    while (isdigit(*cp))
                                                    {
                                                        cp++;
                                                        count_number++;
                                                    }
                                                    strncpy(second_name, cp - count_number - 1, count_number + 1);

                                                    flag_number = 1;
                                                    if (flag_label == 1)
                                                    {
                                                        if (find_label(head, label_name) == 0)
                                                            addLabel(&head, label_name, IC, instruction);
                                                        else
                                                            flag_error = printError(15, count_line);

                                                    }
                                                    IC += 3;
                                                    tow_parameter(number_func, first_name, second_name, &insteruction_head);
                                                }
                                                else
                                                    flag_error++;

                                            }
                                        } 
                                        if ((*cp) == 'r' && cp[1] >= '0' && cp[1] <= '7' && !isdigit(cp[2]) && flag_number == 0) 
                                        { /*If the second parameter is a register*/
                                            strncpy(second_name, cp, 2);
                                            cp += 2;
                                            count_register++;
                                            while (isspace(*cp))
                                                cp++;
                                            if (*(cp) != '\0')
                                                flag_error = printError(5, count_line);
                                            else if (flag_label == 1)
                                            {
                                                if (find_label(head, label_name) == 0)
                                                    addLabel(&head, label_name, IC, instruction);
                                                else
                                                    flag_error = printError(15, count_line);
                                            }
                                            if (count_register != 2) /*If there are 2 registers*/
                                                IC += 3;
                                            else
                                                IC += 2;
                                            tow_parameter(number_func, first_name, second_name, &insteruction_head);
                                        }
					else if((*cp) == '*' && cp[1] == 'r' &&  cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3]) && flag_number == 0)
			                 {
                                            strncpy(second_name, cp, REGISTER_LEN);
                                            cp += 3;
                                            count_register++;
                                            while (isspace(*cp))
                                                cp++;
                                            if (*(cp) != '\0')
                                                flag_error = printError(5, count_line);
                                            else if (flag_label == 1)
                                            {
                                                if (find_label(head, label_name) == 0)
                                                    addLabel(&head, label_name, IC, instruction);
                                                else
                                                    flag_error = printError(15, count_line);
                                            }
                                            if (count_register != 2) /*If there are 2 registers*/
                                                IC += 3;
                                            else
                                                IC += 2;
                                            tow_parameter(number_func, first_name, second_name, &insteruction_head);
                                          }
                                        else if (*(cp) == '#')  /*If the second parameter is a number*/
                                            flag_error = printError(9, count_line);
                                        else  if (flag_number == 0)
                                        {

                                            if (find_end_label(cp, count_line) != 0)    /*If the label is valid*/
                                            {
                                                while (isalpha(*cp) || isdigit(*cp))
                                                    cp++;
                                                strcpy(second_name, "??");
                                            }
                                            else
                                                flag_error++;
                                            while (isspace(*cp))
                                                cp++;
                                            if (*(cp) != '\0' && flag_error == 0)
                                                flag_error = printError(5, count_line);
                                            else  if (flag_error == 0)
                                            {
                                                if (flag_label == 1)
                                                {
                                                    if (find_label(head, label_name) == 0)
                                                        addLabel(&head, label_name, IC, instruction);
                                                    else
                                                        flag_error = printError(15, count_line);
                                                }
                                                IC += 3;
                                                tow_parameter(number_func, first_name, second_name, &insteruction_head);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    else/*if it is one parameter */
                    {
                        if (number_func == NUM_JMP || number_func == NUM_BNE || number_func == NUM_JSR)
                        {  /*If you are a jump function*/
                            cp = cp + strlen(cp) + 1;

                            while (isspace(*cp))
                                cp++;
                            if (*(cp) == '\0')
                                flag_error = printError(7, count_line);
                            else if (*(cp) == '#')   /*if it's a number*/
                                flag_error = printError(9, count_line);
                            else if (!isalpha(*cp) && !isdigit(*cp))
                                flag_error = printError(2, count_line); 
			    else if ((*cp) == '*' && cp[1] == 'r' && cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3])) /*if it's a register*/
                            {
                                strncpy(first_name, cp, REGISTER_LEN);
                                cp = cp + 3;
                                while (isspace(*cp))
                                    cp++;
                                if (*(cp) != '\0')

                                    flag_error = printError(5, count_line);
                                else if (flag_label == 1)
                                {
                                    if (find_label(head, label_name) == 0)
                                        addLabel(&head, label_name, IC, instruction);
                                    else
                                        flag_error = printError(15, count_line);
                                }

                                one_parameter(number_func, first_name, &insteruction_head);
                                IC += 2;
                            } /*end if it register*/
                            else  /*if it's a label*/
                            {
                                while (isalpha(*cp) || isdigit(*cp))
                                    cp++;
                                 if (flag_error == 0)    /*If it is a jump with one parameter*/
                                {
                                    strcpy(first_name, "??");
                                    while (isspace(*cp))
                                        cp++;
                                    if (*(cp) != '\0')
                                        flag_error = printError(5, count_line);
                                    else
                                    {
                                        if (flag_label == 1)
                                        {
                                            if (find_label(head, label_name) == 0)
                                                addLabel(&head, label_name, IC, instruction);
                                            else
                                                flag_error = printError(15, count_line);
                                        }
                                        IC += 2;
                                        one_parameter(number_func, first_name, &insteruction_head);
                                    }
                                }
                            }
                        }

                        else /* If it is one parameter that is not of a jump function*/
                        {
                            int flag_number = 0;
                            cp = cp + strlen(cp) + 1;
                            while (isspace(*cp))
                                cp++;
                            if (*(cp) == '\0')
                                flag_error = printError(7, count_line);
                            if (number_func == NUM_PRN)  /*If you are function number 12*/
                            {
                                if (*(cp) == '#' && isdigit(cp[1]))  /*if it's a number*/
                                {
                                    int count_number = 0, count3 = 0;
                                    cp++;
                                    count3 = find_number(cp, count_line); /*Checks if the number is whole in base 10*/
                                    if (count3 != 0)
                                    {
                                        while (isdigit(*cp))
                                        {
                                            cp++;
                                            count_number++;
                                        }
                                        strncpy(first_name, cp - count_number - 1, count_number + 1);
                                        flag_number = 1;
                                    }
                                    else
                                        flag_error++;
                                }
                                else if (*(cp) == '#' && (cp[1] == '-' || cp[1] == '+') && isdigit(cp[2])) /*if it's a number*/
                                {
                                    int count_number = 1, count3 = 0;
                                    cp += 2;
                                    count3 = find_number(cp - 1, count_line); /*Checks if the number is whole in base 10*/
                                    if (count3 != 0)
                                    {
                                        while (isdigit(*cp))
                                        {
                                            cp++;
                                            count_number++;
                                        }
                                        strncpy(first_name, cp - count_number - 1, count_number + 1);
                                        flag_number = 1;
                                    }
                                    else
                                        flag_error++;
                                } 
                            }   /*end if it 12*/
                            if ((*cp) == 'r' && cp[1] >= '0' && cp[1] <= '7' && flag_number == 0 && !isdigit(cp[2]))
                            {   /*if it's a register*/
                                strncpy(first_name, cp, 2);
                                cp += 2;
                                while (isspace(*cp))
                                    cp++;
                                if (*(cp) != '\0')
                                    flag_error = printError(5, count_line);
                                if (flag_label == 1)
                                {
                                    if (find_label(head, label_name) == 0)
                                        addLabel(&head, label_name, IC, instruction);
                                    else
                                        flag_error = printError(15, count_line);
                                }
                                IC += 2;
                                one_parameter(number_func, first_name, &insteruction_head);
                            }
			    else if((*cp) == '*' && cp[1] == 'r' &&  cp[2] >= '0' && cp[2] <= '7' && !isdigit(cp[3]))
			    {
                                strncpy(first_name, cp, REGISTER_LEN);
                                cp += 3;
                                while (isspace(*cp))
                                    cp++;
                                if (*(cp) != '\0')
                                    flag_error = printError(5, count_line);
                                if (flag_label == 1)
                                {
                                    if (find_label(head, label_name) == 0)
                                        addLabel(&head, label_name, IC, instruction);
                                    else
                                        flag_error = printError(15, count_line);
                                }
                                IC += 2;
                                one_parameter(number_func, first_name, &insteruction_head);

                            }
                            else if (*(cp) == '#')  /*if it's a number*/
                                flag_error = printError(9, count_line);
                            else /*if it's a label*/
                            {

                                if (flag_number == 0 && flag_error == 0)
                                {
                                    if (find_end_label(cp, count_line) != 0)
                                    {
                                        while (isalpha(*cp) || isdigit(*cp))
                                            cp++;
                                        strcpy(first_name, "??");
                                    }
                                    else
                                        flag_error++;
                                }
                                while (isspace(*cp))
                                    cp++;
                                if (*(cp) != '\0' && flag_error == 0)
                                {
                                    flag_error = printError(5, count_line);

                                }
                                else if (flag_error == 0)
                                {
                                    if (flag_label == 1)
                                    {
                                        if (find_label(head, label_name) == 0)
                                            addLabel(&head, label_name, IC, instruction);
                                        else
                                            flag_error = printError(15, count_line);
                                    }
                                    IC += 2;
                                    one_parameter(number_func, first_name, &insteruction_head);

                                }
                            }
                        }
                    }/* end  if it is not need to jump */
                }  /* end of if (find_name_func(cp, func) == 1 || flag == 1)*/
            }  /* (is_directive_command(cp) == 0 && find_name_func(cp, func) == 1) */
            else
            { /* if (is_directive_command(cp) ==1 */
                int count_apostrophes = 0;
                int length = 0, length1 = 0; 
                if (!strncmp(cp + 1, "string", STRING_LEN))
                {
                    cp = cp + 8;
                   if(flag_label==0 && *(cp-1)!='\0' ) /*If there is no space after  .string*/
                        flag_error = printError(21, count_line);
                   else if(flag_label==1 && *(cp-1)!=' ' ) /*If there is no space after  .string*/
                             flag_error = printError(21, count_line);

                    while (isspace(*cp))
                        cp++;
                    if (*(cp) == '\0')
                        flag_error = printError(7, count_line);
                    else if (*(cp) != '"' && flag_error==0 ) /*If there are no opening commas*/
                        flag_error = printError(12, count_line);
                    else
                    {

                        cp++;
                        while (*(cp) != '\n')
                        {
                            if (*(cp) == '"')  
                            {
                                count_apostrophes++;
                                length1 = length; /*The length of the string*/
                            }
                            cp++;
                            length++;  /*The length from the beginning of the string to the end of the line*/
                        }
                        if (count_apostrophes == 0)  /*If there are no closing commas*/
                            flag_error = printError(13, count_line);
                        else
                        {

                            cp = cp - (length - length1) + 1;
                            strncpy(first_name, cp - length1 - 1, length1); /*Copies the string*/
                            while (isspace(*cp))
                                cp++;
                            if (*(cp) != '\0')
                                flag_error = printError(5, count_line);
                            else
                            {
                                string_code(first_name, &data_head);  /*Encodes the string*/
                                if (flag_label == 1)
                                {
                                    if (find_label(head, label_name) == 0)
                                        addLabel(&head, label_name, DC, prompt);
                                    else
                                        flag_error = printError(15, count_line);
                                }

                                DC += length1 + 1;
                            }
                        }
                    }
                } 
                else if (!strncmp(cp + 1, "data", DATA_LEN))
                {
                    int i = 0, number, count3 = 0;
                    int arry[LINE_LEN] = { 0 }; /*An array that contains all the received numbers*/
                    cp = cp + 6;
                    if(flag_label==0 && *(cp-1)!='\0' ) /*If there is no space after  .data*/
                        flag_error = printError(21, count_line);
                   else if(flag_label==1 && *(cp-1)!=' ' ) /*If there is no space after  .data*/
                             flag_error = printError(21, count_line);
                    while (isspace(*cp))
                        cp++;
                    if (*(cp) == '\0')
                        flag_error = printError(7, count_line);
                    else if (*(cp) == ',')
                        flag_error = printError(24, count_line);
                    else 
                    while ((cp = strtok(NULL, comma)))  /*Saves the pointer each time until a space*/
                    {
                        while (isspace(*cp))
                            cp++;
                        if (i == 0 && flag_label == 1)
                            cp = cp + 6;
                        while (isspace(*cp))
                            cp++;
                        number = atoi(cp);
                        arry[i] = number;
                        i++;
                        count3 = Invaild_number_of_data(cp, number, count_line); /*Checks if the number is whole in base 10*/

                    }
                    if (count3 != 0)
                    {
                        if (find_label(head, label_name) == 0)
                            addLabel(&head, label_name, DC, prompt);
                        else
                            flag_error = printError(15, count_line);

                        DC += i;
                        data_code(arry, i, &data_head);

                    }
                  else
                    flag_error++;


                }
                else if (!strncmp(cp + 1, "extern", EXTERN_LEN))
                {
                    int count_len_label = 0;
                    cp = cp + 8;
                    if(flag_label==0 && *(cp-1)!='\0' )    /*If there is no space after .extern*/
                        flag_error = printError(21, count_line);
                   else if(flag_label==1 && *(cp-1)!=' ' )  /*If there is no space after .extern*/
                             flag_error = printError(21, count_line);
                    while (isspace(*cp))
                        cp++;
                    if (*(cp) == '\0' && flag_error==0)
                        flag_error = printError(7, count_line);
                    else if(flag_error==0)
                    {
                        while (isalpha(*cp) || isdigit(*cp))
                        {
                            count_len_label++;
                            cp++;
                        }
                        strncpy(label_name, cp - count_len_label, count_len_label);

                        if (legal_label(label_name,count_line) == 1 )
                        {
                            addLabel(&head, label_name, 0, unknown);
                            setExtern(head, label_name, 1);
                            while (isspace(*cp))
                                cp++;
                            if ((*cp) != '\0')
                                flag_error = printError(5, count_line);
                        }
                    }
                }
            }/* end  if (is_directive_command(cp) ==1 )*/
          }
        }    /* end of if (*line != ';')*/
    else 
       warning++;
    } /* end of while*/

     fclose(am_file);
    if(flag_error!=0)
           cheak_error=FIND_ERROR;
    if (cheak_error == 0&&warning!=count_line)   /*If there are no errors and there are additional lines besides comment lines*/
    {
        setAddress(head, IC);
        second(file_name, head, insteruction_head, IC, DC, data_head);
       
    }
    else if(warning!=count_line)  /*Release all linked lists*/
    {
	  freeInstructionsTable(insteruction_head);
	  freeDataTable(data_head);
	  freeLabelTable(head);
    }
   free(am_name);
}   /* end of first*/
