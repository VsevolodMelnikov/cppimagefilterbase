#ifndef KER_H_INCLUDED__
#define KER_H_INCLUDED__

class Kernel {
public:
  Kernel(int size);
  virtual int get(int x, int y) = 0;
  int getSize();
  virtual ~Kernel();
  bool isInKernel(int x, int y);
  virtual int sum() = 0;

protected:
  int **weight;
  int size;
};

class EdgeKernel : public Kernel {
public:
  EdgeKernel();
  int get(int x, int y);
  int sum();
};

class BlurKernel : public Kernel {
public:
  BlurKernel();
  int get(int x, int y);
  int sum();
};

#endif