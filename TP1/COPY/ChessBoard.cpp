// ChessBoard.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

#include "ez-draw++.hpp"

#include "ChessBoard.hpp"
#include "SquareZone.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Rook.hpp"
#include "Pawn.hpp"

ChessBoard::ChessBoard(const char *board_filename,size_t _nb_row,size_t _nb_column,size_t _x,size_t _y,size_t _width,size_t _height)
 : image(board_filename),nb_column(_nb_column),nb_row(_nb_row),anchor(_x,_y),width(_width),height(_height),whiteToMove(true),
  previousThreatenedPiece(nullptr),previous_zone(nullptr),hand(0,0,_width,_height)
{
 for(size_t j=0;j<nb_row;++j)
 for(size_t i=0;i<nb_column;++i)
   add(new SquareZone(_x+i*width,_y+j*height,width-1,height-1));

/* Neighbors :
 0 1 2
 3 z 4
 5 6 7
*/
 for(size_t j=0;j<nb_row;   ++j)
 for(size_t i=0;i<nb_column;++i)
 {
  AbstractZone& z = *getZone(i,j);
  z.addNeighbour(getZone(i-1,j-1));
  z.addNeighbour(getZone(i  ,j-1));
  z.addNeighbour(getZone(i+1,j-1));
  z.addNeighbour(getZone(i-1,j  ));
  z.addNeighbour(getZone(i+1,j  ));
  z.addNeighbour(getZone(i-1,j+1));
  z.addNeighbour(getZone(i  ,j+1));
  z.addNeighbour(getZone(i+1,j+1));
 }

 setPiece(0,0,new Rook  (false,this));
 setPiece(1,0,new Knight(false,this));
 setPiece(2,0,new Bishop(false,this));
 setPiece(3,0,new Queen (false,this));
 setPiece(4,0,new King  (false,this));
 setPiece(5,0,new Bishop(false,this));
 setPiece(6,0,new Knight(false,this));
 setPiece(7,0,new Rook  (false,this));

 setPiece(0,1,new Pawn  (false,this));
 setPiece(1,1,new Pawn  (false,this));
 setPiece(2,1,new Pawn  (false,this));
 setPiece(3,1,new Pawn  (false,this));
 setPiece(4,1,new Pawn  (false,this));
 setPiece(5,1,new Pawn  (false,this));
 setPiece(6,1,new Pawn  (false,this));
 setPiece(7,1,new Pawn  (false,this));

 setPiece(0,6,new Pawn  (true,this));
 setPiece(1,6,new Pawn  (true,this));
 setPiece(2,6,new Pawn  (true,this));
 setPiece(3,6,new Pawn  (true,this));
 setPiece(4,6,new Pawn  (true,this));
 setPiece(5,6,new Pawn  (true,this));
 setPiece(6,6,new Pawn  (true,this));
 setPiece(7,6,new Pawn  (true,this));

 setPiece(0,7,new Rook  (true,this));
 setPiece(1,7,new Knight(true,this));
 setPiece(2,7,new Bishop(true,this));
 setPiece(3,7,new Queen (true,this));
 setPiece(4,7,new King  (true,this));
 setPiece(5,7,new Bishop(true,this));
 setPiece(6,7,new Knight(true,this));
 setPiece(7,7,new Rook  (true,this));
}

ChessBoard::~ChessBoard()
{
 for(auto& pz : zones)
   delete pz;
}

void ChessBoard::add(AbstractZone *zone)
{ zones.push_back(zone); }

void ChessBoard::setPiece(size_t column,size_t row,AbstractPiece* _piece)
{
 // Éventuellement ici ajouter la pièce à la collection de pièces.
 AbstractZone *zone = getZone(column,row);
 if(zone)
   zone->setPiece(_piece);
 else
   throw runtime_error("Board::setPiece() : zone inexistante !");
 _piece->setZone(zone);
}

void ChessBoard::draw(EZWindow& w) const
{
  image.paint(w,100,0);
  for(const auto& pz : destinations)
    if(pz!=nullptr)
      pz->draw(w,ZoneState::Highlighted);
    else
      throw runtime_error("ChessBoard::draw(): On ne devrait jamais passer ici !");

  for(const auto& pz : zones)
  {
    pz->draw(w);
    AbstractPiece *piece = pz->getPiece();
    if(piece != nullptr)
      piece->draw(w);
  }
  if(hand.getPiece()!=nullptr)
    hand.getPiece()->draw(w);
  w.setColor(whiteToMove?ez_white:ez_black);
  w.setFont(3);
  w.drawText(EZAlign::MC,100+image.getWidth()/2,15,whiteToMove?"White to move":"Black to move");
}

void ChessBoard::buttonPress(int mouse_x,int mouse_y)
{
 if (hand.getPiece() != nullptr)
   throw runtime_error("BoardWindow::buttonPress() : on ne devrait jamais arriver ici avec hand.getPiece()!=nullptr !");

 AbstractPiece      *piece   = isOverPiece(mouse_x,mouse_y);
 BlackAndWhitePiece *bw_piece = dynamic_cast<BlackAndWhitePiece*>(piece);
 if(piece!=nullptr && bw_piece!=nullptr && bw_piece->isWhite()==whiteToMove)
 {
   cout << "Capture " << *piece << endl;
   piece->setState(PieceState::InHand);
   destinations = piece->canMoveTo();
   previous_zone = piece->getZone();
   hand.setPiece(piece);
   //N'est plus utile : piece->setZone(nullptr);
   previous_zone->setPiece(nullptr);
 }
}

void ChessBoard::buttonRelease(int mouse_x,int mouse_y)
{
 if(hand.getPiece()==nullptr || previous_zone==nullptr)
   return;

 cerr << "Drop " << *hand.getPiece();

 AbstractZone  *mouseZone = isOverZone(mouse_x,mouse_y);
 AbstractZone  *destZone = (destinations.find(mouseZone)!=destinations.end()?*destinations.find(mouseZone):nullptr);
 AbstractPiece *advPiece = (destZone!=nullptr?destZone->getPiece():nullptr);
 if(advPiece!=nullptr)
 {
   cerr << " on an adverse square. Capture of " << *advPiece << endl;
   if(previousThreatenedPiece==advPiece)
      previousThreatenedPiece = nullptr;
   delete advPiece;
   hand.getPiece()->setState(PieceState::Normal);
   hand.getPiece()->moveToZone(destZone);
   hand.setPiece(nullptr);
   destinations.clear();
   whiteToMove = !whiteToMove;
 }
 else if(destZone!=nullptr)
 {
   cerr << " on an empty square." << endl;
   hand.getPiece()->setState(PieceState::Normal);
   hand.getPiece()->moveToZone(destZone);
   hand.setPiece(nullptr);
   destinations.clear();
   whiteToMove = !whiteToMove;
 }
 else
 {
   cerr << " on the origin square." << endl;
   hand.getPiece()->setState(PieceState::Normal);
   previous_zone->setPiece(hand.getPiece());
   hand.setPiece(nullptr);
   destinations.clear();
 }
}

 // Déplacement de la souris :
void ChessBoard::motionNotify(int mouse_x,int mouse_y)
{
 BlackAndWhitePiece* piece = dynamic_cast<BlackAndWhitePiece*>(isOverPiece(mouse_x,mouse_y));
 BlackAndWhitePiece* bwPieceInHand = dynamic_cast<BlackAndWhitePiece*>(hand.getPiece());
 if(previousThreatenedPiece)
   previousThreatenedPiece->setState(PieceState::Normal);
 if(piece && bwPieceInHand && piece->isWhite()!=bwPieceInHand->isWhite() && destinations.find(piece->getZone())!=destinations.end())
   piece->setState((hand.getPiece()?PieceState::Threatened:PieceState::Highlighted));
 previousThreatenedPiece = piece;

 hand.setAnchor(mouse_x,mouse_y);
}

AbstractZone* ChessBoard::isOverZone(uint _x,uint _y)
{
 for(const auto& pz : zones)
   if(pz->isOver(_x,_y))
     return pz;
 return nullptr;
}

AbstractPiece* ChessBoard::isOverPiece(uint _x,uint _y)
{
 for(const auto& pz : zones)
 {
   AbstractPiece *piece = pz->getPiece();
   if(piece && piece->isOver(_x,_y))
     return piece;
 }
 return nullptr;
}

ostream& operator<<(ostream& os, const ChessBoard& board)
{
 for(const auto& pz : board.zones)
   os << *pz << endl;
 return os;
}

void ChessBoard::save(ostream& os) const
{
 os << zones.size() << endl << *this;
}

void ChessBoard::load(istream& is)
{
 size_t nbZones,nbPieces;
 is >> nbZones >> nbPieces;
 for(;nbZones>0;--nbZones)
   add(AbstractZone::load(is));
}
