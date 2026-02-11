// AbstractZone.hpp

#include <stdexcept>
#include <vector>

#ifndef ABSTRACT_ZONE_HPP
#define ABSTRACT_ZONE_HPP

// Activer le symbole ci-dessous pour que la classe AbstractZone ne dépende plus de ses classes dérivées.
#define ADVANCED_FACTORY

#ifdef ADVANCED_FACTORY
// Pour la Factory avancée :
#include <string>
#include <map>
#endif

typedef unsigned int uint;
typedef unsigned long int ulong;

#include "Point.hpp"

class AbstractPiece;

enum class ZoneState {
 Normal, Highlighted
};


class AbstractZone {
  Point anchor;
  vector<AbstractZone*> neighbors;
  AbstractPiece* piece;
 public:
  AbstractZone(uint x,uint y);
  AbstractZone(const AbstractZone&);
  AbstractZone(istream& is);
  virtual ~AbstractZone();
  inline  const Point& getAnchor() const { return anchor; }
  inline  void  setAnchor(uint x,uint y) { anchor.setXY(x,y); }
  virtual bool  isOver(uint x,uint y) const = 0;
  virtual void  draw(EZWindow&,ZoneState state=ZoneState::Normal) const = 0;
  inline  void  addNeighbour(AbstractZone* z) { neighbors.push_back(z); }
  AbstractZone* getNeighbour(size_t i) const;
          void  setPiece(AbstractPiece* _piece);
  inline  AbstractPiece* getPiece() const { return piece; }
  friend  ostream& operator<<(ostream&,const AbstractZone&); // Cet opérateur n'étant pas une fonction membre, il ne peut pas être virtual !
  virtual void write(ostream&) const; // Virtuelle
  static AbstractZone* load(istream&);

#ifdef ADVANCED_FACTORY
private:
  typedef AbstractZone* (*factory_function)(istream& is);
  static map<string,factory_function> factories;
public:
  template<typename classType>
  static void register_factory_function(const char *className)
    { factories[className] = [](istream& is)-> AbstractZone* { return new classType(is); }; }
  static void print_registered_factory_functions(std::ostream& os);
#endif
};

#endif
