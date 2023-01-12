#ifndef MINIHEXDUMP_H
#define MINIHEXDUMP_H

/**
* Prints a single row of binary data from a files
*/
void printBinaryRow(int i, FILE* file);


/**
* Prints a mini hex deump of a file.
*/
void miniHexDump(char* filename, int maxLines);

#endif  /* MINIHEXDUMP_H */