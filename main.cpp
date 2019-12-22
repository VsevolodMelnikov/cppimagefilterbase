#include "manager.h"

int main( int argc, char *argv[] )
{
  if (argc == 4) {
    Manager man(argv[1], argv[2], argv[3]);
    man.run();
  }

  return 0;
}