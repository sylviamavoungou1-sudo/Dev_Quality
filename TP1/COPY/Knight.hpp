// Knight.hpp

#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "BlackAndWhitePiece.hpp"

class Knight : public BlackAndWhitePiece {
 public:
  Knight(bool isWhite,ChessBoard *chessboard);
  Knight(istream& is,ChessBoard *chessboard);
  ~Knight() override;
  unordered_set<AbstractZone*> canMoveTo() const override;
private:
  void write(ostream&) const override;
};
#endif
