// Knight.cpp

#include <iostream>

using namespace std;

#include "ez-draw++.hpp"
#include "ChessBoard.hpp"
#include "Knight.hpp"

Knight::Knight(bool _isWhite,ChessBoard *chessboard)
 : BlackAndWhitePiece(_isWhite,"images/White-Knight.png","images/Black-Knight.png",chessboard)
{ DBG("Knight::Knight(bool)"); }

Knight::Knight(istream& is,ChessBoard *chessboard)
 : BlackAndWhitePiece(is,"images/White-Knight.png","images/Black-Knight.png",chessboard)
{ DBG("Knight::Knight(istream&)"); }

Knight::~Knight()
{ DBG("Knight::~Knight()"); }

unordered_set<AbstractZone*> Knight::canMoveTo() const
{
  #
  unordered_set<AbstractZone*> zones;
  AbstractZone *myZone = getZone();
  ChessBoard *cb = getChessBoard();
  size_t c,r;
  cb->getColumnRow(myZone,c,r);
  const struct { int dc,dr; } movements[] = {
    { 2, 1},
    { 2,-1},
    {-2, 1},
    {-2,-1},
    {-1, 2},
    {-1,-2},
    { 1, 2},
    { 1,-2},
    {0,0}
  };
  for(size_t i=0;!(movements[i].dc==0 && movements[i].dr==0);++i)
  {
    AbstractZone *L_zone = cb->getZone(c+movements[i].dc,r+movements[i].dr);
    if(L_zone==nullptr)
      continue;
    AbstractPiece *lPiece = L_zone->getPiece();
    if(lPiece==nullptr)
      { zones.insert(L_zone); continue; }
    BlackAndWhitePiece *bwlPiece = dynamic_cast<BlackAndWhitePiece*>(lPiece);
    if(bwlPiece==nullptr)
      continue;
    if(bwlPiece->isWhite()!=isWhite())
      { zones.insert(L_zone); continue; }
    else
      continue;
  }
  return zones;
}

void Knight::write(ostream& os) const
{
 os << "Knight ";
 BlackAndWhitePiece::write(os);
}
