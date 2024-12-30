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

#endif /* MESSAGES_H */