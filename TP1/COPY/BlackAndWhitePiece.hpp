// BlackAndWhitePiece.hpp

#ifndef BLACK_AND_WHITE_PIECE_HPP
#define BLACK_AND_WHITE_PIECE_HPP

#include "AbstractPiece.hpp"

class ChessBoard;

class BlackAndWhitePiece : public AbstractPiece {
  bool       isWhite_;
  EZImage    imageWhite,imageBlack;
  ChessBoard *chessboard;
 public:
  BlackAndWhitePiece(bool _isWhite,const char *whiteImageFileName,const char *blackImageFileName,ChessBoard *chessboard);
  BlackAndWhitePiece(istream& is,  const char *whiteImageFileName,const char *blackImageFileName,ChessBoard *chessboard);
  ~BlackAndWhitePiece() override;
  inline ChessBoard* getChessBoard() const { return chessboard; }
  bool isOver(uint x,uint y) const override;
  inline bool isWhite() const { return isWhite_; }
  void moveToZone(AbstractZone *destination) override;
  void draw(EZWindow&) const override;
protected:
  void write(ostream&) const override;
};
#endif
