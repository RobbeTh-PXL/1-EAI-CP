# BMP Image Filter
---

## Features
### Filters
- [ ] Smoothing
- [ ] Blur
- [ ] Edges
- [ ] Grayscale
- [ ] Reflect
- [ ] Invert

### File Handling
- [x] Specify input file at start
- [x] Specify output filename and location
- [ ] Input file validation

### User Interface
- [x] Help menu
- [x] Error messages
- [x] Easy to use

## How to compile
```bash
gcc -Wall -pedantic BMP_Image_Filter.c -o BMP_Image_Filter.exe
```

## Notes
The code written in **BMP_Image_Filter.c** is based on the **Harvard University CS50 Filter Exercise** *(See References)*.

## References
- [Microsoft Docs: About Bitmaps](https://docs.microsoft.com/en-us/windows/win32/gdi/about-bitmaps)
- [Harvard University CS50 Course](https://pll.harvard.edu/course/cs50-introduction-computer-science?delta=0)
- [Harvard University CS50 Filter Exercise](https://cs50.harvard.edu/x/2021/psets/4/filter/less/)
- [bmp.h Library](https://gist.github.com/BrainUser/80a4e12f8ae535499243)
- [Linux man pages online](https://man7.org/linux/man-pages/index.html)
