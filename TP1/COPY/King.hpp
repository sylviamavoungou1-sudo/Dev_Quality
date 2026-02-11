// King.hpp

#ifndef KING_HPP
#define KING_HPP

#include "BlackAndWhitePiece.hpp"

class King : public BlackAndWhitePiece {
  bool hasMoved;
 public:
  King(bool isWhite,ChessBoard *chessboard);
  King(istream& is,ChessBoard *chessboard);
  ~King() override;
  unordered_set<AbstractZone*> canMoveTo() const override;
  void moveToZone(AbstractZone *destination) override;
private:
  void write(ostream&) const override;
};
#endif
