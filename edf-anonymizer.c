#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edf-anonymizer.h"
#include "mini-hexdump.h"

void printHelp() {
  printf("Usage:\tedf-anonymizer -h\n");
  printf("\tedf-anonymizer [-d|-s] [-i filename]\n");
  printf("\n");
  printf("\t-h:  Print this help message\n");
  printf("\t-d:  Enable Detail Mode.  Prompt for the four local patient identification fields\n");
  printf("\t-s:  Enable Simple Mode.  Single prompt for the local patient identification (default)\n");
  printf("\t-i filename:  input file name.  The expected format is .edf\n");
}

char* getInputName() {
  char* input = calloc(BUFFER_SIZE , sizeof(char));
  printf("Please enter the input file name: ");
  fgets(input, BUFFER_SIZE, stdin);
  input[strlen(input) - 1] = '\0';
  return input;
}

char* setOutputFilename(char* inputFileName) {
  char* outputFileName = malloc(sizeof(char) * (strlen(inputFileName) + strlen(DEID_FILE_SUFFIX) + 1));
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
  // handle arguments
  if (argc < MINIMUM_ARGUMENTS) {
    printHelp();
    exit(1);
  }

  char* inputFileName = NULL;
  int isSimple = 0;
  int isDetail = 0;

  for (int i = 0; i < argc; i++) {
    if (strcmp("-i", argv[i]) == 0) {
      i++;
      if (argv[i] == NULL) {
        printHelp();
        exit(1);
      }
      inputFileName = argv[i];
      continue;
    }

    if (strcmp("-h", argv[i]) == 0) {
      printHelp();
      exit(1);
    }

    if (strcmp("-d", argv[i]) == 0) {
      isDetail = 1;
      continue;
    }

    if (strcmp("-s", argv[i]) == 0) {
      isSimple = 1;
      continue;
    }
  }

  if (isSimple && isDetail) {
    printf("Cannot request Simple and Detail mode\n");
    printHelp();
    exit(1);
  }

  if (inputFileName == NULL) {
    inputFileName = getInputName();
  }

  // setup file names
  char* outputFileName = setOutputFilename(inputFileName);
  miniHexDump(inputFileName, HEADER_LENGTH);

  // Start anonymizing the data
  char* newData = calloc(LOCAL_PATIENT_IDENFITICATION_LENGTH + 1, sizeof(char));

  // Detail Mode; ask for each field
  if (isDetail) {
    char* patientID = calloc(BUFFER_SIZE, sizeof(char));
    char* patientSex = calloc(BUFFER_SIZE, sizeof(char));
    char* patientDOB = calloc(BUFFER_SIZE, sizeof(char));
    char* patientName = calloc(BUFFER_SIZE, sizeof(char));
    char* tempBuffer = calloc(BUFFER_SIZE * 4, sizeof(char));
    //TODO: actually implement this
    printf("Please enter a response for the following four questions.  Press enter if unknown or not used\n");
    printf("Please enter the patient ID: ");
    fgets(patientID, BUFFER_SIZE, stdin);

    // check if user pressed enter, if so, write "X ", otherwise just remove the last \n
    if (*patientID == '\n') {
      *patientID = 'X';
      *(patientID + 1) = ' ';
    } else {
      *(patientID + strlen(patientID) - 1) = ' ';
    }

    printf("Please enter the patient sex: ");
    fgets(patientSex, BUFFER_SIZE, stdin);
    if (*patientSex == '\n') {
      *patientSex = 'X';
      *(patientSex + 1) = ' ';
    } else {
      *(patientSex + strlen(patientSex) - 1) = ' ';
    }

    printf("Please enter patient date of birth in dd-MMM-yyyy format (e.g. 02-MAR-2001): ");
    fgets(patientDOB, BUFFER_SIZE, stdin);
    if (*patientDOB == '\n') {
      *patientDOB = 'X';
      *(patientDOB + 1) = ' ';
    } else {
      *(patientDOB + strlen(patientDOB) - 1) = ' ';
    }

    printf("Please enter patient name: ");
    fgets(patientName, BUFFER_SIZE, stdin);
    if (*patientName == '\n') {
      *patientName = 'X';
      *(patientName + 1) = '\0';
    } else {
      *(patientName + strlen(patientName) - 1) = '\0';
    }

    strcat(tempBuffer, patientID);
    strcat(tempBuffer, patientSex);
    strcat(tempBuffer, patientDOB);
    strcat(tempBuffer, patientName);
    strncat(newData, tempBuffer, LOCAL_PATIENT_IDENFITICATION_LENGTH + 1);
    //TODO: fill remaining characters (80 - strlen(newData)) with 0x20

  } else {
    // Simple Mode; single prompt for the entire field
    printf("Please enter replacement data for Local Patient Identification (80 character max): ");
    fgets(newData, LOCAL_PATIENT_IDENFITICATION_LENGTH, stdin);
    *(newData + strlen(newData) - 1) = '\0'; // removing the \n
    for (int i = 0; i < LOCAL_PATIENT_IDENFITICATION_LENGTH; i++) {
      if (*(newData + i) == '\0') {
        *(newData + i) = ' ';
      }
    }
  }
  printf("Anonymizing file (this can take a bit for large files)\n");
  fflush(stdout);

  FILE* input = fopen(inputFileName, "rb");
  FILE* output = fopen(outputFileName, "wb");

  // copy the version
  int version[VERSION_LENGTH];
  fread(version, VERSION_LENGTH, sizeof(char), input);
  fwrite(version, VERSION_LENGTH, sizeof(char), output);

  // write the local data
  int buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(buffer));
  fread(buffer, LOCAL_PATIENT_IDENFITICATION_LENGTH, sizeof(char), input);
  fwrite(newData, LOCAL_PATIENT_IDENFITICATION_LENGTH, sizeof(char), output);
  free(newData);

  // write the rest of the original file
  memset(buffer, '\0', sizeof(buffer));
  while ((fread(buffer, sizeof(buffer), sizeof(char), input)) != 0) {
    fwrite(buffer, sizeof(buffer), sizeof(char), output);
    memset(buffer, '\0', sizeof(buffer));
  }


  fclose(input);
  fclose(output);
  printf("Done writing the output file %s\n", outputFileName);
  miniHexDump(outputFileName, HEADER_LENGTH);

  free(outputFileName);

  return 0;
}
