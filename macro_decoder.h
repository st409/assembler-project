#ifndef MACRO_DECODER_H
#define MACRO_DECODER_H

#include "macro_manager.h"
#include "primary_pass.h"

/******************************************************************************
The function receives a pointer to the source file and a pointer to the file name.
The function creates a new file named as the file name received as a parameter with the .am extension 
and writes the source file into it after the macros are removed.
*******************************************************************************/
void macro_retirement(FILE * as_file, char* as_name); 

#endif
