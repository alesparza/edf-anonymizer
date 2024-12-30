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

void loadFile(FileManager* fileManager) {
    assert(fileManager != NULL);
    printFilenameInput();
    printPrompt();
    fileManager->filename = getInput();
    if (fileManager->filename != NULL) {
        fileManager->file = fopen(fileManager->filename, "rb");
    }
    if (fileManager->file == NULL) {
        printFileUnopenable(fileManager->filename);
        free(fileManager->filename);
        fileManager->filename = NULL;
    }
}
