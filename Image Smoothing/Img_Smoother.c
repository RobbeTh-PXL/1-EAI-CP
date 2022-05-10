#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char const *argv[]) {
  printf("__//The Image Processor\\\\__\n");

//ASK USER FOR INPUT-, OUTPUTFILE, FILTER
  char *inputfile = NULL;
  char *outputfile = NULL;

  printf("Path to input file [24 bit BMP]:\n");
  scanf("%s", inputfile);
  fflush(stdin);

  printf("Path to output file:\n");
  scanf("%s", outputfile);
  fflush(stdin);
//ASK USER FOR INPUT-, OUTPUTFILE, FILTER

  return 0;
}
