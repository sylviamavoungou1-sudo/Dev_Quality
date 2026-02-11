// Rook.cpp

#include <iostream>
#include <array>

using namespace std;

#include "ez-draw++.hpp"
#include "AbstractZone.hpp"
#include "Rook.hpp"

Rook::Rook(bool _isWhite,ChessBoard *chessboard)
 : BlackAndWhitePiece(_isWhite,"images/White-Rook.png","images/Black-Rook.png",chessboard)
{ DBG("Rook::Rook(bool)"); }

Rook::Rook(istream& is,ChessBoard *chessboard)
 : BlackAndWhitePiece(is,"images/White-Rook.png","images/Black-Rook.png",chessboard)
{ DBG("Rook::Rook(istream&)"); }

Rook::~Rook()
{ DBG("Rook::~Rook()"); }

unordered_set<AbstractZone*> Rook::canMoveTo() const
{
  unordered_set<AbstractZone*> zones;
  AbstractZone *myZone = getZone();
  array<const size_t,4> directions = {1,3,4,6};
  for(auto& d : directions)
  {
    for(AbstractZone *step = myZone->getNeighbour(d); step!=nullptr ; step = (step?step->getNeighbour(d):nullptr))
    {
      AbstractPiece *stepPiece = (step?step->getPiece():nullptr);
      BlackAndWhitePiece *stepBWPiece = dynamic_cast<BlackAndWhitePiece*>(stepPiece);
      if(step)
      {
        if(!stepBWPiece)
          zones.insert(step);
        else if(stepBWPiece->isWhite()!=isWhite())
          { zones.insert(step); step = nullptr; }
        else
          step = nullptr;
      }
    }
  }

  return zones;
}

void Rook::write(ostream& os) const
{
 os << "Rook ";
 BlackAndWhitePiece::write(os);
}
