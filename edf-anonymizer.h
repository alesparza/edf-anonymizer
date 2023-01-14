#ifndef EDFANONYMIZE_H
#define EDFANONYMIZE_H

#define DEID_FILE_SUFFIX "_deid"
#define EDF_EXTENSION ".edf"
#define DEID_EDF_EXTENSION "_deid.edf"
#define MINIMUM_ARGUMENTS 1
#define HEADER_LENGTH 16
#define LOCAL_PATIENT_IDENFITICATION_LENGTH 80
#define BUFFER_SIZE 1024
#define VERSION_LENGTH 8


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
* Sets the output filename.
* 
* If the input is test.edf, then the output is test_deid.edf
*/
char* setOutputFilename(char* inputFileName);

#endif /* EDFANONYMIZE_H */