#include "messages.h"

void printWelcome() {
    printf("Welcome to EDF anonymizer\n");
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

void printFilenameInput() {
    printf("Please enter the filename to load.\n");
}

void printFileUnopenable(char* filename) {
    printf("Unable to open file '%s'.  Please check spelling and extension inclusion.\n", filename);
}
