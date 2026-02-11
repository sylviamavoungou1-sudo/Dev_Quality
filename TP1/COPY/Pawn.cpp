// Pawn.cpp

#include <iostream>

using namespace std;

#include "ez-draw++.hpp"
#include "AbstractZone.hpp"
#include "Pawn.hpp"

Pawn::Pawn(bool _isWhite,ChessBoard *chessboard)
 : BlackAndWhitePiece(_isWhite,"images/White-Pawn.png","images/Black-Pawn.png",chessboard),hasMoved(false)
{ DBG("Pawn::Pawn(bool)"); }

Pawn::Pawn(istream& is,ChessBoard *chessboard)
 : BlackAndWhitePiece(is,"images/White-Pawn.png","Black-Pawn.png",chessboard),hasMoved(false)
{ DBG("Pawn::Pawn(istream&)"); }

Pawn::~Pawn()
{ DBG("Pawn::~Pawn()"); }

void Pawn::moveToZone(AbstractZone *destination)
{
  BlackAndWhitePiece::moveToZone(destination);
  hasMoved = true;
}

unordered_set<AbstractZone*> Pawn::canMoveTo() const
{
  TODO("Ce serait amusant de rajouter l'implantation de la règle de la prise en passant.")
  unordered_set<AbstractZone*> zones;
  AbstractZone *myZone = getZone();
  AbstractZone *up1 = myZone->getNeighbour(isWhite()?1:6);
  if(up1!=nullptr && up1->getPiece()==nullptr)
    zones.insert(up1);
  AbstractZone *up2 = (!hasMoved && up1!=nullptr?up1->getNeighbour(isWhite()?1:6):nullptr);
  if(up2!=nullptr && up2->getPiece()==nullptr)
    zones.insert(up2);
  AbstractZone *tl = myZone->getNeighbour(isWhite()?0:5);
  if(tl!=nullptr && tl->getPiece()!=nullptr)
  {
    BlackAndWhitePiece* p2 = dynamic_cast<BlackAndWhitePiece*>(tl->getPiece());
    if(p2!=nullptr && p2->isWhite()!=isWhite())
      zones.insert(tl);
  }
  AbstractZone *tr = myZone->getNeighbour(isWhite()?2:7);
  if(tr!=nullptr && tr->getPiece()!=nullptr)
  {
    BlackAndWhitePiece* p2 = dynamic_cast<BlackAndWhitePiece*>(tr->getPiece());
    if(p2!=nullptr && p2->isWhite()!=isWhite())
      zones.insert(tr);
  }

  return zones;
}

void Pawn::write(ostream& os) const
{
 os << "Pawn ";
 BlackAndWhitePiece::write(os);
}
