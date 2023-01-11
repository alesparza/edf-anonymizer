#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edf-anonymize.h"


void printBinaryRow(int i, FILE* file) {
  printf("%05d\t", i*10);
  char data[18] = {0};
  fgets(data, 17, file);
  printf("| %s |\n", data);
}

void miniHexDump(char* filename) {
  if (filename == NULL) {
    printf("miniHexDump: invalid filename %s\n", filename);
    exit(1);
  }

  printf("Reviewing file %s\n", filename);

  FILE* file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Error opening file, is the filename correct? (tried %s)\n", filename);
    exit(1);
  }

  printf("Printing header for %s\n", filename);
  for (int i = 0; i < HEADER_LENGTH; i++) {
    printBinaryRow(i, file);
  }
  printf("Done!\n");

  return;
}

char* setOutputFilename(char* inputFileName) {
  char* outputFileName = malloc(sizeof(char) * strlen(inputFileName) + strlen(DEID_FILE_SUFFIX));
  strcpy(outputFileName, inputFileName);
  char* extensionIndex = strstr(outputFileName, EDF_EXTENSION);
  if (extensionIndex == NULL) {
    printf("Can't find .edf extension, unable to create output file\n");
    exit(1);
  }
  strcpy(extensionIndex, DEID_EDF_EXTENSION);

  printf("Set output filename to %s\n", outputFileName);
  return outputFileName;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Invalid number of arguments, need to provide the input file!\n");
    exit(1);
  }

  char* inputFileName = argv[1];
  char* outputFileName = setOutputFilename(inputFileName);
  miniHexDump(argv[1]);

  return 0;
}
