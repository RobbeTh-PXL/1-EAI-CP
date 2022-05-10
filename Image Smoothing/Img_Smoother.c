#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char const *argv[]) {
  printf("__//The Image Processor\\\\__\n");

//ASK USER FOR INPUT-, OUTPUTFILE, FILTER
  char inputfile[50];
  char outputfile[50];

  printf("Path to input file [24 bit BMP]:\n");
  scanf("%s", inputfile);
  fflush(stdin);

  printf("Path to output file:\n");
  scanf("%s", outputfile);
  fflush(stdin);
//ASK USER FOR INPUT-, OUTPUTFILE, FILTER

//OPEN INPUT-, OUTPUTFILE
  FILE *inFile = fopen(inputfile, "r");
  if (inFile == NULL) {
    printf("[-] Could not open input file!\n");
    exit(1);
  }

  FILE *outFile = fopen(outputfile, "w");
  if (outFile == NULL) {
    printf("[-] Could not create output file!\n");
    exit(2);
  }
//OPEN INPUT-, OUTPUTFILE

//READ INPUTFILE BMP FILE HEADER
  BITMAPFILEHEADER bmpfile;
  fread(&bmpfile, sizeof(BITMAPFILEHEADER), 1, inFile);
//READ INPUTFILE BMP FILE HEADER

//READ INPUTFILE BMP INFO HEADER
  BITMAPINFOHEADER bmpinfo;
  fread(&bmpinfo, sizeof(BITMAPINFOHEADER), 1, inFile);
//READ INPUTFILE BMP INFO HEADER
  return 0;
}
