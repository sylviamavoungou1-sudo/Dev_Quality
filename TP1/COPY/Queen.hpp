// Queen.hpp

#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "BlackAndWhitePiece.hpp"

class Queen : public BlackAndWhitePiece {
 public:
  Queen(bool isWhite,ChessBoard *chessboard);
  Queen(istream& is,ChessBoard *chessboard);
  ~Queen() override;
  unordered_set<AbstractZone*> canMoveTo() const override;
private:
  void write(ostream&) const override;
};
#endif
