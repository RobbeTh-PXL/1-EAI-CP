#ifndef FILTERS_H
#define FILTERS_H
#include "bmp.h"
/*SMOOTHING
* DISC:   Pixel smoothing 3x3 box filter
* PARAM:  image height, -width, -pixel array (rgb values)
* RETURN: -
*/
void smoothing(int height, int width, RGBTRIPLE image[height][width]);

//EDGE
//EDGE

/* GRAYSCALE
* DISC:   Converts image to grayscale
* PARAM:  image height, -width, -pixel array (rgb values)
* RETURN: -
*/
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

/* INVERT
* DISC:   Inverts the image RGB colors
* PARAM:  image height, -width, -pixel array (rgb values)
* RETURN: -
*/
void invert(int height, int width, RGBTRIPLE image[height][width]);

//REFLECT
//REFLECT

//INVERT
//INVERT

/* TROLL
* DISC:   Rolls the image in 45° increments
* PARAM:  image height, -width, -pixel array (rgb values)
* RETURN: -
*/
void troll(int height, int width, RGBTRIPLE image[height][width]);
#endif /* FILTERS_H */
