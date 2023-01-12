#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edf-anonymizer.h"
#include "mini-hexdump.h"


char* setOutputFilename(char* inputFileName) {
  char* outputFileName = malloc(sizeof(char) * strlen(inputFileName) + strlen(DEID_FILE_SUFFIX));
  strcpy(outputFileName, inputFileName);
  char* extensionIndex = strstr(outputFileName, EDF_EXTENSION);
  if (extensionIndex == NULL) {
    printf("Can't find .edf extension, unable to create output file\n");
    exit(1);
  }
  strcpy(extensionIndex, DEID_EDF_EXTENSION);  // copies new extension to filename

  printf("Set output filename to %s\n", outputFileName);
  return outputFileName;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Invalid number of arguments, need to provide the input file!\n");
    exit(1);
  }

  // setup file names
  char* inputFileName = argv[1];
  char* outputFileName = setOutputFilename(inputFileName);
  miniHexDump(argv[1], HEADER_LENGTH);

  return 0;
}
