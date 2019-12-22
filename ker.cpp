#include "ker.h"

Kernel::Kernel(int size)
  :size(size)
{
  if (size > 0) {
    weight = new int* [size];
    for (int i = 0; i < size; ++i) {
      weight[i] = new int[size];
    }
  }
  else {
    weight = nullptr;
    this->size = 0;
  }
}
int Kernel::getSize() {
  return size;
}
bool Kernel::isInKernel(int x, int y) {
  if (y < 0 || y >= size) {
    return false;
  }
  if (x < 0 || x >= size) {
    return false;
  }
  return true;
}
Kernel::~Kernel() {
  if (size > 0) {
    for (int i = 0; i < size; ++i)
      delete[] weight[i];
    delete[] weight;
  }
}

EdgeKernel::EdgeKernel()
  :Kernel(3)
{
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      weight[i][j] = -1;
    }
  }
  weight[1][1] = 9;
}
int EdgeKernel::sum() {
  return 1;
}
int EdgeKernel::get(int x, int y) {
  if (isInKernel(x, y)) {
    return weight[x][y];
  }
  else {
    return 0;
  }
}

BlurKernel::BlurKernel()
  :Kernel(3)
{
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      weight[i][j] = 1;
    }
  }
}
int BlurKernel::sum() {
  return 9;
}
int BlurKernel::get(int x, int y) {
  if (isInKernel(x, y)) {
    return weight[x][y];
  }
  else {
    return 0;
  }
}