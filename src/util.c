
#include <stdio.h>
#include <stdlib.h>

#include "include/util.h"

char *mcm_util_readFile(const char *filepath) {
  FILE *file = fopen(filepath, "r");

  if (!file) {
    printf("Error: Failed to read file at \"%s\"!", filepath);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *content = malloc(len + 1);
  fread(content, len, 1, file);
  content[len] = '\0';

  fclose(file);
  return content;
}
