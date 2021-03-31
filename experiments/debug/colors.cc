#include <iostream>
#include <windows.h>   // WinApi header
#include <bitset>
using namespace std;    // std::cout, std::cin

bool GetColor(short &ret){

        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
            return false;
        ret = 0;
        ret = info.wAttributes;
        return true;
}

namespace ConsoleForeground
{
  enum {
    BLACK             = 0,
    DARKBLUE          = FOREGROUND_BLUE,
    DARKGREEN         = FOREGROUND_GREEN,
    DARKCYAN          = FOREGROUND_GREEN | FOREGROUND_BLUE,
    DARKRED           = FOREGROUND_RED,
    DARKMAGENTA       = FOREGROUND_RED | FOREGROUND_BLUE,
    DARKYELLOW        = FOREGROUND_RED | FOREGROUND_GREEN,
    DARKGRAY          = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    GRAY              = FOREGROUND_INTENSITY,
    BLUE              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    GREEN             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    CYAN              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    RED               = FOREGROUND_INTENSITY | FOREGROUND_RED,
    MAGENTA           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    YELLOW            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    WHITE             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
  };
}

int main()
{
  HANDLE  hConsole;
	int k;
  
  short prev;
  GetColor(prev);
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // you can loop k higher to see more color choices
  // short tmp = 1;
  // for(k = 0; k < 16; k++)
  // {
  //   // pick the colorattribute k you want
  //   short tmp2 = tmp & prev;
  //   SetConsoleTextAttribute(hConsole, tmp2 | ConsoleForeground::DARKBLUE);

  //   cout << tmp << " I want to be nice today!" << endl;

  //   tmp = tmp << 1;
  // }
  // for (short aaa = 0; aaa != 255; ++aaa){
  // short aaaa = aaa | ConsoleForeground::DARKBLUE;
  

  // SetConsoleTextAttribute(hConsole, aaaa);
  // std::cout << std::bitset<sizeof(short) * 8>(aaaa) << std::endl;
  // cout << aaa << " asdasd!" << endl;
  //}

  short backgr = 0b1110000;
  backgr &= prev;
  SetConsoleTextAttribute(hConsole, backgr | ConsoleForeground::DARKBLUE);
  //SetConsoleTextAttribute(hConsole, 9374);
  cout << k << " asdasd!" << endl;
  SetConsoleTextAttribute(hConsole,prev);
  cout << prev << " Default!" << endl;
  return 0;
}
