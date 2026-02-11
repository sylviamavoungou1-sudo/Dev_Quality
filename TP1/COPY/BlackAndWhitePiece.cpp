// BlackAndWhitePiece.cpp

#include <iostream>
#include <stdexcept>

using namespace std;

#include "ez-draw++.hpp"
#include "BlackAndWhitePiece.hpp"
#include "AbstractZone.hpp"

BlackAndWhitePiece::BlackAndWhitePiece(bool _isWhite,const char *_whiteImageFileName,const char *_blackImageFileName,ChessBoard* _chessboard)
 : isWhite_(_isWhite),imageWhite(_whiteImageFileName),imageBlack(_blackImageFileName),chessboard(_chessboard)
{
 imageWhite.setAlpha(true);
 imageBlack.setAlpha(true);
 DBG("BlackAndWhitePiece::BlackAndWhitePiece()");
}

BlackAndWhitePiece::BlackAndWhitePiece(istream& is,const char *_whiteImageFileName,const char *_blackImageFileName,ChessBoard* _chessboard)
 : AbstractPiece(is),isWhite_(true),imageWhite(_whiteImageFileName),imageBlack(_blackImageFileName),chessboard(_chessboard)
{
 imageWhite.setAlpha(true);
 imageBlack.setAlpha(true);
 string color;
 is >> color;
 if(color == "White")
   isWhite_ = true;
 else if(color == "Black")
   isWhite_ = false;
 else
   throw runtime_error("Unexpected color found during construction of BlackAndWhitePiece(istream&). This should be either \"Black\" or \"White\".");
 DBG("BlackAndWhitePiece::BlackAndWhitePiece(istream&)");
}

BlackAndWhitePiece::~BlackAndWhitePiece()
{ DBG("BlackAndWhitePiece::~BlackAndWhitePiece()"); }


bool BlackAndWhitePiece::isOver(uint x,uint y) const
{
 AbstractZone *zone = getZone();
 if(!zone) return false;
 const Point& p = zone->getAnchor();
 const EZImage& image(isWhite_?imageWhite:imageBlack);
 return ( p.getX() <= x && x < p.getX()+image.getWidth()) &&
        ( p.getY() <= y && y < p.getY()+image.getHeight());
}

void BlackAndWhitePiece::moveToZone(AbstractZone *destination)
{
  destination->setPiece(this);
  setZone(destination);
}

void BlackAndWhitePiece::draw(EZWindow& w) const
{
 const AbstractZone *zone = getZone();
 if(zone!=nullptr)
 {
  const Point& p = zone->getAnchor();
  const EZImage& image(isWhite_?imageWhite:imageBlack);
  const int delta = 5;

  if(getState()==PieceState::Highlighted)
  {
    w.setColor(ez_yellow);
    w.setThick(4);
    w.drawCircle(p.getX()+delta,p.getY()+delta,p.getX()+image.getWidth()-2*delta,p.getY()+image.getHeight()-2*delta);
  }
  else if(getState()==PieceState::Threatened)
  {
    w.setColor(ez_red);
    w.setThick(4);
    w.fillCircle(p.getX()+delta,p.getY()+delta,p.getX()+image.getWidth()-2*delta,p.getY()+image.getHeight()-2*delta);
  }
  image.paint(w,p.getX(),p.getY());
 }
 else
   throw runtime_error("BlackAndWhitePiece::draw(): getZone() gives a nullptr !");
}

void BlackAndWhitePiece::write(ostream& os) const
{
 AbstractPiece::write(os);
 os << (isWhite_?"White":"Black");
}
