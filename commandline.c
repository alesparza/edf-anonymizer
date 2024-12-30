#include "commandline.h"

void printPrompt() {
    printf("%s", PROMPT_STRING);
}

char* getInput() {
    char buffer[COMMANDLINE_BUFFER_SIZE];
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


void printFilenameInput() {
    printf("Please enter the filename to load.\n");
}
