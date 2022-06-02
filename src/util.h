/*
 * FILE: util.h
 * AUTHOR: Vansitha Induja Ratnayake
 * UNIT: Unix Systems Programming COMP2002
 * PURPOSE: Contains function declarations and constants used in util.c
 * REFERENCE: None
 * COMMENTS: None
 * LAST MOD: 29/05/2022
 */

#ifndef UTIL_H
#define UTIL_H

#define REQ_ARG_LEN 2
#define NO_ARGS 1
#define FILENAME_LEN 20
#define STR_LEN 6

void getCommandLineArgs(int argc, char **argv, char **getFileName);
void generateOutFileName(int outFileCount, char **getFileName);
int getStrLen(char *string);

#endif