/******************************************************************************
              MMN14 - final project - 2024B - 30/07/2024
The authors of the project:
Esti Hoba - 326041159 
Batsheva Rosenblum - 214725251  
*******************************************************************************/
#include "macro_decoder.h"
int main(int argc,char* argv[])
{
    FILE* ifp;
    int i,j;
    char full_name[MAX_NAME_FILE]={'\0'}; /*The name of the file to compile includes the suffix as*/
    if(argc==1) /*Checking that at least one file was inserted there for compilation*/
    {
	      fprintf(stderr,"no arguments only program name\n");
          return 0;
    }
    for(i = 1; i< argc; i++) /*Go to the command line and read the names of the files inserted into the folder*/
	{
            for(j=0;j<MAX_NAME_FILE;j++)/*Reset filename to pick up a new filename*/
               full_name[j]='\0';
            strcpy(full_name, *(argv+i)); /*Copying the file name from the command line to the full_name variable*/
	        strcat(full_name, ".as"); /*Adding an as suffix to the full_name variable*/
	        if ((ifp=fopen(full_name,"r")) == NULL)/*Checks if the file was opened successfully*/
		    {
		        fprintf(stderr,"Cannot open file %s\n",full_name);
			exit(0);
		    }
           else
	            macro_retirement(ifp,full_name); /*Sending a pointer to the source file and the name of the file to the function that interprets the macros*/
           fprintf(stdout, "Finishing work on a file %s\n\n\n",full_name);
    }
    return 0;
}

