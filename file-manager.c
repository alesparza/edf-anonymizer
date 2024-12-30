#include "file-manager.h"


FileManager* initialiseFileManager() {
    FileManager* fileManager = malloc(sizeof(FileManager));
    fileManager->filename = NULL;
    fileManager->file = NULL;
    fileManager->staticHeader = NULL;
    fileManager->dynamicHeader = NULL;

    return fileManager;
}


void freeFileManager(FileManager* fileManager) {
    free(fileManager->filename);
    if (fileManager->file != NULL) {
        fclose(fileManager->file);
    }
    free(fileManager);
}

void loadFile(FileManager* fileManager) {
    assert(fileManager != NULL); // this should never happen
    printFilenameInput();
    printPrompt();
    fileManager->filename = getInput();

    if (fileManager->filename != NULL) {
        fileManager->file = fopen(fileManager->filename, "rb");
    }

    // if the file cannot be opened, clean up the file manager, just to be safe
    if (fileManager->file == NULL) {
        printFileUnopenable(fileManager->filename);
        free(fileManager->filename);
        fileManager->filename = NULL;
        freeStaticHeader(fileManager->staticHeader);
        fileManager->staticHeader = NULL;
        freeDynamicHeader(fileManager->dynamicHeader);
        fileManager->dynamicHeader = NULL;
        return;
    }

    // read the data now
    fileManager->staticHeader = initialiseStaticHeader();
    readStaticHeader(fileManager->staticHeader, fileManager->file);
    // fileManager->dynamicHeader = initialiseDynamicHeader(); // this isn't actually necessary for anonymization
    rewind(fileManager->file); // have to reset this now to avoid issues copying later
    printSuccessfulLoad(fileManager->filename);
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
