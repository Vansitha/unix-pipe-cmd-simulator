/*
 * FILE: process.h
 * AUTHOR: Vansitha Induja Ratnayake
 * UNIT: Unix Systems Programming COMP2002
 * PURPOSE: Contains the function declarations and constants 
 *          for process.c
 * REFERENCE: None
 * COMMENTS: None
 * LAST MOD: 29/05/2022
 */

#ifndef CHILDPROCESS_H
#define CHILDPROCESS_H
#include "linkedList.h"

#define COMMAND_BUFFER_MAX 30
#define CAT_COMMAND_ARR 3
#define CAT_COMMAND_END 4

void runBashCommands(LinkedList *ll);
void displayBashCommands(char *command, ListNode *currNode, int commandCount);
void runCatCommand(char *filename);

#endif