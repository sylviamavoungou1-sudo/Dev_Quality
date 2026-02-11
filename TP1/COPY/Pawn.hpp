// Pawn.hpp

#ifndef PAWN_HPP
#define PAWN_HPP

#include "BlackAndWhitePiece.hpp"

class Pawn : public BlackAndWhitePiece {
  bool hasMoved;
 public:
  Pawn(bool isWhite,ChessBoard *chessboard);
  Pawn(istream& is,ChessBoard *chessboard);
  ~Pawn() override;
  unordered_set<AbstractZone*> canMoveTo() const override;
  void moveToZone(AbstractZone *destination) override;
private:
  void write(ostream&) const override;
};
#endif
