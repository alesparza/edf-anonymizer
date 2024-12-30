#include "file-manager.h"


FileManager* initialiseFileManager() {
    FileManager* fileManager = malloc(sizeof(FileManager));
    fileManager->filename = NULL;
    fileManager->file = NULL;

    return fileManager;
}


void freeFileManager(FileManager* fileManager) {
    free(fileManager->filename);
    if (fileManager->file != NULL) fclose(fileManager->file);
    free(fileManager);
}
