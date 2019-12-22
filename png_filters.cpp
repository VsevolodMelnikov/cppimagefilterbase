#include "png_filters.h"
#include "png_toolkit.h"
#include "buf_picture.h"
#include "ker.h"

#include <iostream>
using namespace std;

ImageBorders::ImageBorders(int u, int l, int d, int r)
  :u(u), l(l), d(d), r(r)
{}
ImageBorders::ImageBorders(const ImageBorders& bords)
  : u(bords.u), l(bords.l), d(bords.d), r(bords.r)
{}

Filter::Filter(const ImageBorders& bords)
  : bords(bords)
{}
Filter::Filter(int u, int l, int d, int r)
  : bords(u, l, d, r)
{}
Filter::~Filter() 
{};

BlackWhiteFilter::BlackWhiteFilter(const ImageBorders& bords)
  : Filter(bords)
{}
BlackWhiteFilter::BlackWhiteFilter(int u, int l, int d, int r)
  : Filter(u, l, d, r)
{}
void BlackWhiteFilter::apply(image_data& image) {
  int x_start = (bords.l) ? (image.w / bords.l) : 0;
  int x_end = (bords.r) ? (image.w / bords.r) : 0;
  int y_start = (bords.u) ? (image.h / bords.u) : 0;
  int y_end = (bords.d) ? (image.h / bords.d) : 0;

  ImageBorders bords = ImageBorders(y_start, x_start, y_end, x_end);

  int buf;

  BufPicture bp = BufPicture(bords, image);

  for (int y = y_start; y < y_end; ++y) {
    for (int x = x_start; x < x_end; ++x) {
      buf = bp.getIntensity(y, x);
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x] = buf;
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 1] = buf;
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 2] = buf;
    }
  }
}

RedFilter::RedFilter(const ImageBorders& bords)
  : Filter(bords)
{}
RedFilter::RedFilter(int u, int l, int d, int r)
  : Filter(u, l, d, r)
{}
void RedFilter::apply(image_data& image) {
  int x_start = (bords.l) ? (image.w / bords.l) : 0;
  int x_end = (bords.r) ? (image.w / bords.r) : 0;
  int y_start = (bords.u) ? (image.h / bords.u) : 0;
  int y_end = (bords.d) ? (image.h / bords.d) : 0;

  for (int y = y_start; y < y_end; ++y) {
    for (int x = x_start; x < x_end; ++x) {
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x] = 0xFF;
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 1] = 0x00;
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 2] = 0x00;
    }
  }
}

ThresholdFilter::ThresholdFilter(const ImageBorders& bords)
  : Filter(bords)
{}
ThresholdFilter::ThresholdFilter(int u, int l, int d, int r)
  : Filter(u, l, d, r)
{}
void ThresholdFilter::apply(image_data& image) {
  int x_start = (bords.l) ? (image.w / bords.l) : 0;
  int x_end = (bords.r) ? (image.w / bords.r) : 0;
  int y_start = (bords.u) ? (image.h / bords.u) : 0;
  int y_end = (bords.d) ? (image.h / bords.d) : 0;
  ImageBorders filter_bords = ImageBorders(y_start, x_start, y_end, x_end);
  BufPicture bp = BufPicture(filter_bords, image);

  BlackWhiteFilter bw = BlackWhiteFilter(bords);
  bw.apply(image);
  

  stbi_uc* buf_pixels = new stbi_uc[image.compPerPixel * (y_end - y_start) * (x_end - x_start)];
  for (int y = y_start; y < y_end; ++y) {
    for (int x = x_start; x < x_end; ++x) {
      if (bp.getIntensity(y, x) < bp.getMedianIntensity(y, x, 2)) {
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start)] = 0x00;
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 1] = 0x00;
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 2] = 0x00;
      }
      else {
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start)] = bp.getR(y, x);
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 1] = bp.getG(y, x);
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 2] = bp.getB(y, x);
      }
    }
  }

  for (int y = y_start; y < y_end; ++y) {
    for (int x = x_start; x < x_end; ++x) {
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x] =
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start)];
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 1] =
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 1];
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 2] =
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 2];
    }
  }

  delete[] buf_pixels;
}

BlurFilter::BlurFilter(const ImageBorders& bords)
  : Filter(bords)
{}
BlurFilter::BlurFilter(int u, int l, int d, int r)
  : Filter(u, l, d, r)
{}
void BlurFilter::apply(image_data& image) {
  int x_start = (bords.l) ? (image.w / bords.l) : 0;
  int x_end = (bords.r) ? (image.w / bords.r) : 0;
  int y_start = (bords.u) ? (image.h / bords.u) : 0;
  int y_end = (bords.d) ? (image.h / bords.d) : 0;
  ImageBorders filter_bords = ImageBorders(y_start, x_start, y_end, x_end);
  BufPicture bp = BufPicture(filter_bords, image);

  BlurKernel ker = BlurKernel();

  stbi_uc* buf_pixels = new stbi_uc[image.compPerPixel * (y_end - y_start) * (x_end - x_start)];
  for (int y = y_start; y < y_end; ++y) {
    int y_pos = image.compPerPixel * (y - y_start) * (x_end - x_start);
    for (int x = x_start; x < x_end; ++x) {
      int x_pos = image.compPerPixel * (x - x_start);

      buf_pixels[y_pos + x_pos] = bp.getContractionR(y, x, ker);
      buf_pixels[y_pos + x_pos + 1] = bp.getContractionG(y, x, ker);
      buf_pixels[y_pos + x_pos + 2] = bp.getContractionB(y, x, ker);
    }
  }

  for (int y = y_start; y < y_end; ++y) {
    int y_pos = image.compPerPixel * (y - y_start) * (x_end - x_start);
    for (int x = x_start; x < x_end; ++x) {
      int x_pos = image.compPerPixel * (x - x_start);

      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x] =
        buf_pixels[y_pos + x_pos];
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 1] =
        buf_pixels[y_pos + x_pos + 1];
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 2] =
        buf_pixels[y_pos + x_pos + 2];
    }
  }

  delete[] buf_pixels;
}

EdgeFilter::EdgeFilter(const ImageBorders& bords)
  : Filter(bords)
{}
EdgeFilter::EdgeFilter(int u, int l, int d, int r)
  : Filter(u, l, d, r)
{}
void EdgeFilter::apply(image_data& image) {
  int x_start = (bords.l) ? (image.w / bords.l) : 0;
  int x_end = (bords.r) ? (image.w / bords.r) : 0;
  int y_start = (bords.u) ? (image.h / bords.u) : 0;
  int y_end = (bords.d) ? (image.h / bords.d) : 0;
  ImageBorders filter_bords = ImageBorders(y_start, x_start, y_end, x_end);
  BufPicture bp = BufPicture(filter_bords, image);

  BlackWhiteFilter bw = BlackWhiteFilter(bords);
  bw.apply(image);

  EdgeKernel ker = EdgeKernel();

  stbi_uc* buf_pixels = new stbi_uc[image.compPerPixel * (y_end - y_start) * (x_end - x_start)];
  for (int y = y_start; y < y_end; ++y) {
    for (int x = x_start; x < x_end; ++x) {
      buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start)] = bp.getContractionR(y, x, ker);
      buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 1] = bp.getContractionG(y, x, ker);
      buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 2] = bp.getContractionB(y, x, ker);
    }
  }

  for (int y = y_start; y < y_end; ++y) {
    for (int x = x_start; x < x_end; ++x) {
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x] =
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start)];
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 1] =
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 1];
      image.pixels[image.compPerPixel * image.w * y + image.compPerPixel * x + 2] =
        buf_pixels[image.compPerPixel * (y - y_start) * (x_end - x_start) + image.compPerPixel * (x - x_start) + 2];
    }
  }

  delete[] buf_pixels;
}