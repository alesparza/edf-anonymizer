#include "commandline.h"

void printPrompt() {
    printf("%s", PROMPT_STRING);
}

char* getInput() {
    char buffer[1024];
    memset(buffer, '\0', sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);
    int length = strlen(buffer);
    if ((length > 0) && (buffer[length - 1]) == '\n') {
        buffer[length - 1] = '\0';
    }
    char* ret = malloc(strlen(buffer) * sizeof(char) + 1);
    strncpy(ret, buffer, strlen(buffer));
    return ret;
}

void printWelcome() {
    printf("Welcome to EDF anonymizer\n");
}

void printMain(char* filename) {
    if (filename != NULL) {
        printf("Current open file is %s\n", filename);
    }
    printf("Please select an option:\n");
    printf("\t%d %s\n", EXIT_VAL, EXIT_STRING);
    printf("\t%d %s\n", LOAD_VAL, LOAD_STRING);
    if (filename != NULL) {
        printf("\t%d %s\n", MODIFY_VAL, MODIFY_STRING);
        printf("\t%d %s\n", SAVE_VAL, SAVE_STRING);
    }
}

void printNotNumber(char* string) {
    printf("ERROR: '%s' is not a number!  Please try again.\n", string);
}

void printUnknownOption(int option) {
    printf("ERROR: Unknown option '%d'!  Please try again.\n", option);
}

void printNoOpenFile() {
    printf("ERROR: No file currently open!  Please load a file first.");
}