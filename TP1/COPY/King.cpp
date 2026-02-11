// King.cpp

#include <iostream>

using namespace std;

#include "ez-draw++.hpp"
#include "AbstractZone.hpp"
#include "King.hpp"

King::King(bool _isWhite,ChessBoard *chessboard)
 : BlackAndWhitePiece(_isWhite,"images/White-King.png","images/Black-King.png",chessboard),hasMoved(false)
{ DBG("King::King(uint _x,uint _y,bool)"); }

King::King(istream& is,ChessBoard *chessboard)
 : BlackAndWhitePiece(is,"images/White-King.png","images/Black-King.png",chessboard),hasMoved(false)
{ DBG("King::King(istream&)"); }

King::~King()
{ DBG("King::~King()"); }

unordered_set<AbstractZone*> King::canMoveTo() const
{
TODO("Il faut vérifier que le roi ne se met pas lui-même en échec lors de son déplacement.")
TODO("Il faut ajouter la règle du roque grâce à la balise hasMoved.")
  unordered_set<AbstractZone*> zones;
  AbstractZone *myZone = getZone();
  for(size_t i=0;i<8;++i)
  {
    AbstractZone *step = myZone->getNeighbour(i);
    AbstractPiece *stepPiece = (step?step->getPiece():nullptr);
    BlackAndWhitePiece *stepBWPiece = dynamic_cast<BlackAndWhitePiece*>(stepPiece);
    if(step && (!stepBWPiece || stepBWPiece->isWhite()!=isWhite()))
      zones.insert(step);
  }

  return zones;
}

void King::moveToZone(AbstractZone *destination)
{
  BlackAndWhitePiece::moveToZone(destination);
  hasMoved = true;
}

void King::write(ostream& os) const
{
 os << "King ";
 BlackAndWhitePiece::write(os);
}
