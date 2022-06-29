/*
 * FILE: fileIO.h
 * AUTHOR: Vansitha Induja Ratnayake
 * UNIT: Unix Systems Programming COMP2002
 * PURPOSE: Contains function declarations and constants for
 *          reading and writing to files
 * REFERENCE: None
 * COMMENTS: None
 * LAST MOD: 29/05/2022
 */


#ifndef FILEIO_H
#define FILEIO_H
#include "linkedList.h"

#define ERROR -1
#define BUFFER_SIZE 200
#define FIRST_COMMAND 1

void extractCommands(char *fileName, LinkedList *ll);
void executeFirstCommand(char *command, int outputFileCount);
void executeCommand(char *command, int outputFileCount);
int checkFileExists(char *filename);

#endif
