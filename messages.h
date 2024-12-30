#ifndef MESSAGES_H
#define MESSAGES_H

#include <stdio.h>

/**
 * Print a welcoming message.
 */
void printWelcome();

/**
 * Print a message indicating the input is not a valid option, and indicate which option was not valid.
 */
void printUnknownOption(int option);

/**
 * Print a message indicating the input is not a number.
 */
void printNotNumber(char* string);

/**
 * Print a message indicating a file is not loaded yet.
 */
void printNoOpenFile();

/**
 * Print a message asking for a filename.
 */
void printFilenameInput();

/**
 * Print a message indicating the file could not be opened. 
 */
void printFileUnopenable(char* filename);

#endif /* MESSAGES_H */