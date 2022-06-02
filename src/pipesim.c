/*
 * FILE: pipesim.c
 * AUTHOR: Vansitha Induja Ratnayake
 * UNIT: Unix Systems Programming COMP2002
 * PURPOSE: Contains driver program
 * REFERENCE: None
 * COMMENTS: None
 * LAST MOD: 29/05/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "linkedList.h"
#include "util.h"
#include "process.h"

/*
 * NAME: main
 * PURPOSE: Entry point for the program
 * IMPORTS: argc (integer), argv (string)
 * EXPORTS: None
 * ASSERTIONS:
 *      PRE: None
 *      POST: Display output for the executed commands 
 * REMARKS: None
 */
int main(int argc, char **argv)
{
    LinkedList *ll = NULL;
    char *filename = NULL;

    getCommandLineArgs(argc, argv, &filename);

    if (filename != NULL && checkFileExists(filename) > 0)
    {
        ll = createLinkedList();
        extractCommands(filename, ll);
        runBashCommands(ll);

        // free linked list
        freeLinkedList(ll, freeData);
        ll = NULL;
    }
    else if (argc == 2)
    {
        printf("'%s' file does not exist!\n", filename);
    }
    return 0;
}