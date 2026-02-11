// SquareZone.hpp

#ifndef SQUARE_ZONE_HPP
#define SQUARE_ZONE_HPP

#include "AbstractZone.hpp"

/*
Pour les échecs, le voisinage d'une case z peut être représenté par un tableau (ou vecteur) dont les 8 éléments correspondent aux directions de déplacement vers les cases voisines :
 0 1 2
 3 z 4
 5 6 7
*/

class SquareZone : public AbstractZone {
 size_t width,height;
 public:
  SquareZone(uint x,uint y,size_t w,size_t h);
  SquareZone(istream& is);
  ~SquareZone() override;
  bool isOver(uint x,uint y) const override;
  void draw(EZWindow&,ZoneState state) const override;
private:
  void write(ostream&) const override;
};
#endif
