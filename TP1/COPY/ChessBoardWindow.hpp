// ChessBoardWindow.hpp

#ifndef CHESSBOARD_WINDOW_HPP
#define CHESSBOARD_WINDOW_HPP

#include "ez-draw++.hpp"
#include "ChessBoard.hpp"

class ChessBoardWindow : public EZWindow
{
 ChessBoard board;
 public:
  ChessBoardWindow();
  ~ChessBoardWindow();
 void expose();
 void buttonPress(int mouse_x,int mouse_y,int button);
 void buttonRelease(int mouse_x,int mouse_y,int button);
 void motionNotify(int mouse_x,int mouse_y,int button);
 void keyPress(EZKeySym keysym);
};

#endif
