#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edf-anonymizer.h"
#include "edf-header.h"
#include "mini-hexdump.h"

void printAndExit(int exitCode) {
  printf("Press ENTER to quit...\n");
  fgetc(stdin);
  exit(exitCode);
}

void printHelp() {
  printf("Usage:\tedf-anonymizer -h|-H\n");
  printf("\tedf-anonymizer [-d|-s] [-r] [-i filename]\n");
  printf("\n");
  printf("\t-h:  Print this help message\n");
  printf("\t-H:  Print a more verbose help message\n");
  printf("\t-d:  Enable Detail Mode.  Prompt for the four local patient identification fields\n");
  printf("\t-s:  Enable Simple Mode.  Single prompt for the local patient identification (default)\n");
  printf("\t-r:  Review Mode.  Do not anonymize data, just print the header\n");
  printf("\t-i <filename>:  input file name.  The expected format is .edf\n");
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

void readStaticHeader(StaticHeader* header, FILE* input) {
  fread(header->version, HEADER_VERSION_LENGTH, sizeof(char), input);
  fread(header->localPatientIdentification, HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH, sizeof(char), input);
  fread(header->localRecordingIdentification, HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH, sizeof(char), input);
  fread(header->startDate, HEADER_STARTDATE_RECORDING_LENGTH, sizeof(char), input);
  fread(header->startTime, HEADER_STARTTIME_RECORDING_LENGTH, sizeof(char), input);
  fread(header->totalBytes, HEADER_TOTAL_BYTES_LENGTH, sizeof(char), input);
  fread(header->reserved, HEADER_RESERVED, sizeof(char), input);
  fread(header->numDataRecords, HEADER_NUMBER_DATA_RECORDS_LENGTH, sizeof(char), input);
  fread(header->dataDuration, HEADER_DATA_DURATION_LENGTH, sizeof(char), input);
  fread(header->numSignals, HEADER_NUMBER_SIGNALS_LENGTH, sizeof(char), input);
}

char* setOutputFilename(char* inputFileName) {
  // copy the current filename to the new buffer, then add the appropriate extension
  char* outputFileName = malloc(sizeof(char) * (strlen(inputFileName) + strlen(DEID_FILE_SUFFIX) + 1));
  strncpy(outputFileName, inputFileName, strlen(inputFileName) + 1);
  char* extensionIndex = strstr(outputFileName, EDF_EXTENSION);
  if (extensionIndex == NULL) {
    printf("Can't find .edf extension, unable to create output file\n");
    return NULL;
  }
  strncpy(extensionIndex, DEID_EDF_EXTENSION, strlen(DEID_EDF_EXTENSION) + 1);  // copies new extension to filename
  printf("Set output filename to %s\n", outputFileName);
  return outputFileName;
}

char* appendPromptResponse(char* currentResponse) {
  char* response = calloc(BUFFER_SIZE, sizeof(char));
  fgets(response, BUFFER_SIZE - 1, stdin);

  // set the response to "X " if no entry, otherwise just drop the \n
  if (*response == '\n') {
    *response = 'X';
    *(response + 1) = ' '; //TODO: remove this
  } else {
    *(response + strlen(response) - 1) = ' ';
  }

  //TODO: convert spaces to underscores

  // append to the current response contents
  strncat(currentResponse, response, strlen(response) + 1);
  //TODO: write a space after the response
  free(response);

  return currentResponse;
}

void checkLength(char* data) {
  int len = strlen(data);
  if (len > HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH) {
    printf("Warning: the length of your responses is longer than the allowed length\n");
    printf("Only the first %d characters will be written to the file\n", HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH);
  }
}

int main(int argc, char **argv) {
  if (argc < MINIMUM_ARGUMENTS) {
    printHelp();
    printAndExit(1);
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
        printAndExit(1);
      }
      char* tempName = calloc(BUFFER_SIZE, sizeof(char));
      strncpy(tempName, argv[i], BUFFER_SIZE);
      inputFileName = tempName;
      continue;
    }

    if (strcmp("-h", argv[i]) == 0) {
      printHelp();
      printAndExit(1);
    }

    if (strcmp("-H", argv[i]) == 0) {
      printVerboseHelp();
      printAndExit(1);
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
    printAndExit(1);
  }

  // ensure we have some kind of filename
  if (inputFileName == NULL) {
    inputFileName = getInputName();
  }

  // print the current headers, exit immediately if in Review Mode
  miniHexDump(inputFileName, HEADER_ROWS);
  if (isReview) {
    printAndExit(0);
  }

  // Put the data into the header
  StaticHeader* staticHeader = initialiseStaticHeader();
  // TODO: read the header and update the internal fields.

  // Start anonymizing the data
  char* outputFileName = setOutputFilename(inputFileName);
  if (outputFileName == NULL) {
    printAndExit(1);
  }
  char* newData = calloc(BUFFER_SIZE, sizeof(char));

  // Detail Mode; ask for each field individually
  if (isDetail) {
    char* tempBuffer = calloc(BUFFER_SIZE * 4, sizeof(char));
    printf("Please enter a response for the following four questions.  Press enter if unknown or not used\n");

    // for each prompt, check if user pressed enter, if so, write "X ", otherwise just remove the last \n
    printf("Please enter the patient ID: ");
    appendPromptResponse(tempBuffer);

    printf("Please enter the patient sex: ");
    appendPromptResponse(tempBuffer);

    printf("Please enter patient date of birth in dd-MMM-yyyy format (e.g. 02-MAR-2001): ");
    appendPromptResponse(tempBuffer);

    printf("Please enter patient name: ");
    appendPromptResponse(tempBuffer);

    checkLength(tempBuffer);
    for (int i = strlen(tempBuffer); i < HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH; i++) {
      *(tempBuffer + i) = ' ';
    }
    strncat(newData, tempBuffer, HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH);
    free(tempBuffer);


  } else {
    // Simple Mode; single prompt for the entire field
    printf("Please enter replacement data for Local Patient Identification (80 character max): ");
    fgets(newData, BUFFER_SIZE - 1, stdin);
    checkLength(newData);

    // remove the \n if it exists
    int index = strlen(newData) - 1;
    if (*(newData + index) == '\n') {
      *(newData + index) = ' ';
    }

    // replace NULLs from calloc with spaces, per specification
    for (int i = 0; i < HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH + 1; i++) {
      if (*(newData + i) == '\0') {
        *(newData + i) = ' ';
      }
    }
  }

  printf("Anonymizing file (this can take a bit for large files)\n");
  fflush(stdout);

  FILE* input = fopen(inputFileName, "rb");
  FILE* output = fopen(outputFileName, "wb");

  readStaticHeader(staticHeader, input);
  rewind(input); // Necessary during testing since the pointer moves

  // copy the version; this is the only part before the patient info section
  int version[HEADER_VERSION_LENGTH];
  fread(version, HEADER_VERSION_LENGTH, sizeof(char), input);
  fwrite(version, HEADER_VERSION_LENGTH, sizeof(char), output);

  // write the local patient info data
  int buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(buffer));
  fread(buffer, HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH, sizeof(char), input);
  fwrite(newData, HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH, sizeof(char), output);
  free(newData);

  // write the rest of the original file
  memset(buffer, '\0', sizeof(buffer));
  while ((fread(buffer, sizeof(buffer), sizeof(char), input)) != 0) {
    fwrite(buffer, sizeof(buffer), sizeof(char), output);
    memset(buffer, '\0', sizeof(buffer));
  }
  printf("Done writing the output file %s\n", outputFileName);

  // cleanup
  miniHexDump(outputFileName, HEADER_ROWS);
  fclose(input);
  fclose(output);
  free(outputFileName);
  free(inputFileName);
  staticHeader = freeStaticHeader(staticHeader);
  
  printf("Press ENTER to close\n");
  fgetc(stdin);
  return 0;
}
