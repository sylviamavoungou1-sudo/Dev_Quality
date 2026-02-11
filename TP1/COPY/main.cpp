#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

#include "ChessBoardWindow.hpp"

int main(int argc,char *argv[])
{
  DBG("Début du main");

  EZDraw ezDraw;

  ChessBoardWindow win;
  ezDraw.mainLoop();
  DBG("Fin du main");
  return 0;
}
