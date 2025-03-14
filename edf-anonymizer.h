#ifndef EDF_ANONYMIZER_H
#define EDF_ANONYMIZER_H

#include "commandline.h"
#include "mini-hexdump.h"
#include "edf-header.h"
#include "edf-anonymizer.h"
#include "file-manager.h"
#include "commandline.h"
#include "messages.h"

#define BUFFER_SIZE 1024
#define DEID_FILE_SUFFIX "_deid"
#define EDF_EXTENSION ".edf"
#define DEID_EDF_EXTENSION "_deid.edf"

/**
 * Write an EDF File using the contents of the file manager.
 */
void writeFile(FileManager* fileManager);

/**
 * Gets the output filename for a specified input filename.
 * Adds _deid at the end of the filename, but before the extension.
 */
char* getOutputFilename(char* inputFileName);

#endif /* EDF_ANONYMIZER_H */