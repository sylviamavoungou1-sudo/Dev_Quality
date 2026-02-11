#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

#include "ChessBoardWindow.hpp"


ChessBoardWindow::ChessBoardWindow()
: EZWindow(1200,1000,"EZ Chess++"),board("images/chessboard2.png",8,8,193,93,102,102)
{
 TODO("il faut pointer les dépendances de chaque fichier pour le Makefile")
 setDoubleBuffer(true);
 DBG("BoardWindow::BoardWindow()");
}

ChessBoardWindow::~ChessBoardWindow()
{ DBG("BoardWindow::~BoardWindow()"); }

void ChessBoardWindow::expose()
{
 clear(ez_grey);
 board.draw(*this);
}

// Bouton de la souris enfonce :
void ChessBoardWindow::buttonPress(int mouse_x,int mouse_y,int button)
{
 board.buttonPress(mouse_x,mouse_y);
 sendExpose();
}

 // Bouton relâché :
void ChessBoardWindow::buttonRelease(int mouse_x,int mouse_y,int button)
{
//    cout << "ButtonRelease    win = " << this << " mouse_x = " << mouse_x << " mouse_y = " << mouse_y << " button = " << button << endl ;
 board.buttonRelease(mouse_x,mouse_y);
 sendExpose();
}

 // Déplacement de la souris :
void ChessBoardWindow::motionNotify(int mouse_x,int mouse_y,int button)
{
//    cout << "MotionNotify     win = " << this << " mouse_x = " << mouse_x << " mouse_y = " << mouse_y << " button = " << button << endl ;
 board.motionNotify(mouse_x,mouse_y);
 sendExpose();
}

void ChessBoardWindow::keyPress(EZKeySym keysym)
{
  switch (keysym)
   {
      case EZKeySym::_1:
          break;
      case EZKeySym::_2:
          break;
      case EZKeySym::_3:
          break;
      case EZKeySym::Escape:
      case EZKeySym::q :
          EZDraw::quit();
          break;
      case EZKeySym::S:
          {
            ofstream ofs("/tmp/board.dat");
            board.save(ofs);
          }
          break;
      default: // Dans tous les autres cas on ne fait rien (nécessaire
        break; // pour éviter un warning a la compilation).
   }
}
