#ifndef MANAGER_H_INCLUDED__
#define MANAGER_H_INCLUDED__

#include "png_filters.h"
#include <vector>

class Manager {
public:
  Manager(char* arg1, char* arg2, char* arg3);
  void run();
  ~Manager();

private:
  char* filename_in;
  char* filename_out;
  std::vector<Filter*> filters;
};

#endif