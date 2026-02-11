// AbstractPiece.cpp
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

#include "ez-draw++.hpp"
#include "AbstractPiece.hpp"

AbstractPiece::AbstractPiece()
 : state(PieceState::Normal),zone(nullptr)
{ DBG("AbstractPiece::AbstractPiece(uint,uint)"); }

AbstractPiece::AbstractPiece(const AbstractPiece& o)
 : state(PieceState::Normal),zone(nullptr)
{ DBG("AbstractPiece::AbstractPiece(const AbstractPiece& o)"); }

AbstractPiece::AbstractPiece(istream& is)
 :state(PieceState::Normal),zone(nullptr)
{
 DBG("AbstractPiece::AbstractPiece(istream&)");
}

AbstractPiece::~AbstractPiece()
{ DBG("AbstractPiece::~AbstractPiece()"); }

// void AbstractPiece::draw(EZWindow& w) const {}

ostream& operator<<(ostream& os,const AbstractPiece& p) // Ne peut pas être virtual
{
 p.write(os); // mais écrire() peut l'être !
 return os;
}

void AbstractPiece::write(ostream& os) const
{}

#ifdef ADVANCED_FACTORY

map<string,AbstractPiece::factory_function> AbstractPiece::factories;

void AbstractPiece::print_registered_factory_functions(ostream& os)
{
  os << "Classes dont les factory ont été enregistrées associées à une chaîne de typage :" << endl;
  for(const auto& e : factories) // Boucle « Pour » généralisée (C++11) et utilisation de la déduction de type (« auto »).
    os << e.first << endl;   // e est une paire constituée de la chaîne (membre first) et de l'adresse de la fonction (membre second).
}

AbstractPiece *AbstractPiece::load(istream& is)
{
 string typeName;
 is >> typeName;
 try
 {
   factory_function f = factories.at(typeName); // On cherche la fonction factory qui est enregistrée sous ce nom de forme
   AbstractPiece *piece = (*f)(is);      // On appelle la fonction qui construit l'instance de AbstractPiece.
   return piece;                 // On renvoie la forme construite.
 }
 catch (std::range_error&)     // Si la chaîne de type n'a pas été trouvée dans le map, on lance une runtime_error.
 {
    std::ostringstream oss;
    oss << "Chaîne de type de forme inconnue \"" << typeName << "\". Impossible de créer cette AbstractPiece et donc de continuer. Abandon.";
    throw std::runtime_error(oss.str());
 }
}
#else
// Pour la prochaine fonction, on a besoin de rajouter les déclarations des classes
// correspondantes... C'est l'inévitable défaut de cette conception relativement
// simple.
#include "King.hpp"

AbstractPiece *AbstractPiece::load(istream& is)
{
 string type;
 is >> type;
      if(type=="King") return new Rectangle(is);
// else if(type=="Carre")     return new Carre(is);
 else
  throw range_error("Type rencontré inconnu dans AbstractPiece *AbstractPiece::load(istream&).");
}
#endif
