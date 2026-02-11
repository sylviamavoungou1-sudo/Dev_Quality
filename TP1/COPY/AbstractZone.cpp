// AbstractZone.cpp
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

#include "ez-draw++.hpp"
#include "AbstractZone.hpp"
#include "AbstractPiece.hpp"

AbstractZone::AbstractZone(uint x,uint y)
 : anchor(x,y),piece(nullptr)
{ DBG("AbstractZone::AbstractZone(uint,uint)"); }

AbstractZone::AbstractZone(const AbstractZone& o)
 : anchor(o.anchor),piece(nullptr)
{ DBG("AbstractZone::AbstractZone(const AbstractZone& o)"); }

AbstractZone::AbstractZone(istream& is)
 : anchor(0,0),piece(nullptr)
{
 is >> anchor;
 DBG("AbstractZone::AbstractZone(istream&)");
}

AbstractZone::~AbstractZone()
{
 delete piece;
 DBG("AbstractZone::~AbstractZone()" <<);
}

// void AbstractZone::draw(EZWindow& w) const {}

AbstractZone* AbstractZone::getNeighbour(size_t i) const
{
  if(i<neighbors.size())
    return neighbors[i];
  else
    throw runtime_error("AbstractZone::getNeighbour(i): i is larger than the neighbors count of this AbstractZone.");
}

ostream& operator<<(ostream& os,const AbstractZone& z) // Ne peut pas être virtual
{
 z.write(os); // mais écrire() peut l'être !
 return os;
}

void AbstractZone::write(ostream& os) const
{
 os << anchor;
}

void AbstractZone::setPiece(AbstractPiece* _piece)
{
 //delete piece;
TODO("Il faut probablement remettre le delete pour éviter une fuite de mémoire.")
 piece = _piece;
 if(piece!=nullptr)
   piece->setZone(this);
}

#ifdef ADVANCED_FACTORY

map<string,AbstractZone::factory_function> AbstractZone::factories;

void AbstractZone::print_registered_factory_functions(ostream& os)
{
  os << "Classes dont les factory ont été enregistrées associées à une chaîne de typage :" << endl;
  for(const auto& e : factories) // Boucle « Pour » généralisée (C++11) et utilisation de la déduction de type (« auto »).
    os << e.first << endl;   // e est une paire constituée de la chaîne (membre first) et de l'adresse de la fonction (membre second).
}

AbstractZone *AbstractZone::load(istream& is)
{
 string typeName;
 is >> typeName;
 try
 {
   factory_function f = factories.at(typeName); // On cherche la fonction factory qui est enregistrée sous ce nom de forme
   AbstractZone *zone = (*f)(is);      // On appelle la fonction qui construit l'instance de AbstractZone.
   return zone;                 // On renvoie la forme construite.
 }
 catch (std::range_error& e)     // Si la chaîne de type n'a pas été trouvée dans le map, on lance une runtime_error.
 {
    std::ostringstream oss;
    oss << "Chaîne de type de AbstractZone inconnue \"" << typeName << "\". Impossible de créer cette zone et donc de continuer. Abandon.";
    throw std::runtime_error(oss.str());
 }
}
#else
// Pour la prochaine fonction, on a besoin de rajouter les déclarations des classes
// correspondantes... C'est l'inévitable défaut de cette conception relativement
// simple.
#include "SquareZone.hpp"

AbstractZone *AbstractZone::load(istream& is)
{
 string type;
 is >> type;
      if(type=="SquareZone") return new SquareZone(is);
// else if(type=="Carre")     return new Carre(is);
 else
  throw range_error("Type rencontré inconnu dans AbstractZone *AbstractZone::load(istream&).");
}
#endif
