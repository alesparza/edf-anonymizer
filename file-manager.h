#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "edf-header.h"
#include "messages.h"
#include "commandline.h"


/**
 * File Management struct
 */
typedef struct {
    char* filename;
    FILE* file;

} FileManager;

/**
 * Initialises the file manager struct.
 */
FileManager* initialiseFileManager();

/**
 * Frees the file manager struct.
 */
void freeFileManager(FileManager* fileManager);

/**
 * Loads a file into memory.
 */
void loadFile(FileManager* fileManager);

#endif /* FILEMANAGER_H */