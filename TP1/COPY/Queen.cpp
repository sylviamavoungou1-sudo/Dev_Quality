// Queen.cpp

#include <iostream>
#include <array>

using namespace std;

#include "ez-draw++.hpp"
#include "AbstractZone.hpp"
#include "Queen.hpp"

Queen::Queen(bool _isWhite,ChessBoard *chessboard)
 : BlackAndWhitePiece(_isWhite,"images/White-Queen.png","images/Black-Queen.png",chessboard)
{ DBG("Queen::Queen(bool)"); }

Queen::Queen(istream& is,ChessBoard *chessboard)
 : BlackAndWhitePiece(is,"images/White-Queen.png","images/Black-Queen.png",chessboard)
{ DBG("Queen::Queen(istream&)"); }

Queen::~Queen()
{ DBG("Queen::~Queen()"); }

unordered_set<AbstractZone*> Queen::canMoveTo() const
{
  unordered_set<AbstractZone*> zones;
  AbstractZone *myZone = getZone();
  std::array<size_t,8> directions = {0,1,2,3,4,5,6,7};
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

void Queen::write(ostream& os) const
{
 os << "Queen ";
 BlackAndWhitePiece::write(os);
}
