#ifndef EDFANONYMIZE_H
#define EDFANONYMIZE_H

#include "edf-header.h"

#define DEID_FILE_SUFFIX "_deid"
#define EDF_EXTENSION ".edf"
#define DEID_EDF_EXTENSION "_deid.edf"
#define MINIMUM_ARGUMENTS 1
#define BUFFER_SIZE 1024


/**
* Prints a help message for how to use this program.
*/
void printHelp();

/**
* Prints a verbose help message for how to use this program.
*/
void printVerboseHelp();


/**
* Gets the input file name from the user
*/
char* getInputName();

/**
* Reads the static portion of the header into memory
*/
void readStaticHeader(StaticHeader* header, FILE* input);

/**
* Sets the output filename.
* 
* If the input is test.edf, then the output is test_deid.edf
*/
char* setOutputFilename(char* inputFileName);

/*
* Gets user prompt, then appends to a current response.
*
* If user presses enter without data, returns "X ".
*
* The current response should be large enough to hold the user input.
*/
char* appendPromptResponse(char* currentResponse);

/**
* Checks if the length of data is within the specifications.
*
* Prints a warning that the data will be truncated.
*/
void checkLength(char* data);

/**
* Prints "Exiting..., waits for user to press key, then exits with code
*/
void printAndExit(int exitCode);

#endif /* EDFANONYMIZE_H */
