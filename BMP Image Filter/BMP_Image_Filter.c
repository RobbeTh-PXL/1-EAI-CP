#include <stdio.h>
#include <stdlib.h>
#include "Filters.h"

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

int main(int argc, char const *argv[]) {
  clearscreen();
  printf("__//The BMP Image Filter Processor\\\\__\n");

//ASK USER FOR INPUT-, OUTPUTFILE, FILTER
  char inputfile[50];
  char outputfile[50];

  printf("\nPath to input file [24 bit BMP]:\n");
  printf("[?] > ");
  scanf("%s", inputfile);
  fflush(stdin);

  printf("\nPath to output file:\n");
  printf("[?] > ");
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

//ASK USER FOR FILTER
  char filter = '\0';
  int isValid = 0;

  printf("\nPlease select one of the following filters:\n");
  printf("g - Grayscale\n");
  printf("[?] > ");
  scanf("%c", &filter);
  fflush(stdin);
//ASK USER FOR FILTER

//APPLY FILTER
do {
  switch (filter) {
    case 'g':
      printf("\n[+] Processing Pixel Array (Grayscale)...\n");
      grayscale(height, width, image);
      isValid = 1;
      break;

    default:
      printf("[-] Unknown Filter!\n");
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
  printf("%s\n", outputfile);

  free(image);
  fclose(inFile);
  fclose(outFile);
  return 0;
}
