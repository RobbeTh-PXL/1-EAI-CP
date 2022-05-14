# BMP Image Filter
---

## Features
### Filters
- [x] Smoothing / Blur
- [ ] Edges
- [x] Grayscale
- [ ] Reflect
- [x] Invert
- [x] Troll

### File Handling
- [x] Specify input file at start
- [x] Specify output filename and location
- [ ] Input file validation

### User Interface
- [x] Help menu
- [x] Error messages
- [x] Easy to use

## How to compile
1. Create an object file from Filters.c
```bash
gcc -Wall -pedantic -c Filters.c -o Filters.o
```
2. Compile BMP_Image_Filter.c
```bash
gcc -Wall -pedantic BMP_Image_Filter.c Filters.o -o BMP_Image_Filter.exe
```

## Filter Flow
### Grayscale
1. Get RGB value of a pixel
2. Calculate average of the RGB colors
3. Set pixel RGB value to average

### Smoothing / Blur
1. Duplicate image into a RGBTRIPLE array (preserves original pixels for calculations)
2. Select a pixel as centre
3. Check for surrounding pixels (horizontal & vertical)
4. Add up RGB values of surrounding pixels
5. Calculate average RGB value of surrounding pixels (sum of RGB values divided by amount of surrounding pixels)
6. Set pixel RGB value to average

### Invert
1. Get RGB value of a pixel
2. Subtract RGB value from 255 (255 - RGB)
3. Set pixel RGB value to subtraction result

## Notes
The code written in **BMP_Image_Filter.c** is partly based on the **Harvard University CS50 Filter Exercise** *(See References)*.

## References
- [Microsoft Docs: About Bitmaps](https://docs.microsoft.com/en-us/windows/win32/gdi/about-bitmaps)
- [Harvard University CS50 Course](https://pll.harvard.edu/course/cs50-introduction-computer-science?delta=0)
- [Harvard University CS50 Filter Exercise](https://cs50.harvard.edu/x/2021/psets/4/filter/less/)
- [Image processing in C by Dwayne Phillips](https://homepages.inf.ed.ac.uk/rbf/BOOKS/PHILLIPS/)
- [bmp.h Library](https://gist.github.com/BrainUser/80a4e12f8ae535499243)
- [Calculating Scanline Padding for Bitmaps](https://forum.powerbasic.com/forum/user-to-user-discussions/programming/43679-calculating-scanline-padding-for-bitmaps)
- [Linux man pages online](https://man7.org/linux/man-pages/index.html)
- [Tutorialspoint C Standard Library Reference](https://www.tutorialspoint.com/c_standard_library/index.htm)
