#include <stdio.h>
#include <stdlib.h>
#include "Filters.h"

/* NOTE ABOUT POINTERS!
  When you pass an array to a function, it gets converted into a pointer. That happens with all arrays in C.
  "image" Is an array of rgb colors/pixel of the input bmp image!
  When using an array like "image" in a function e.g. smoothing(height, width, image);, "image" is only ALLOCATED ONCE.
*/

void clearscreen(void) {
  #ifdef _WIN32
      system("cls");
  #elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
      system("clear");
  #else
      printf("[-] OS not supported!");
      exit(4);
  #endif
}

int main(void) {
  clearscreen();
  printf("__//The BMP Image Filter Processor\\\\__\n");

//ASK USER FOR INPUT-, OUTPUTFILE & OPEN THEM
  char inputfile[50] = "\0";
  char outputfile[50] = "\0";
  FILE *inFile = NULL;
  FILE *outFile = NULL;

  do {
    printf("\nPath to input file [24 bit BMP]:\n");
    printf("[?] > ");
    scanf("%49s[^\n]", inputfile);
    fflush(stdin);

    inFile = fopen(inputfile, "rb");
    if (inFile == NULL) {
      printf("\n[!] Could not open input file!\n");
    }
  } while(inFile == NULL);

  do {
    printf("\nPath to output file:\n");
    printf("[?] > ");
    scanf("%49s[^\n]", outputfile);
    fflush(stdin);

    outFile = fopen(outputfile, "wb");
    if (outFile == NULL) {
      printf("\n[!] Could not create output file!\n");
    }
  } while(outFile == NULL);
//ASK USER FOR INPUT-, OUTPUTFILE & OPEN THEM

//READ INPUTFILE BMP FILE HEADER & WRITE TO STRUCT BMPFILE
  printf("\n[+] Reading BMP File Header...\n");
  BITMAPFILEHEADER bmpfile;
  fread(&bmpfile, sizeof(BITMAPFILEHEADER), 1, inFile);
//READ INPUTFILE BMP FILE HEADER & WRITE TO STRUCT BMPFILE

//READ INPUTFILE BMP INFO HEADER & WRITE TO STRUCT BMPINFO
  printf("[+] Reading BMP Info Header...\n");
  BITMAPINFOHEADER bmpinfo;
  fread(&bmpinfo, sizeof(BITMAPINFOHEADER), 1, inFile);
//READ INPUTFILE BMP INFO HEADER & WRITE TO STRUCT BMPINFO

//EXTRACT IMAGE- HEIGHT, WIDTH FROM STRUCT BMPINFO
  int height = abs(bmpinfo.biHeight);
  int width = abs(bmpinfo.biWidth);
//EXTRACT IMAGE- HEIGHT, WIDTH FROM STRUCT BMPINFO

//ALLOCATE MEMORY FOR IMAGE
  printf("[+] Allocating Pixel Array...\n");
  RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
  if (image == NULL) {
    printf("[-] Failed to allocate memory!\n");
    fclose(inFile);
    fclose(outFile);
    exit(1);
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

//ASK USER FOR INPUT
  char filter = '\0';
  int isValid = 0;
  int offset = 0;

  printf("\nPlease select one of the following filters:\n");
  printf("g - Grayscale \t Converts the image to black and white\n");
  printf("s - Smoothing \t Removes noise, sharpness and clutter\n");
  printf("i - Invert    \t Inverts the colors\n");
  printf("b - Brightness\t Change the brightness\n");
  printf("c - Contrast  \t Change the contrast\n");
  printf("t - T-roll    \t Rolls the image in 45 DEG increments\n");
  printf("[?] > ");
  scanf("%c", &filter);
  fflush(stdin);
//ASK USER FOR INPUT

//APPLY FILTER
do {
  switch (filter) {
    case 'g':
      printf("\n[+] Processing Pixel Array (Grayscale)...\n");
      grayscale(height, width, image);
      isValid = 1;
      break;

    case 's':
      printf("\n[+] Processing Pixel Array (Smoothing)...\n");
      smoothing(height, width, image);
      isValid = 1;
      break;

    case 'i':
      printf("\n[+] Processing Pixel Array (Invert)...\n");
      invert(height, width, image);
      isValid = 1;
      break;

    case 'b':
      printf("\nBrightness offset:\n");
      printf("[?] > ");
      scanf("%d", &offset);
      fflush(stdin);
      printf("\n[+] Processing Pixel Array (Brightness)...\n");
      brightness(height, width, offset, image);
      isValid = 1;
      break;

    case 'c':
      printf("\nContrast offset:\n");
      printf("[?] > ");
      scanf("%d", &offset);
      fflush(stdin);
      printf("\n[+] Processing Pixel Array (Contrast)...\n");
      contrast(height, width, offset, image);
      isValid = 1;
      break;

    case 't':
      printf("\n[+] Processing Pixel Array (T-roll)...\n");
      troll(height, width, image);
      isValid = 1;
      break;

    default:
      printf("[!] Unknown Filter!\n");
      printf("[?] > ");
      scanf("%c", &filter);
      fflush(stdin);
  }
} while(isValid == 0);
//APPLY FILTER

//WRITE BITMAPFILEHEADER TO OUTPUT FILE
  printf("[+] Writing BMP File Header...\n");
  fwrite(&bmpfile, sizeof(BITMAPFILEHEADER), 1, outFile);
//WRITE BITMAPFILEHEADER TO OUTPUT FILE

//WRITE BITMAPINFOHEADER TO OUTPUT FILE
  printf("[+] Writing BMP Info Header...\n");
  fwrite(&bmpinfo, sizeof(BITMAPINFOHEADER), 1, outFile);
//WRITE BITMAPINFOHEADER TO OUTPUT FILE

//WRITE PIXEL ARRAY TO OUTPUTFILE
  printf("[+] Writing Pixel Array...\n");
  for (int i = 0; i < height; i++) { //WRITE ROW
    fwrite(image[i], sizeof(RGBTRIPLE), width, outFile);

    for (int j = 0; j < padding; j++) { //WRITE PADDING (END OF ROW)
      fputc(0x00, outFile);
    }
  }
//WRITE PIXEL ARRAY TO OUTPUTFILE

  printf("\n[+] The image can be found in:\n");
  printf(" > %s\n", outputfile);

  free(image);
  fclose(inFile);
  fclose(outFile);
  return 0;
}
