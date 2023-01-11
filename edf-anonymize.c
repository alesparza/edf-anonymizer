#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printBinaryRow(int i, FILE* file) {
  printf("%05d\t", i*10);
  char data[18] = {0};
  fgets(data, 17, file);
  printf("| %s |\n", data);
}

void miniHexDump(char* filename) {
  if (filename == NULL) {
    printf("miniHexDump: invalid filename %s\n", filename);
    exit(1);
  }

  printf("Reviewing file %s\n", filename);

  FILE* file = fopen(filename, "rb");

  if (file == NULL) {
    printf("Error opening file, is the filename correct? (tried %s)\n", filename);
    exit(1);
  }

  printf("Printing header for %s\n", filename);

  for (int i = 0; i < 15; i++) {
    printBinaryRow(i, file);
  }

  printf("Done!\n");
  return;
}



int main(int argc, char **argv) {

miniHexDump(argv[1]);


  return 0;
}
