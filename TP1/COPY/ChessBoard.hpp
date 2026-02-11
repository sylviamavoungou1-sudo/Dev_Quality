// ChessBoard.hpp

#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <vector>
#include <unordered_set>
#include <algorithm>

#include "SquareZone.hpp"
#include "BlackAndWhitePiece.hpp"

class ChessBoard {
  EZImage image;
  size_t nb_column,nb_row;
  Point anchor;
  size_t width,height;
  vector<AbstractZone*> zones;
  bool whiteToMove;
  AbstractPiece* previousThreatenedPiece;
  AbstractZone*  previous_zone;
  SquareZone     hand;
  unordered_set<AbstractZone*> destinations;
 public:
  ChessBoard(const char *boardFilename,size_t _nbRow,size_t _nbColumn,size_t _x,size_t _y,size_t _width,size_t _height);
  ~ChessBoard();
  void add(AbstractZone *zone);
  inline AbstractZone* getZone(size_t column,size_t row)
   { return (column<nb_column && row<nb_row ? zones[row*nb_row+column] : nullptr); }
  inline size_t getZone(const AbstractZone* z) const
   { return find(zones.begin(),zones.end(),z)-zones.begin(); }
  inline void getColumnRow(const AbstractZone* zone,size_t& column,size_t& row) const
   { size_t t = getZone(zone); column = t % nb_row; row = t / nb_row; }
  void setPiece(size_t column,size_t row,AbstractPiece* _piece);
  AbstractZone*  isOverZone(uint _x,uint _y);
  AbstractPiece* isOverPiece(uint _x,uint _y);
  void draw(EZWindow& w) const;
  void buttonPress(int mouse_x,int mouse_y);
  void buttonRelease(int mouse_x,int mouse_y);
  void motionNotify(int mouse_x,int mouse_y);
  friend ostream&  operator<<(ostream&  os, const ChessBoard& board);
  void save(ostream& os) const;
  void load(istream& is);
};
#endif
