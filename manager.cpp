#include "manager.h"
#include "png_filters.h"
#include <fstream>
#include <vector>

using namespace std;

Manager::Manager(char* arg1, char* arg2, char* arg3)
  :filename_in(arg2), filename_out(arg3)
{
  ifstream f(arg1);
  int u, l, d, r;
  string filtname;

  /*try {
    while (f >> filtname) {
      f >> u;
      f >> l;
      f >> d;
      f >> r;

      if (filtname == (string)"Red") {
        filters.push_back(new RedFilter(u, l, d, r));
      }
      else if (filtname == (string)"Threshold") {
        filters.push_back(new ThresholdFilter(u, l, d, r));
      }
      else if (filtname == (string)"Blur") {
        filters.push_back(new BlurFilter(u, l, d, r));
      }
      else if (filtname == (string)"Edge") {
        filters.push_back(new EdgeFilter(u, l, d, r));
      }
    }
  }
  catch (...) {}*/
  while (f.eof()) {
    try {
      f >> filtname;
      f >> u;
      f >> l;
      f >> d;
      f >> r;

      if (filtname == (string)"Red") {
        filters.push_back(new RedFilter(u, l, d, r));
      }
      else if (filtname == (string)"Threshold") {
        filters.push_back(new ThresholdFilter(u, l, d, r));
      }
      else if (filtname == (string)"Blur") {
        filters.push_back(new BlurFilter(u, l, d, r));
      }
      else if (filtname == (string)"Edge") {
        filters.push_back(new EdgeFilter(u, l, d, r));
      }
    }
    catch (...) {
      break;
    }
  }
  f.close();
}
void Manager::run() {
  png_toolkit studTool;

  studTool.load(filename_in);
  for (Filter* filt : filters) {
    image_data data = studTool.getPixelData();
    filt->apply(data);
  }
  studTool.save(filename_out);
}
Manager::~Manager() {
  for (Filter * filt : filters) {
    filt->~Filter();
  }
}