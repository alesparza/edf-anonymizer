#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// values for main menu options and values
#define EXIT_STRING "Exit"
#define EXIT_VAL 1
#define LOAD_STRING "Load a .edf file"
#define LOAD_VAL 2
#define MODIFY_STRING "Modify the header"
#define MODIFY_VAL 3
#define SAVE_STRING "Write to a new file"
#define SAVE_VAL 4

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
 * Prints the main loop options.
 */
void printMain(char* filename);

#endif /* COMMANDLINE_H */