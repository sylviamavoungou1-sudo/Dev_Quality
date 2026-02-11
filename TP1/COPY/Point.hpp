// Point.hpp

#ifndef POINT_HPP
#define POINT_HPP

#include "Chess.hpp"

class Point {
  static const uint taille = 3;
  uint x,y;
 public:
  Point(unsigned int _x,unsigned int _y);
  Point(const Point&);
  Point(istream& is);
  ~Point();
  inline uint getX() const { return x; }
  inline uint getY() const { return y; }
  inline void setXY(unsigned int _x,unsigned int _y) { x = _x; y = _y; }
         bool isOver(uint _x,uint _y) const;
         void draw(EZWindow&,bool isActive=false) const;
  inline Point& operator=(const Point& p) { x = p.x; y = p.y; return *this; }

  friend ostream& operator<<(ostream& os,const Point& p);
  friend istream& operator>>(istream& is,      Point& p);
};

#endif
