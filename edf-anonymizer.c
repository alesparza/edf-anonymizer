#include "edf-anonymizer.h"

void writeFile(FileManager* fileManager) {
  printf("Writing file (this can take a bit for large files)\n");
  fflush(stdout);

  FILE* input = fileManager->file;
  if (input == NULL) {
    printf("ERROR: (unexpected) file is NULL");
    return;
  }
  rewind(input); // necessary in case it was moved from the start
  char* outputFilename = getOutputFilename(fileManager->filename);
  if (outputFilename == NULL) {
    printf("ERROR: (unexpected) returned NULL for getOutputFilename\n");
    return;
  }
  FILE* output = fopen(outputFilename, "wb");
  if (output == NULL) {
    printf("ERROR: unable to open output file\n");
    free(outputFilename);
    return;
  }

  // copy the version; this is the only part before the patient info section
  int version[HEADER_VERSION_LENGTH];
  fread(version, HEADER_VERSION_LENGTH, sizeof(char), input);
  fwrite(version, HEADER_VERSION_LENGTH, sizeof(char), output);

  // write the local patient info data
  int buffer[BUFFER_SIZE];
  fseek(input, HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH, SEEK_CUR); // skip reading this from the file since it is modified
  fwrite(fileManager->staticHeader->localPatientIdentification, HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH, sizeof(char), output);

  //TODO: write the header sections individually, then move the input file 256 bytes and copy the rest of the data

  // write the rest of the original file
  memset(buffer, '\0', sizeof(buffer));
  while ((fread(buffer, sizeof(buffer), sizeof(char), input)) != 0) {
    fwrite(buffer, sizeof(buffer), sizeof(char), output);
    memset(buffer, '\0', sizeof(buffer));
  }
  printf("Done writing the output file %s\n", outputFilename);
  free(outputFilename);
}

char* getOutputFilename(char* inputFileName) {
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

int main() {
    FileManager* fileManager = initialiseFileManager();
    printWelcome();

    // main loop: print options, process input, call handler
    while(1) {
        printMain(fileManager->filename);
        printPrompt();
        char* response = getInput();

        // process the response to be sure it is a number
        int selection = validateNumericInput(response);
        if (selection == 0) {
            printNotNumber(response);
            continue;
        }

        // handle the input
        switch (selection) {
            case EXIT_VAL:
                printf("Bye bye!\n");
                freeFileManager(fileManager);
                exit(0);
            case LOAD_VAL:
                loadFile(fileManager);
                break;
            case VIEW_VAL:
                if (fileManager->filename == NULL) {
                    printNoOpenFile();
                    break;
                }
                miniHexDump(fileManager->filename, HEADER_ROWS);
                break;
            case MODIFY_VAL:
                if (fileManager->filename == NULL) {
                    printNoOpenFile();
                    break;
                }
                printf("modify header unimplemented\n");
                break;
            case SAVE_VAL:
                if (fileManager->filename == NULL) {
                    printNoOpenFile();
                    break;
                }
                writeFile(fileManager);
                break;
            default:
                printUnknownOption(selection);
                break;
        }
    }
}
