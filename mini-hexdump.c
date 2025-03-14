#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mini-hexdump.h"

void printBinaryRow(int i, FILE* file) {
  printf("%05d\t", i*10);
  char data[18] = {0};
  fgets(data, 17, file);
  printf("| %s |\n", data);
}

void miniHexDump(char* filename, int maxLines) {
  if (filename == NULL) {
    printf("miniHexDump: invalid filename %s\n", filename);
    return;
  }

  FILE* file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Error opening file, is the filename correct? (tried %s)\n", filename);
    return;
  }

  printf("Printing header for %s\n", filename);
  for (int i = 0; i < maxLines; i++) {
    printBinaryRow(i, file);
  }
  printf("Done!\n");
  fclose(file);

  return;
}