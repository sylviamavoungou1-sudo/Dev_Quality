// Bishop.hpp

#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "BlackAndWhitePiece.hpp"

class Bishop : public BlackAndWhitePiece {
 public:
  Bishop(bool isWhite,ChessBoard *chessboard);
  Bishop(istream& is,ChessBoard *chessboard);
  ~Bishop() override;
  unordered_set<AbstractZone*> canMoveTo() const override;
private:
  void write(ostream&) const override;
};
#endif
