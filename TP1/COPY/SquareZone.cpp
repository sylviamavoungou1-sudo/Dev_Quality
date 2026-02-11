// SquareZone.cpp

#include <iostream>

using namespace std;

#include "ez-draw++.hpp"
#include "SquareZone.hpp"

SquareZone::SquareZone(uint _x,uint _y,size_t w,size_t h)
 : AbstractZone(_x,_y),width(w),height(h)
{ DBG("SquareZone::SquareZone(uint _x,uint _z,size_t w,size_t h)"); }

SquareZone::SquareZone(istream& is)
 : AbstractZone(is),width(10),height(10)
{
 DBG("SquareZone::SquareZone(istream&)");
 is >> width >> height;
}

SquareZone::~SquareZone()
{ DBG("SquareZone::~SquareZone()"); }

bool SquareZone::isOver(uint _x,uint _y) const
{
  uint x = getAnchor().getX(), y = getAnchor().getY();
  return x <= _x && _x < x+width &&
         y <= _y && _y < y+height;
}

void SquareZone::draw(EZWindow& w,ZoneState state) const
{
 int x = getAnchor().getX(), y = getAnchor().getY();
 if(state==ZoneState::Highlighted)
 {
   w.setColor(ez_blue);
   w.setThick(1);
   w.fillRectangle(x,y,int(x+width),int(y+height));
   w.setColor(ez_yellow);
   w.setThick(4);
   w.drawRectangle(x,y,int(x+width),int(y+height));
 }
}

void SquareZone::write(ostream& os) const
{
 os << "SquareZone ";
 AbstractZone::write(os);
 os << " " << width << " " << height;
}
