// AbstractPiece.hpp

#include <vector>
#include <unordered_set>
#include <stdexcept>

#ifndef ABSTRACT_PIECE_HPP
#define ABSTRACT_PIECE_HPP

// Activer le symbole ci-dessous pour que la classe AbstractPiece ne dépende plus de ses classes dérivées.
#define ADVANCED_FACTORY

#ifdef ADVANCED_FACTORY
// Pour la Factory avancée :
#include <string>
#include <map>
#endif

typedef unsigned int uint;
typedef unsigned long int ulong;

#include "Point.hpp"

class AbstractZone;

enum class PieceState {
 Normal, Highlighted, Threatened, InHand
};

class AbstractPiece {
  PieceState state;
  AbstractZone *zone;
 public:
  AbstractPiece();
  AbstractPiece(const AbstractPiece&);
  AbstractPiece(istream& is);
  virtual ~AbstractPiece();
  inline PieceState getState() const { return state; }
  inline void setState(PieceState _state) { state = _state; }
  inline AbstractZone *getZone() const { return zone; }
  inline void setZone(AbstractZone *_zone) { zone = _zone; }
  virtual void moveToZone(AbstractZone *destination) = 0;
  virtual bool isOver(uint x,uint y) const = 0;
  virtual unordered_set<AbstractZone*> canMoveTo() const = 0;
  virtual void draw(EZWindow&) const = 0;

  friend ostream& operator<<(ostream&,const AbstractPiece&); // Cet opérateur n'étant pas une fonction membre, il ne peut pas être virtual !
  virtual void write(ostream&) const; // Virtuelle
  static AbstractPiece* load(istream&);

#ifdef ADVANCED_FACTORY
private:
  typedef AbstractPiece* (*factory_function)(istream& is);
  static map<string,factory_function> factories;
public:
  template<typename classType>
  static void register_factory_function(const char *className)
    { factories[className] = [](istream& is)-> AbstractPiece* { return new classType(is); }; }
  static void print_registered_factory_functions(std::ostream& os);
#endif
};

#endif
