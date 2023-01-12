#ifndef EDFANONYMIZE_H
#define EDFANONYMIZE_H

#define DEID_FILE_SUFFIX "_deid"
#define EDF_EXTENSION ".edf"
#define DEID_EDF_EXTENSION "_deid.edf"
#define HEADER_LENGTH 16

/**
* Sets the output filename.
* 
* If the input is test.edf, then the output is test_deid.edf
*/
char* setOutputFilename(char* inputFileName);

#endif /* EDFANONYMIZE_H */