#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// values for menu options and values
#define EXIT_STRING "Exit"
#define EXIT_VAL 1
#define LOAD_STRING "Load a .edf file"
#define LOAD_VAL 2
#define MODIFY_STRING "Modify the header"
#define MODIFY_VAL 3
#define SAVE_STRING "Write to a new file"
#define SAVE_VAL 4

#define PROMPT_STRING "==> "

/**
 * Gets input from the user.
 */
char* getInput();

/**
 * Print the prompt string.
 */
void printPrompt();

/**
 * Print a welcoming message.
 */
void printWelcome();

/**
 * Prints the main loop options.
 */
void printMain(char* filename);

/*
* Error messages
*/

/**
 * Print a message indicating the input is not a valid option, and indicate which option was not valid.
 */
void printUnknownOption(int option);

/**
 * Print a message indicating the input is not a number.
 */
void printNotNumber(char* string);

#endif /* COMMANDLINE_H */