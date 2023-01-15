#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edf-anonymizer.h"
#include "mini-hexdump.h"

void printHelp() {
  printf("Usage:\tedf-anonymizer -h|-H\n");
  printf("\tedf-anonymizer [-d|-s] [-r] [-i filename]\n");
  printf("\n");
  printf("\t-h:  Print this help message\n");
  printf("\t-H:  Print a more verbose help message\n");
  printf("\t-d:  Enable Detail Mode.  Prompt for the four local patient identification fields\n");
  printf("\t-s:  Enable Simple Mode.  Single prompt for the local patient identification (default)\n");
  printf("\t-r:  Review Mode.  Do not anonymize data, just print the header\n");
  printf("\t-i filename:  input file name.  The expected format is .edf\n");
}

void printVerboseHelp() {
  printf("Verbose Help Message not configured.  Here's the short version.\n");
  printHelp();
}

char* getInputName() {
  char* input = calloc(BUFFER_SIZE , sizeof(char));
  printf("Please enter the input file name: ");
  fgets(input, BUFFER_SIZE, stdin);
  input[strlen(input) - 1] = '\0';
  return input;
}

char* setOutputFilename(char* inputFileName) {
  // copy the current filename to the new buffer, then add the appropriate extension
  char* outputFileName = malloc(sizeof(char) * (strlen(inputFileName) + strlen(DEID_FILE_SUFFIX) + 1));
  strncpy(outputFileName, inputFileName, strlen(inputFileName) + 1);
  char* extensionIndex = strstr(outputFileName, EDF_EXTENSION);
  if (extensionIndex == NULL) {
    printf("Can't find .edf extension, unable to create output file\n");
    exit(1);
  }
  strncpy(extensionIndex, DEID_EDF_EXTENSION, strlen(DEID_EDF_EXTENSION) + 1);  // copies new extension to filename
  printf("Set output filename to %s\n", outputFileName);
  return outputFileName;
}

char* getPromptResponse() {
  char* response = calloc(BUFFER_SIZE, sizeof(char));
  fgets(response, BUFFER_SIZE, stdin);

  // set the response to "X " if no entry, otherwise just drop the \n
  if (*response == '\n') {
    *response = 'X';
    *(response + 1) = ' ';
  } else {
    *(response + strlen(response) - 1) = ' ';
  }
  return response;
}

int main(int argc, char **argv) {
  if (argc < MINIMUM_ARGUMENTS) {
    printHelp();
    exit(1);
  }

  // flags for various arguments
  char* inputFileName = NULL;
  int isSimple = 0;
  int isDetail = 0;
  int isReview = 0;

  // check all the arguments, set flags, report errors (or print the help message)
  for (int i = 0; i < argc; i++) {
    //TODO: switch to switch block
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

    if (strcmp("-H", argv[i]) == 0) {
      printVerboseHelp();
      exit(1);
    }

    if (strcmp("-r", argv[i]) == 0) {
      isReview = 1;
      continue;
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

  // these are mutually exclusive
  if (isSimple && isDetail) {
    printf("Cannot request Simple and Detail mode\n");
    printHelp();
    exit(1);
  }

  // ensure we have some kind of filename
  if (inputFileName == NULL) {
    inputFileName = getInputName();
  }

  // print the current headers, exit immediately if in Review Mode
  miniHexDump(inputFileName, HEADER_LENGTH);
  if (isReview) {
    exit(0);
  }

  // Start anonymizing the data
  char* outputFileName = setOutputFilename(inputFileName);
  char* newData = calloc(LOCAL_PATIENT_IDENFITICATION_LENGTH + 1, sizeof(char));

  // Detail Mode; ask for each field individually
  if (isDetail) {
    char* response;
    char* tempBuffer = calloc(BUFFER_SIZE * 4, sizeof(char));
    printf("Please enter a response for the following four questions.  Press enter if unknown or not used\n");

    // for each prompt, check if user pressed enter, if so, write "X ", otherwise just remove the last \n
    printf("Please enter the patient ID: ");
    response = getPromptResponse();
    strcat(tempBuffer, response);
    free(response);

    printf("Please enter the patient sex: ");
    response = getPromptResponse();
    strcat(tempBuffer, response);
    free(response);

    printf("Please enter patient date of birth in dd-MMM-yyyy format (e.g. 02-MAR-2001): ");
    response = getPromptResponse();
    strcat(tempBuffer, response);
    free(response);

    printf("Please enter patient name: ");
    response = getPromptResponse();
    strcat(tempBuffer, response);
    free(response);

    int len = strlen(tempBuffer); // TODO: print message if length is too long
    for (int i = len; i < LOCAL_PATIENT_IDENFITICATION_LENGTH; i++) {
      *(tempBuffer + i) = ' ';
    }
    strncat(newData, tempBuffer, LOCAL_PATIENT_IDENFITICATION_LENGTH + 1);
    free(tempBuffer);


  } else {
    // Simple Mode; single prompt for the entire field
    printf("Please enter replacement data for Local Patient Identification (80 character max): ");
    fgets(newData, LOCAL_PATIENT_IDENFITICATION_LENGTH, stdin); //TODO: print error if too long
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

  // copy the version; this is the only part before the patient info section
  int version[VERSION_LENGTH];
  fread(version, VERSION_LENGTH, sizeof(char), input);
  fwrite(version, VERSION_LENGTH, sizeof(char), output);

  // write the local patient info data
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
  printf("Done writing the output file %s\n", outputFileName);

  // cleanup
  miniHexDump(outputFileName, HEADER_LENGTH);
  fclose(input);
  fclose(output);
  free(outputFileName);
  free(inputFileName);

  return 0;
}
