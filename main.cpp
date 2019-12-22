#include "manager.h"

int main( int argc, char *argv[] )
{
  //char* arg1 = "C:\\Users\\edwar\\source\\repos\\VsevolodMelnikov\\cppimagefilterbase\\files\\config.txt";
  //char* arg2 = "C:\\Users\\edwar\\source\\repos\\VsevolodMelnikov\\cppimagefilterbase\\files\\in.jpg";
  //char* arg3 = "C:\\Users\\edwar\\source\\repos\\VsevolodMelnikov\\cppimagefilterbase\\files\\out.jpg";
  Manager man(argv[1], argv[2], argv[3]);
  man.run();

  return 0;
}
