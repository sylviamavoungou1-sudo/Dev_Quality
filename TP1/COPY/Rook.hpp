// Rook.hpp

#ifndef ROOK_HPP
#define ROOK_HPP

#include "BlackAndWhitePiece.hpp"

class Rook : public BlackAndWhitePiece {
 public:
  Rook(bool isWhite,ChessBoard *chessboard);
  Rook(istream& is,ChessBoard *chessboard);
  ~Rook() override;
  unordered_set<AbstractZone*> canMoveTo() const override;
private:
  void write(ostream&) const override;
};
#endif
