#include "Filters.h"

/* NOTES:
*  Pixel colors of bmp are formatted in BGR
*/

//SMOOTHING
//SMOOTHING

//EDGE
//EDGE

//GRAYSCALE
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) { //ROWS
    for (int j = 0; j < width; j++) { //COLUMNS
      //CALCULATE THE AVG COLOR VAL
      int avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
      //WRITE AVG
      image[i][j].rgbtBlue = avg;
      image[i][j].rgbtGreen = avg;
      image[i][j].rgbtRed = avg;
    }
  }
}
//GRAYSCALE

//REFLECT
//REFLECT

//INVERT
//INVERT

//TROLL
void troll(int height, int width, RGBTRIPLE image[height][width]) {
  #ifdef _WIN32
      system("start https://shattereddisk.github.io/rickroll/rickroll.mp4");
  #else
      system("open https://shattereddisk.github.io/rickroll/rickroll.mp4");
  #endif
}
//TROLL
