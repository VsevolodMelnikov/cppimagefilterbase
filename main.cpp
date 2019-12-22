#include "manager.h"

int main( int argc, char *argv[] )
{
  char* arg1 = "C:\\Users\\edwar\\source\\repos\\VsevolodMelnikov\\cppimagefilterbase\\files\\config.txt";
  char* arg2 = "C:\\Users\\edwar\\source\\repos\\VsevolodMelnikov\\cppimagefilterbase\\files\\in.jpg";
  char* arg3 = "C:\\Users\\edwar\\source\\repos\\VsevolodMelnikov\\cppimagefilterbase\\files\\out.jpg";
  Manager man(arg1, arg2, arg3);
  man.run();

  return 0;
}
