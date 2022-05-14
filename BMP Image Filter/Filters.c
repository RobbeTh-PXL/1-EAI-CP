#include "Filters.h"
#include <stdlib.h>
#include <math.h>

/* NOTES:
*  Pixel colors of bmp are formatted in BGR
*/

//SMOOTHING
void smoothing(int height, int width, RGBTRIPLE image[height][width]) {
  //DUPLICATE IMAGE
  RGBTRIPLE temp[height][width];
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      temp[i][j] = image[i][j];
    }
  }
  //DUPLICATE IMAGE

  //BOX FILTER
  for (int i = 0; i < height; i++) { //ROWS
    for (int j = 0; j < width; j++) { //COLUMNS
      float blue_sum = 0.0;
      float green_sum = 0.0;
      float red_sum = 0.0;
      int counter = 0;

      for (int k = -1; k < 2; k++) { //SURROUNDING PIXELS ON ROW
        for (int l = -1; l < 2; l++) { //SURROUNDING PIXELS ON COLUMN
          if (i+k < 0 || i+k >= height) { //CHECK IF PIXEL IS OUT OF BOUNDS (ROW)
            continue;
          }
          if (j+1 < 0 || j+l >= width) { //CHECK IF PIXEL IS OUT OF BOUNDS (COLUMN)
            continue;
          }

          //ADD VALUE TO SUM WHEN NOT OUT OF BOUNDS
          blue_sum += temp[i+k][j+l].rgbtBlue;
          green_sum += temp[i+k][j+l].rgbtGreen;
          red_sum += temp[i+k][j+l].rgbtRed;
          counter++;
        }
      }

      //CALCULATE & WRITE AVG
      image[i][j].rgbtBlue = round(blue_sum / (float) counter);
      image[i][j].rgbtGreen = round(green_sum / (float) counter);
      image[i][j].rgbtRed = round(red_sum / (float) counter);
    }
  }
  //BOX FILTER
}
//SMOOTHING

//EDGE
//EDGE

//GRAYSCALE
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) { //ROWS
    for (int j = 0; j < width; j++) { //COLUMNS
      //CALCULATE THE AVG COLOR VAL
      int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
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
