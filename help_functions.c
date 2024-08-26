
#include "help_functions.h"

int printError(int error, int count_line)
{
    switch (error)
    {

    case 1:
        fprintf(stdout,"error in line %d -Missing a colon at the end of a label  \n", count_line);
        return 1;
    case 2:
        fprintf(stdout,"error in line %d -Invalid label \n", count_line);
        return 1;
    case 3:
       fprintf(stdout,"error in line %d -Invalid function \n", count_line);
        return 1;
    case 4:
       fprintf(stdout,"error in line %d -Missing space after label \n", count_line);
        return 1;
    case 5:
        fprintf(stdout,"error in line %d -Additional characters at the end of a line \n", count_line);
        return 1;
    case 6:
        fprintf(stdout,"error in line %d -Missing space after function  \n", count_line);
        return 1;
    case 7:
        fprintf(stdout,"error in line %d -Missing parameter \n", count_line);
        return 1;
    case 8:
        fprintf(stdout,"error in line %d -Missing comma  \n", count_line);
        return 1;
    case 9:
        fprintf(stdout,"error in line %d -Function does not support numeric input \n", count_line);
        return 1;
    case 10:
        fprintf(stdout,"error in line %d -Unneed space \n", count_line);
        return 1;
    case 12:
        fprintf(stdout,"error in line %d -Missing quotation marks at the beginning of a string \n", count_line);
        return 1;
    case 13:
        fprintf(stdout,"error in line %d -Missing quotation marks at the end of a string \n", count_line);
        return 1;
    case 14:
        fprintf(stdout,"error in line %d -Undefined label name \n", count_line);
        return 1;
    case 15:
        fprintf(stdout,"error in line %d -Label name is already in use \n", count_line);
        return 1;
    case 16:
        fprintf(stdout,"error in line %d -Number value beyond range limits \n", count_line);
        return 1;
    case 17:
       fprintf(stdout,"error in line %d -Number not an integer \n", count_line);
        return 1;
    case 18:
       fprintf(stdout,"error in line %d -Double commas  \n", count_line);
        return 1;
    case 19:
        fprintf(stdout,"error in line %d -Macro name must differ from function name \n", count_line);
        return 1;
    case 20:
       fprintf(stdout,"error in line %d -Macro name must differ from register name  \n", count_line);
        return 1;
    case 21:
        fprintf(stdout,"error in line %d -Space required after directive command \n", count_line);
        return 1;
    case 22:
        fprintf(stdout,"error in line %d -More than 4096 lines in the code  \n", count_line);
        return 1;
    case 23:
        fprintf(stdout,"error in line %d -Label name longer than 32 characters  \n", count_line);
        return 1;
    case 24:
        fprintf(stdout,"error in line %d -Comma before parameter is not valid  \n", count_line);
        return 1;
    }
    return 1;
}

/* Replaces all tab characters in the input string with space characters.*/
void replace_tab_in_space(char command_line[])
{
    int z;
    for (z = 0; z < strlen(command_line); z++)
        if (command_line[z] == '\t')
            command_line[z] = ' ';
}




int two_comma(char command_line_help[])
{
    int w, help = 0;
    for (w = 0; w < (strlen(command_line_help) - 1); w++)
        if (command_line_help[w] == ',') 
        {
            /* Found the first comma */
            help = w + 1;
            while (command_line_help[help] == ' ') 
            {
                /* Skipping spaces after the first comma */
                help++;
            }
            if (command_line_help[help] == ',') 
                /* Found the second comma after spaces */
                return 1; /* Return 1 if consecutive commas are found */
        }
    return 0; /* Return 0 if no consecutive commas are found */
}





int legal_label(char cp[LABEL_LENGTH],int count_line)
{

    int i, length = strlen(cp);
    char* temp = cp;
    if (length > LABEL_LENGTH)  /*If the length of the label big than 31*/
    {
        printError(23,count_line);
        return 0;
    }
    if (!isalpha(*temp)) /*If the label does not start with a letter*/
    {
        printError(2,count_line);
        return 0;
    }
    for (i = 1; i < length; i++)
    {
        if (isalpha(*temp) || isdigit(*temp) ) /*Check that the label has only letters and numbers*/
            temp++;
        else
        {
            printError(2,count_line);
            return 0;
        }
    }
    return 1;
}




int find_index_func(char* name, char* func[NUM_OF_FUNC])
{
    int i;
    for (i = 0; i < NUM_OF_FUNC; i++)
    {
        if (!strcmp(func[i], name))
            /* Found the function name in the array */
            return i; /* Return the index of the matching function name */
    }
    return i; /* Return the index after the loop if not found */
}





int find_name_func(char* name, char* func[NUM_OF_FUNC])
{
    int i;
    for (i = 0; i < NUM_OF_FUNC; i++)
    {
        if (!strcmp(func[i], name))
            /* Found the function name in the array */
            return 1; /* Return 1 if the function name is found */
    }
    return 0; /* Return 0 if the function name is not found */
}



int is_directive_command(char* cp)
{
    char* temp = cp;
    if (*temp == '.'&& (!strncmp(temp + 1, "data", DATA_LEN) ||  !strncmp(temp + 1, "string", STRING_LEN) || !strncmp(temp + 1, "entry", ENTRY_LEN) || !strncmp(temp 		+1,"extern",EXTERN_LEN)))
        /* Checks if the string starts with '.' followed by a valid directive */
        return 1; /* Return 1 if it is a directive command */
    
    return 0; /* Return 0 if it is not a directive command */
}


void binary(short binar, instructionsTable** insteruction_head)
{
    char word[WORD_LEN] = { 0 }; /* The array of the word is initialized to 0 */
    short mask1 = 1 << (WORD_LEN - 1); 
    int i;

    for (i = 0; i < WORD_LEN; i++)
    {
        if (mask1 & binar)
            word[i] = '1'; /* Set bit to '1' if the corresponding bit in binar is 1 */
        else
            word[i] = '0'; /* Set bit to '0' otherwise */
        mask1 >>= 1;
    }

    addInstructions(insteruction_head, word); /* Add the binary word to the instructions table */
}

void binary_data(short binar, dataTable** data_head)
{
    char word[WORD_LEN] = { 0 }; /* The array of the word is initialized to 0 */
    short mask1 = 1 << (WORD_LEN - 1);
    int i;

    for (i = 0; i < WORD_LEN; i++)
    {
        if (mask1 & binar)
            word[i] = '1'; /* Set bit to '1' if the corresponding bit in binar is 1 */
        else
            word[i] = '0'; /* Set bit to '0' otherwise */
        mask1 >>= 1;
    }

    addData(data_head, word); /* Add the binary word to the data table */
}

void set_binary(short binar, instructionsTable** insteruction_head, int back)
{
    char word[WORD_LEN] = { 0 }; /* The array of the word is initialized to 0 */
    short mask1 = 1 << (WORD_LEN - 1);
    int i;
    int length = num_of_cells(*insteruction_head); /* Get the current number of cells in the instructions table */

    for (i = 0; i < WORD_LEN; i++)
    {
        if (mask1 & binar)
            word[i] = '1'; /* Set bit to '1' if the corresponding bit in binar is 1 */
        else
            word[i] = '0'; /* Set bit to '0' otherwise */
        mask1 >>= 1;
    }

    setInstructions(*insteruction_head, word, length - back); /* Update the instructions table with the new binary word */
}





void tow_parameter(int str1, char str2[], char str3[], instructionsTable** insteruction_head)
{
    short mask1, mask2, mask3, mask4;
    int num1, num2, flag =0;
    mask1 = str1 << 11; /* shifts the label name by 11 bits for the opcode to be in bits 11 to 14*/
    mask2 = 0; /* Source operand addressing mode (bits 10-7)*/
    mask3 = 0; /* Destination operand addressing mode (bits 6-3)*/
    mask4 = 1;
    mask4 = mask4 << 2; /* A = 1, R = 0, E = 0*/
    mask1 = mask1 | mask4;
   
    if (str2[0] == '#') /*If the first parameter is a number*/
    {
        mask2 = 1; /* 0001 - number*/
        mask2 = mask2 << 7;
        mask1 = mask1 | mask2;
        binary(mask1, insteruction_head); /* Add the first part of the instruction*/
	num1 = atoi(str2 + 1);
        num1 = num1 << 6;
	num1 = mask4 | num1;
        binary(num1, insteruction_head);
    }
    else if (str2[0] == 'r') /*If the first parameter is a register*/
    {
        mask2 = 8; /* 1000 - register direct*/
        mask2 = mask2 << 7; /* Shift to bits 7-10*/
        mask1= mask2 | mask1; /* Combine with the opcode*/
        binary(mask1, insteruction_head);
	num1 = atoi(str2 + 1);
	num1 = num1 << 6;
	num1 = mask4 | num1;
        binary(num1, insteruction_head);
	if(str3[0] == 'r' || (str3[0] == '*' && str3[1]== 'r'))
	{
	    flag =1;	
	    if(str3[0] == '*' && str3[1]== 'r')
		{
		  mask3 = 4; /* 0100 - non direct register*/
                  mask3 = mask3 << 3; /* Shift to bits 3-6*/
                  mask1 = mask3 | mask1; /* Combine with the opcode*/
                  set_binary(mask1, insteruction_head, 2);
		  num2 = atoi(str3 + 2);
	          num2 = num2 << 3;
	          num1 = num1 | num2;
                  set_binary(num1, insteruction_head,1);	
                  return;
		}
	    else
	        {	
		  mask3 = 8; /* 0100 - non direct register*/
                  mask3 = mask3 << 3; /* Shift to bits 3-6*/
                  mask1= mask3 | mask1; /* Combine with the opcode*/
                  set_binary(mask1, insteruction_head, 2);
		  num2 = atoi(str3 + 1);
	          num2 = num2 << 3;
	          num1 = num1 | num2;
                  set_binary(num1, insteruction_head,1);	
                  return;
		}
	}
    }
    else if (str2[0] == '*' && str2[1]== 'r') /*If the first parameter is a non direct register*/
    {
        mask2 = 4; /* 0100 - non direct register*/
        mask2 = mask2 << 7; /* Shift to bits 7-10*/
        mask1= mask1 | mask2; /* Combine with the opcode*/
        binary(mask1, insteruction_head);
	num1 = atoi(str2 + 2);
	num1 = num1 << 6;
	num1 = mask4 | num1;
        binary(num1, insteruction_head);
	if(str3[0] == 'r' || (str3[0] == '*' && str3[1]== 'r'))
	{
	    if(str3[0] == '*' && str3[1]== 'r')
		{
		  mask3 = 4; /* 0100 - non direct register*/
                  mask3 = mask3 << 3; /* Shift to bits 3-6*/
                  mask1= mask3 | mask1; /* Combine with the opcode*/
                  set_binary(mask1, insteruction_head, 2);
		  num2 = atoi(str3 + 2);
	          num2 = num2 << 3;
	          num1 = num1 | num2;
		  num1 = mask4 | num1;
                  set_binary(num1, insteruction_head,1);	
                  return;
		}
	     else
	        {	
		  mask3 = 8; /* 0100 - non direct register*/
                  mask3 = mask3 << 3; /* Shift to bits 3-6*/
                  mask1= mask3 | mask1; /* Combine with the opcode*/
                  set_binary(mask1, insteruction_head, 2);
		  num2 = atoi(str3 + 1);
	          num2 = num2 << 3;
	          num1 = num1 | num2;
                  set_binary(num1, insteruction_head,1);	
                  return;
		}
	}
    }
    else /*Direct addressing (label)*/
    {
        mask2 = 2; /* 0010 - direct*/
        mask2 = mask2 << 7; /* Shift to bits 7-10*/
        mask1 = mask2 | mask1;/* Combine with the opcode*/
        binary(mask1, insteruction_head );
        addInstructions(insteruction_head, "??????????????");
    }

    if (str3[0] == '#') /*If the second parameter is a number*/
    {
        mask3 = 1; /* 0001 - number*/
        mask3 = mask3 << 3;
	mask1= mask1 | mask3;
        set_binary(mask1, insteruction_head, 2);
	num1 = atoi(str3 + 1);
        num1 = num1 << 3;
	num1 = mask4 | num1;
        binary(num1, insteruction_head);
    }
    else if (str3[0] == 'r' && flag==0) /*If the second parameter is a register*/
    {
        mask3 = 8; /* 1000 - register direct*/
        mask3 = mask3 << 3; /* Shift to bits 3-6*/
        mask1= mask1 | mask3; /* Combine with the opcode*/
        set_binary(mask1, insteruction_head, 2);
	num1 = atoi(str3 + 1);
	num1 = num1 << 3;
	num1 = mask4 | num1;
        binary(num1, insteruction_head);
	
    }
    else if (str3[0] == '*' && str3[1]== 'r' && flag==0) /*If the first parameter is a non direct register*/
    {
        mask3 = 4; /* 0100 - non direct register*/
        mask3 = mask3 << 3; /* Shift to bits 3-6*/
        mask1= mask3 | mask1; /* Combine with the opcode*/
        set_binary(mask1, insteruction_head, 2);
	num1 = atoi(str3 + 2);
	num1 = num1 << 3;
	num1 = mask4 | num1;
        binary(num1, insteruction_head);
    }
    else /*Direct addressing (label)*/
    {
        mask3 = 2; /* 0010 - direct*/
        mask3=mask3 << 3;/* Shift to bits 3-6*/
        mask1=mask3 | mask1;/* Combine with the opcode*/
        set_binary(mask1, insteruction_head,2);
        addInstructions(insteruction_head, "??????????????");
    }
    printf(" ");
}





void one_parameter(int str1, char str2[], instructionsTable** insteruction_head)
{
   short mask1, mask2, mask4;
    int num1=0;
    mask1 = str1 << 11; /* shifts the label name by 11 bits for the opcode to be in bits 11 to 14*/
    mask2 = 0; /* Source operand addressing mode (bits 10-7)*/
    mask4 = 1;
    mask4 = mask4 << 2; /* A = 1, R = 0, E = 0*/
    mask1 = mask1 | mask4;
    if (str2[0] == '#') /*If the first parameter is a number*/
    {
        mask2 = 1; /* 0001 - number*/
        mask2 = mask2 << 3;
        mask1 = mask1 | mask2;
        binary(mask1, insteruction_head); /* Add the first part of the instruction*/
	num1 = atoi(str2 + 1);
        num1 = num1 << 3;
	num1 = mask4 | num1;
        binary(num1, insteruction_head);
    }
    else if (str2[0] == 'r') /*If the first parameter is a register*/
    {
        mask2 = 8; /* 1000 - register direct*/
        mask2 = mask2 << 3; /* Shift to bits 3-6*/
        mask1= mask2 | mask1; /* Combine with the opcode*/
        binary(mask1, insteruction_head);
	num1 = atoi(str2 + 1);
	num1 = num1 << 3;
	num1 = mask4 | num1;
        binary(num1, insteruction_head);
    }
    else if (str2[0] == '*' && str2[1]== 'r') /*If the first parameter is a non direct register*/
    {
        mask2 = 4; /* 0100 - non direct register*/
        mask2 = mask2 << 3; /* Shift to bits 3-6*/
        mask1= mask2 | mask1; /* Combine with the opcode*/
        binary(mask1, insteruction_head);
	num1 = atoi(str2 + 2);
	num1 = num1 << 3;
	num1 = mask4 | num1;
        binary(num1, insteruction_head);
    }
    else /*Direct addressing (label)*/
    {
        mask2 = 2; /* 0010 - direct*/
        mask2 = mask2 << 3; /* Shift to bits 3-6*/
        mask1 = mask2 | mask1;/* Combine with the opcode*/
        binary(mask1, insteruction_head);
        addInstructions(insteruction_head, "??????????????");
    }
    printf( " ");

}


void data_code(int arr[], int length, dataTable** data_head)
{
    int i;
    for (i = 0; i < length; i++)
    {
        binary_data((short)arr[i], data_head); /* Convert each integer in the array to binary and add it to the data table */
    }
}

void string_code(char* string, dataTable** data_head)
{
    int i;
    for (i = 0; i < strlen(string); i++)
    {
        binary_data((short)string[i], data_head); /* Convert each character in the string to binary and add it to the data table */
    }
    binary_data(0, data_head); /* Add a null terminator to the data table to indicate the end of the string */
}



void zero_parameter(int str1, instructionsTable** insteruction_head)
{
    short mask1, mask2;  
     mask1 = str1 << 11; /* shifts the label name by 11 bits for the opcode to be in bits 11 to 14*/
     mask2 = 1 << 2; /* A = 1, R = 0, E = 0*/
     mask1 = mask1 | mask2;
     binary(mask1, insteruction_head); /* Add the first part of the instruction*/	
 
}


int update_adress_label(char label_name[LABEL_LENGTH], labelTable* head, int count_line, instructionsTable** insteruction_head, int L)
{
    if (find_label(head, label_name) == 0)
    {
        /* Label not found, print error and return 0 */
        printError(14, count_line);
        return 0;
    }
    else
    {
        int i;
        int adress = find_adress_label(head, label_name); /* Get the address of the label */
        int length = num_of_cells(*insteruction_head);   /* Get the current number of cells in the instructions table */

        /* Set the binary representation of the address with a specific format */
        set_binary((adress << 3) | 2, insteruction_head, length - L);

        /* Clear the label name array */
        for (i = 0; i < LABEL_LENGTH; i++)
            label_name[i] = '\0';

        return 1; /* Return 1 if the address was successfully updated */
    }
}

int is_exist_label(char label_name[LABEL_LENGTH], labelTable* head, int count_line)
{
    if (find_label(head, label_name) == 0)
    {
        /* Label not found, print error and return 0 */
        printError(14, count_line);
        return 0;
    }
    return 1; /* Return 1 if the label exists */
}






int find_number(char* cp, int count_line)
{
    int number,  i = 0,count3 = 0; /*the value of count3 is 1 if the number is invalid and 0*/
    number = atoi(cp);
    while ((cp[i]) != '\n')
    {
        i++;  /*i count the length of the pointer till \n */
    }
    count3 = Invaild_number(cp, number, i, count_line);
    return count3;
}




int find_end_label(char* cp, int count_line)
{
    int i=0 ,count3 = 0 ; /*the value of count3 is 1 if the label is invalid and 0*/
    while ((cp[i]) != '\n')
    {
        i++; /*i count the length of the pointer till \n */
    }
    count3 = Invaild_label(cp, i, count_line);
    return count3;
}





int find_number_kfiza(char* cp, int count_line)
{
    int number, count3 = 0, i = 0; /*the value of count3 is 1 if the number is invalid and 0*/
    number = atoi(cp);
    if (strchr(cp, ')') != NULL)
    {
        while ((cp[i]) != ')')
        {
            i++; /*i count the length of the pointer till ) */
        }
        count3 = Invaild_number(cp, number, i, count_line);
        return count3;
    }
    else
        return 1;
}



int find_number_before_comma(char* cp, int count_line)
{
    int number, count3 = 0, i = 0; /*the value of count3 is 1 if the number is invalid and 0*/
    number = atoi(cp);
    if (strchr(cp, ',') != NULL)
    {
        while ((cp[i]) != ',')
        {
            i++;  /*i count the length of the pointer till comaa */
        }
        count3 = Invaild_number(cp, number, i, count_line);
        return count3;
    }
    else
        return 0;
}





int find_label_before_comma(char* cp, int count_line)
{
    int count3 = 0, i = 0; /*the value of count3 is 1 if the number is invalid and 0*/
    if (strchr(cp, ',') != NULL)
    {
        while ((cp[i]) != ',')
        {
            i++; /*i count the length of the pointer till comma */
        }
        count3 = Invaild_label(cp, i, count_line);
        return count3;
    }
    else
        return 0;
}




int Invaild_number_of_data(char cp[], int number, int count_line)
{
    int w, count3 = 1, count1 = 0, i = 0, count4 = 1; 
    for (w = 0; w < strlen(cp); w++)
        if ((isdigit(cp[w])) == 0 && cp[w] != '\n' && !(w == 0 && (cp[0] == '+' || cp[0] == '-')))
        {
            count1++;  /* count1 Counts the number of times there is a character in the pointer that is not a number*/
            break;
        }
    /*Checks if the last character that is not a number or letter -  is profit .If the character is not a space then the label is invalid
      Otherwise it continues to check that all characters after it are spaces Otherwise the label is invalid*/
    if (cp[w] == ' ')
    {
        count4 = 0;  
        i = w + 1;
        while (cp[i] != '\0')
        {
            if (cp[i] != ' ' && cp[i] != '\n')
            {
                count4++; /*count4 Counts the number of times the pointer has a non-digit character after a space*/
                break;
            }
            i++;
        }
    }

/* Checking if the length of the number is valid That is, is the number in the range between -8192 and 8191*/
    if ((number < MIN_DATA_NUMBER) || (number > MAX_DATA_NUMBER))
    {
        printError(16, count_line);
        count3 = 0;
    }
    else if (count1 != 0 && count4 != 0) /*If an invalid non-whitespace character is found*/
    {
        printError(17, count_line);
        count3 = 0;
    }
    return count3;
}





int Invaild_label(char cp[], int length, int count_line)
{
    int w, count3 = 1, count1 = 0, i = 0, count4 = 1;
   /* cp=strtok(cp, space);*/	
    while(isspace(*cp))
	cp++;
    if (!isalpha(*cp))
    {
        printError(2, count_line);
        return 0;
    }
    for (w = 1; w < length; w++)
    {
        if ((!isdigit(cp[w])) && !isalpha(cp[w]) && cp[w] != '\n')
        {
            count1++; /* count1 Counts the number of times there is a character in the pointer that is not a number*/
            break;
        }
     }
     /*Checks if the last character that is not a number -  is profit .If the character is not a space then the number is invalid
      Otherwise it continues to check that all characters after it are spaces Otherwise the number is invalid*/
    if (cp[w] == ' ')
    {
        count4 = 0;
        i = w + 1;
        while (i < length)
        {
            if (cp[i] != ' ' && cp[i] != '\n' && cp[i] != '\0')
            {
                count4++; /*count4 Counts the number of times the pointer has a non-digit or letter character after a space*/
                break;
            }
            i++;
        }
    }
    if(w>LABEL_LENGTH) /*If the length of the label big than 31*/
    {
      printError(23, count_line);
      count3 = 0;
    }
   else if (count1 != 0 && count4 != 0 ) /*If an invalid non-whitespace character is found*/
    {
        printError(2, count_line);
        count3 = 0;
    }
    return count3;
}






int Invaild_number(char cp[], int number, int length, int count_line)
{
    int w, count3 = 1, count1 = 0, i = 0, count4 = 1;
    for (w = 0; w < length; w++)
        if ((isdigit(cp[w])) == 0 && cp[w] != '\n' && !(w == 0 && (cp[0] == '+' || cp[0] == '-')))
        {
            count1++; /* count1 Counts the number of times there is a character in the pointer that is not a number*/
            break;
        }

    /*Checks if the last character that is not a number -  is profit .If the character is not a space then the number is invalid
      Otherwise it continues to check that all characters after it are spaces Otherwise the number is invalid*/
    if (cp[w] == ' ')
    {
        count4 = 0;
        i = w + 1;
        while (i < length)
        {
            if (cp[i] != ' ' && cp[i] != '\n')
            {
                count4++;  /* count4 Counts the number of times the pointer has a non-digit character after a space*/
                break;
            }
            i++;
        }
    }

    /* Checking if the length of the number is valid That is, is the number in the range between -2048 and 2047*/
    if ((number < MIN_NUMBER) || (number >  MAX_NUMBER)) 
    {
        printError(16, count_line);
        count3 = 0;
    }
    else if (count1 != 0 && count4 != 0) /*If an invalid non-whitespace character is found*/
    {
        printError(17, count_line);
        count3 = 0;
    }
    return count3;
}


