#include "buf_picture.h"
#include "png_filters.h"
#include <vector>
#include <algorithm>

BufPicture::BufPicture(ImageBorders& bords, image_data& image)
  : bords(bords), image(image)
{}

bool BufPicture::isInPicture(int y, int x) const {
  if (y < bords.u || y >= bords.d) {
    return false;
  }
  if (x < bords.l || x >= bords.r) {
    return false;
  }
  return true;
}
int BufPicture::getR(int y, int x) const {
  if (isInPicture(y, x))
    return image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x];
  else
    return 0;
}
int BufPicture::getG(int y, int x) const {
  if (isInPicture(y, x))
    return image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 1];
  else
    return 0;
}
int BufPicture::getB(int y, int x) const {
  if (isInPicture(y, x))
    return image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 2];
  else
    return 0;
}
int BufPicture::getIntensity(int y, int x) const {
  return (int)((3 * getR(y, x) + 6 * getG(y, x) + getB(y, x)) / 10);
}
int BufPicture::getMedianIntensity(int y, int x, int radius) const {
  std::vector<int> medians;

  for (int x_iter = x - radius; x_iter < x + 1 + radius; ++x_iter) {
    for (int y_iter = y - radius; y_iter < y + 1 + radius; ++y_iter) {
      if (isInPicture(y_iter, x_iter)) {
        medians.push_back(getIntensity(y_iter, x_iter));
      }
    }
  }

  std::sort(medians.begin(), medians.end());

  return medians[medians.size() / 2];
}
int BufPicture::getContractionR(int y, int x, Kernel& ker) const {
  if (ker.getSize() % 2) {
    int radius = ker.getSize() / 2;
    int sum = 0;

    for (int x_iter = x - radius; x_iter < x + 1 + radius; ++x_iter) {
      for (int y_iter = y - radius; y_iter < y + 1 + radius; ++y_iter) {
        if (isInPicture(y_iter, x_iter)) {
          sum += getR(y_iter, x_iter) * ker.get(y_iter - y + radius, x_iter - x + radius);
        }
      }
    }

    sum /= ker.sum();

    if (sum < 0x00) {
      sum = 0x00;
    }
    else if (sum > 0xFF) {
      sum = 0xFF;
    }

    return sum;
  }
  else {
    return 0;
  }
}
int BufPicture::getContractionG(int y, int x, Kernel& ker) const {
  if (ker.getSize() % 2) {
    int radius = ker.getSize() / 2;
    int sum = 0;

    for (int x_iter = x - radius; x_iter < x + 1 + radius; ++x_iter) {
      for (int y_iter = y - radius; y_iter < y + 1 + radius; ++y_iter) {
        if (isInPicture(y_iter, x_iter)) {
          sum += getG(y_iter, x_iter) * ker.get(y_iter - y + radius, x_iter - x + radius);
        }
      }
    }
    
    sum /= ker.sum();

    if (sum < 0x00) {
      sum = 0x00;
    }
    else if (sum > 0xFF) {
      sum = 0xFF;
    }

    return sum;
  }
  else {
    return 0;
  }
}
int BufPicture::getContractionB(int y, int x, Kernel& ker) const {
  if (ker.getSize() % 2) {
    int radius = ker.getSize() / 2;
    int sum = 0;

    for (int x_iter = x - radius; x_iter < x + 1 + radius; ++x_iter) {
      for (int y_iter = y - radius; y_iter < y + 1 + radius; ++y_iter) {
        if (isInPicture(y_iter, x_iter)) {
          sum += getB(y_iter, x_iter) * ker.get(y_iter - y + radius, x_iter - x + radius);
        }
      }
    }    
    sum /= ker.sum();

    if (sum < 0x00) {
      sum = 0x00;
    }
    else if (sum > 0xFF) {
      sum = 0xFF;
    }

    return sum;
  }
  else {
    return 0;
  }
}
BufPicture& BufPicture::operator=(BufPicture& bf) {
  bords = bf.bords;
  image = bf.image;
  return *this;
}