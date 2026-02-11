// Point.cpp

#include <iostream>

using namespace std;

#include "ez-draw++.hpp"
#include "Point.hpp"

Point::Point(uint _x,uint _y)
 : x(_x),y(_y)
{ DBG("Point::Point(uint,uint)"); }

Point::Point(const Point& o)
 : Point(o.x,o.y)
{ DBG("Point::Point(const Point&)"); }

Point::Point(istream& is)
 : x(0),y(0)
{ is >> x >> y; }

Point::~Point()
{ DBG("Point::~Point()"); }

bool Point::isOver(uint _x,uint _y) const
{
 uint dx = (x>=_x?x-_x:_x-x); // Astuce pour dx toujours >=0 en restant en uint !
 uint dy = (y>=_y?y-_y:_y-y); // Idem
 return (dx <= taille && dy <= taille);
}

void Point::draw(EZWindow& w,bool isActive) const
{
 if(isActive)
   w.fillRectangle(x-taille,y-taille,x+taille,y+taille);
 else
   w.drawRectangle(x-taille,y-taille,x+taille,y+taille);
}

ostream& operator<<(ostream& os,const Point& p)
{ os << p.x << " " << p.y; return os; }

istream& operator>>(istream& is,Point& p)
{ is >> p.x >> p.y; return is; }
