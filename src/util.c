/*
 * FILE: util.c
 * AUTHOR: Vansitha Induja Ratnayake
 * UNIT: Unix Systems Programming COMP2002
 * PURPOSE: Contains additional helper functions for the 
 *          program since library calls cannot be used
 * REFERENCE: None
 * COMMENTS: None
 * LAST MOD: 29/05/2022
 */

#include <stdio.h>
#include "util.h"

/*
 * NAME: getCommandLineArgs
 * PURPOSE: Get filename from command line 
 * IMPORTS: argc (integer), argv and getFileName (pointers to a an array), 
 * EXPORTS: None
 * ASSERTIONS:
 *      PRE: None
 *      POST: Get file name or display appproiate error message
 * REMARKS: None
 */
void getCommandLineArgs(int argc, char **argv, char **getFileName)
{
    char *fileName = NULL;
    if (argc == REQ_ARG_LEN)
    {
        fileName = argv[1];
    }
    else if (argc == NO_ARGS)
    {
        printf("No arguments provided!\n");
        printf("Usage: ./pipesim <input_file>\n");
    }
    else
    {
        printf("Too many arguments provided!\n");
        printf("Usage: ./pipesim <input_file>\n");
    }

    *getFileName = fileName;
}

/*
 * NAME: generateOutFileName
 * PURPOSE: generate a file name with its extension in the following format
 *          "input<required-number>.txt"
 * IMPORTS: outFileCount (integer), getFileName (pointer to an array)
 * EXPORTS: None
 * ASSERTIONS:
 *      PRE: None
 *      POST: Sets the getFileName pointer parameter to the generated 
 *            filename
 * REMARKS: None
 */
void generateOutFileName(int outFileCount, char **getFileName)
{
   char outFileName[FILENAME_LEN];
   char outputCharArr[STR_LEN] = {'o', 'u', 't', 'p', 'u', 't'};

   int i;
   for(i = 0; i < STR_LEN; i++)
   {
       // append the word "output"
       outFileName[i] = outputCharArr[i];

       /* if at the end of the string append the file extension 
       and null terminator */
       if (i == (STR_LEN - 1))
       {
           outFileName[i + 1] = outFileCount + '0';
           outFileName[i + 2] = '.';
           outFileName[i + 3] = 't';
           outFileName[i + 4] = 'x';
           outFileName[i + 5] = 't';
           outFileName[i + 6] = '\0';
       }
   }
   
   // set pointer
   *getFileName = outFileName;

}

/*
 * NAME: getStrLen
 * PURPOSE: calculates a length of a given string 
 * IMPORTS: string (pointer to an array)
 * EXPORTS: None
 * ASSERTIONS:
 *      PRE: None
 *      POST: returns total number of characters in the string 
 *            till null terminator
 * REMARKS: None
 */
int getStrLen(char *string)
{
    int index = 0;
    while (string[index] != '\0')
    {
        index++;

    }

    return index;
}