#ifndef PNG_FILTERS_H_INCLUDED__
#define PNG_FILTERS_H_INCLUDED__

#include "png_toolkit.h"

struct ImageBorders {
public:
  ImageBorders(int u, int l, int d, int r);
  ImageBorders(const ImageBorders& bords);

  int u;
  int l;
  int d;
  int r;
};

class Filter {
public:
  Filter(const ImageBorders& bords);
  Filter(int u, int l, int d, int r);
  virtual void apply(image_data& image) = 0;
  virtual ~Filter();

protected:
  ImageBorders bords;
};

class RedFilter : public Filter {
public:
  RedFilter(const ImageBorders& bords);
  RedFilter(int u, int l, int d, int r);
  void apply(image_data& image);
};

class BlackWhiteFilter : public Filter {
public:
  BlackWhiteFilter(const ImageBorders& bords);
  BlackWhiteFilter(int u, int l, int d, int r);
  void apply(image_data& image);
};

class ThresholdFilter : public Filter {
public:
  ThresholdFilter(const ImageBorders& bords);
  ThresholdFilter(int u, int l, int d, int r);
  void apply(image_data& image);
};

class BlurFilter : public Filter {
public:
  BlurFilter(const ImageBorders& bords);
  BlurFilter(int u, int l, int d, int r);
  void apply(image_data& image);
};

class EdgeFilter : public Filter {
public:
  EdgeFilter(const ImageBorders& bords);
  EdgeFilter(int u, int l, int d, int r);
  void apply(image_data& image);
};

#endif