#ifndef EDFANONYMIZE_H
#define EDFANONYMIZE_H

#define DEID_FILE_SUFFIX "_deid"
#define EDF_EXTENSION ".edf"
#define DEID_EDF_EXTENSION "_deid.edf"
#define HEADER_LENGTH 16

/**
* Prints a single row of binary data from a files
*/
void printBinaryRow(int i, FILE* file);


/**
* Prints a mini hex deump of a file.
* 
* Prints the first 256 bytes which is the header
*/
void miniHexDump(char* filename);

/**
* Sets the output filename.
* 
* If the input is test.edf, then the output is test_deid.edf
*/
char* setOutputFilename(char* inputFileName);

#endif /* EDFANONYMIZE_H */