#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messages.h"

// values for main menu options and values
#define EXIT_STRING "Exit"
#define EXIT_VAL 1
#define LOAD_STRING "Load a .edf file"
#define LOAD2_STRING "Load a different .edf file"
#define LOAD_VAL 2
#define VIEW_STRING "View header contents"
#define VIEW_VAL 3
#define MODIFY_STRING "Modify the header"
#define MODIFY_VAL 4
#define SAVE_STRING "Write to a new file"
#define SAVE_VAL 5


#define PROMPT_STRING "==> "
#define COMMANDLINE_BUFFER_SIZE 1024

/**
 * Gets input from the user.
 */
char* getInput();

/**
 * Print the prompt string.
 */
void printPrompt();

/**
 * Validates that an input is numeric.
 * Returns 0 is not a number, otherwise returns the number.
 */
int validateNumericInput(char* input);

/**
 * Prints the main loop options.
 */
void printMain(char* filename);

#endif /* COMMANDLINE_H */