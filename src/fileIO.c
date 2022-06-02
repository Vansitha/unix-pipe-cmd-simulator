/*
 * FILE: fileIO.c
 * AUTHOR: Vansitha Induja Ratnayake
 * UNIT: Unix Systems Programming COMP2002
 * PURPOSE: Contains function implementations for 
 *          reading and writing to files
 * REFERENCE: None
 * COMMENTS: None
 * LAST MOD: 29/05/2022
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "fileIO.h"
#include "util.h"

/*
 * NAME: extractCommands
 * PURPOSE: Reads the initial input file with commands
 * IMPORTS: filename (String) ll (pointer to Linkedlist struct)
 * EXPORTS: None
 * ASSERTIONS:
 *      PRE: Assumes that each commands in the input file is 
 *           separated by a new line character and is a valid command
 *      POST: Access to linked list with a node for each bash command 
 *            read from file
 * REMARKS: None
 */
void extractCommands(char *fileName, LinkedList *ll)
{
    int fileDescriptor = ERROR;
    char buffer[BUFFER_SIZE] = "";
    int fileStatus = 0;
    int bytesRead = 0;


    // open the file from reading only
    fileDescriptor = open(fileName, O_RDONLY);

    if (fileDescriptor == ERROR)
    {
        printf("Could not open file: %s\n", fileName);
    }
    else
    {
        
        bytesRead = read(fileDescriptor, &buffer, sizeof(buffer));
        // inserts null terminator after all the bytes are read
        buffer[bytesRead + 2] = '\0';
    }

    /* 
    Unfortunately could not implement my own version of strtok therefore used 
    built in library function.
    Tokenize the data read from the file and insert each tokenized command as
    an individual node into the linked list
    */
    char *token = strtok(buffer, "\n");
    while (token != NULL)
    {
        insertLast(ll, strdup(token));
        token = strtok(NULL, "\n");
    }

    // closing file
    fileStatus = close(fileDescriptor);
    if (fileStatus == ERROR)
    {
        printf("Failed to close file!\n");
    }

}

/*
 * NAME: checkFileExists 
 * PURPOSE: Used to check whether a file exists in the current directory
 * IMPORTS: filename (string)
 * EXPORTS: fileDescriptor (integer)
 * ASSERTIONS:
 *      PRE: Assumed that invalid command line arguments are handled by the 
 *           calling function
 *      POST: Returns and error code if the file does not exist or the actual 
 *            filedescriptor if it does exist
 * REMARKS: None
 */
int checkFileExists(char *filename)
{
    int fileDescriptor = ERROR;
    fileDescriptor = open(filename, O_RDONLY);

    return fileDescriptor;
}

/*
 * NAME: executeCommand 
 * PURPOSE: Responsible for reading the previous output file, executing the command 
 *          and redirecting the output into another output file. File format of the 
 *          output file is "output<number>.txt".
 * IMPORTS: command (string), outputFileCount (integer)
 * EXPORTS: none
 * ASSERTIONS:
 *      PRE:  Calling function needs to track the number of commands already 
 *            executed
 *      POST: Bash command executed and output from it saved into a new file as 
 *            mentioned above.
 * REMARKS: None
 */
void executeCommand(char *command, int outputFileCount)
{
    int readFileDescriptor = ERROR;

    // additional check to see whether its the first command being executed or not
    if (outputFileCount > 1)
    {
        char *prevProcessOutFile = NULL;
        // generate the name of the previous output file that was created
        generateOutFileName(outputFileCount - 1, &prevProcessOutFile);
        readFileDescriptor = open(prevProcessOutFile, O_RDONLY);
    }
    else
    {
        // runs if this is the first command being exeuctued from the linked list
        executeFirstCommand(command, outputFileCount);
    }
    
    // if the previous block of code has an error and not the intital execution
    if ((outputFileCount > 1) && (readFileDescriptor == ERROR))
    {
        printf("An error occurred while opening file to read!\n");
    }
    else
    {
        char *outFilename;
        generateOutFileName(outputFileCount, &outFilename);

        // read, write and execute permission for all users
        const int permissons = 0777;

        // create a new file with the new output file name generated
        int writeFileDescriptor = open(outFilename, O_WRONLY | O_CREAT, permissons);

        if (writeFileDescriptor == ERROR)
        {
            printf("An error occurred while opening file to write!\n");
        }
        else
        {
            /* set the read and write buffers to the two input and output files and 
            once execution is complete flush the buffer to the ouput file */
            dup2(readFileDescriptor, STDIN_FILENO);
            dup2(writeFileDescriptor, STDOUT_FILENO);
            system(command);
            fflush(stdout);
            close(writeFileDescriptor); 
            // NOTE: read fd is not closed since it automatically closes
        }
    }
}

/*
 * NAME: executeFirstCommand
 * PURPOSE: Acts as helper function for executeCommand
 * IMPORTS: command (string), outputFileCount (integer)
 * EXPORTS: none
 * ASSERTIONS:
 *      PRE:  Calling function needs to track the number of commands already
 *            executed
 *      POST: Executes first bash command and output from it saved into a new file
 *            callled output1.txt (name can change based on the name geerator function)
 * REMARKS: None
 */
void executeFirstCommand(char *command, int outputFileCount)
{
    // generate output file name based on current count
    char *outFilename;
    generateOutFileName(outputFileCount, &outFilename);

    // read, write and execute permission for all users
    const int permissons = 0777;

    // create a new file with the new output file name generated
    int writeFileDescriptor = open(outFilename, O_WRONLY | O_CREAT, permissons);

    if (writeFileDescriptor == ERROR)
    {
        printf("An error occurred while opening file to write!\n");
    }
    else
    {
        // duplicate stdout fd and replace with file and flush the output to the file
        dup2(writeFileDescriptor, STDOUT_FILENO);
        system(command);
        fflush(stdout);
        close(writeFileDescriptor);
        // NOTE: read fd is not closed since it automatically closes
    }
}