#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <stdio.h>

/*
* Prompt stuff.
*/

#define PROMPT_STRING "==> "

/**
 * Print the prompt string.
 */
void printPrompt();


/*
* Welcome message stuff 
*/

#define WELCOME_EXIT_STRING "Exit"
#define WELCOME_EXIT_VAL 0
#define WELCOME_LOAD_STRING "Load a .edf file"
#define WELCOME_LOAD_VAL 1

/**
 * Print a welcoming string to get started.
 */
void printWelcome();






/*
* Miscellaneous messages
*/

/**
 * Print a retry message, and indicate which option was not valid.
 */
void printRetry(int option);

#endif /* COMMANDLINE_H */