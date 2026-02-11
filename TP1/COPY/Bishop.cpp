// Bishop.cpp

#include <iostream>
#include <array>

using namespace std;

#include "ez-draw++.hpp"
#include "AbstractZone.hpp"
#include "Bishop.hpp"

Bishop::Bishop(bool _isWhite,ChessBoard *chessboard)
 : BlackAndWhitePiece(_isWhite,"images/White-Bishop.png","images/Black-Bishop.png",chessboard)
{ DBG("Bishop::Bishop(uint _x,uint _y,bool)"); }

Bishop::Bishop(istream& is,ChessBoard *chessboard)
 : BlackAndWhitePiece(is,"images/White-Bishop.png","images/Black-Bishop.png",chessboard)
{ DBG("Bishop::Bishop(istream&)"); }

Bishop::~Bishop()
{ DBG("Bishop::~Bishop()"); }

unordered_set<AbstractZone*> Bishop::canMoveTo() const
{
  unordered_set<AbstractZone*> zones;
  AbstractZone *my_zone = getZone();
  array<const size_t,4> directions = {0,2,5,7};
  for(auto& d : directions)
  {
    for(AbstractZone *step = my_zone->getNeighbour(d); step!=nullptr ; step = (step?step->getNeighbour(d):nullptr))
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

void Bishop::write(ostream& os) const
{
 os << "Bishop ";
 BlackAndWhitePiece::write(os);
}
