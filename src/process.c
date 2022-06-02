/*
 * FILE: process.c
 * AUTHOR: Vansitha Induja Ratnayake
 * UNIT: Unix Systems Programming COMP2002
 * PURPOSE: Create and handle child processes and 
 *          contains speicif functions required by them 
 * REFERENCE: None
 * COMMENTS: None
 * LAST MOD: 29/05/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "linkedList.h"
#include "fileIO.h"
#include "util.h"
#include "process.h"

/*
 * NAME: runBashCommands
 * PURPOSE: Creates child processes for each node in the linked list and executes
 * IMPORTS: ll (struct for linedlist)
 * EXPORTS: None
 * ASSERTIONS:
 *      PRE: Calling function needs to initalize the linked list and add the data
 *           to it before callling this function
 *      POST: Complete exeuction of all commands and output each exeuction to file
 * REMARKS: None
 */
void runBashCommands(LinkedList *ll)
{
    int pid;
    ListNode *currNode = ll->head;
    char *command = NULL;

    /* outputFileCount will be number of the output files created by each process 
    initially it is set to 1 */
    int outputFileCount = FIRST_COMMAND;      

    while(currNode != NULL)
    {
        // create child process and execute command in node
        pid = fork();
        if (pid == 0)
        {
            command = (char *)currNode->data;
            displayBashCommands(command, currNode, outputFileCount);
            executeCommand(command, outputFileCount);
            exit(0);
            
        }
        // parent process waits for child to finish and outputs results
        else if (pid > 0)
        {   
            pid = wait(NULL);
            currNode = currNode->next;
            if (currNode == NULL)
            {
                char *finalFileName = NULL;
                generateOutFileName(outputFileCount, &finalFileName);
                runCatCommand(finalFileName);
            }
            outputFileCount++;
        }
        else
        {
            printf("Creation of child process failed!\n");
        }
    }
}

/*
 * NAME: runCatCommand 
 * PURPOSE: runs cat <final-output-file.txt> to display the results of the final 
 *          exeuction
 * IMPORTS: filename (string)
 * EXPORTS: None
 * ASSERTIONS:
 *      PRE: Execute the bash commands first to create the final output file 
 *      POST: Display the result of execution in terminal
 * REMARKS: None
 */
void runCatCommand(char *filename)
{
    // stores the entire cat command with the file name
    char catCommandBuffer[COMMAND_BUFFER_MAX];

    catCommandBuffer[0] = 'c';
    catCommandBuffer[1] = 'a';
    catCommandBuffer[2]= 't';
    catCommandBuffer[3] = ' '; 

    int i;
    int count = 0;
    for (i = 0; i < getStrLen(filename); i++)
    {
        //append the file name to buffer
        catCommandBuffer[CAT_COMMAND_END + count] = filename[count];
        count++;
    }
    catCommandBuffer[CAT_COMMAND_END + count] = '\0';
    printf("Output For Execution: \n");
    printf("---------------------\n");
    system(catCommandBuffer);
}

/*
 * NAME: displayBashCommands
 * PURPOSE: Display each command that was executed by a process
 * IMPORTS: command (string), currNode (struct to a single listNode),
 *          commandCount (integer)
 * EXPORTS: None
 * ASSERTIONS:
 *      PRE: linked list needs to be initalised with the commands
 *      POST: Display the command executed in an understandable manner
 *            for the user
 * REMARKS: None
 */
void displayBashCommands(char *command, ListNode *currNode, int commandCount)
{
    if (commandCount == FIRST_COMMAND)
    {
        printf("Executed Bash Command: ");
    }
    if (currNode->next != NULL)
    {
        printf("%s | ", command);
        fflush(stdout);
    }
    else
    {
        printf("%s \n", command);
    }
}