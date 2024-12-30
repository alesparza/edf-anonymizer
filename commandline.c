#include "commandline.h"

void printPrompt() {
    printf("%s", PROMPT_STRING);
}

void printWelcome() {
    printf("Welcome to EDF anonymizer\n");
    printf("Please select an option:\n");
    printf("\t%d %s\n", WELCOME_EXIT_VAL, WELCOME_EXIT_STRING);
    printf("\t%d %s\n", WELCOME_LOAD_VAL, WELCOME_LOAD_STRING);
}













void printRetry(int option) {
    printf("Unknown option '%d', please try again", option);
}