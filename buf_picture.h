#ifndef BUF_PICTURE_H_INCLUDED__
#define BUF_PICTURE_H_INCLUDED__

#include "png_filters.h"
#include "png_toolkit.h"
#include "ker.h"

class BufPicture {
public:
  BufPicture(ImageBorders& bords, image_data& image);
  bool isInPicture(int y, int x) const;
  int getR(int y, int x) const;
  int getG(int y, int x) const;
  int getB(int y, int x) const;
  int getIntensity(int y, int x) const;
  int getMedianIntensity(int y, int x, int radius) const;
  int getContractionR(int y, int x, Kernel& ker) const;
  int getContractionG(int y, int x, Kernel& ker) const;
  int getContractionB(int y, int x, Kernel& ker) const;
  BufPicture& operator=(BufPicture& bf);

private:
  ImageBorders& bords;
  image_data& image;
};

#endif