#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char const *argv[]) {
  printf("__//The BMP Image Filter Processor\\\\__\n");

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

//READ INPUTFILE BMP FILE HEADER & WRITE TO STRUCT BMPFILE
  BITMAPFILEHEADER bmpfile;
  fread(&bmpfile, sizeof(BITMAPFILEHEADER), 1, inFile);
//READ INPUTFILE BMP FILE HEADER & WRITE TO STRUCT BMPFILE

//READ INPUTFILE BMP INFO HEADER & WRITE TO STRUCT BMPINFO
  BITMAPINFOHEADER bmpinfo;
  fread(&bmpinfo, sizeof(BITMAPINFOHEADER), 1, inFile);
//READ INPUTFILE BMP INFO HEADER & WRITE TO STRUCT BMPINFO

//EXTRACT IMAGE- HEIGHT, WIDTH FROM STRUCT BMPINFO
  int height = abs(bmpinfo.biHeight);
  int width = abs(bmpinfo.biWidth);
//EXTRACT IMAGE- HEIGHT, WIDTH FROM STRUCT BMPINFO

//ALLOCATE MEMORY FOR IMAGE
  RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
  if (image == NULL) {
    printf("[-] Failed to allocate memory!\n");
    fclose(inFile);
    fclose(outFile);
    exit(3);
  }
//ALLOCATE MEMORY FOR IMAGE

//SET PADDING
  int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
//SET PADDING

//WRITE PIXEL ARRAY PER ROW (SCANLINE)
  for (int i = 0; i < height; i++) {
    fread(image[i], sizeof(RGBTRIPLE), width, inFile);

    //SKIP PADDING
    fseek(inFile, padding, SEEK_CUR);
  }
//WRITE PIXEL ARRAY PER ROW (SCANLINE)

  free(image);
  fclose(inFile);
  fclose(outFile);
  return 0;
}
