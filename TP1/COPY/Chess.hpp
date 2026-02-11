// Chess.hpp

#ifndef CHESS_HPP
#define CHESS_HPP

#ifdef DEBUG
#define DBG(msg) cerr << msg << endl
#else
#define DBG(msg)
#endif


#if defined(__clang__)
#define TODO(x)
#elif defined(__GNUC__) || defined(__GNUG__)
//#define TODO(x) #warning(x)
//#define TODO(x) #pragma message (x)
#define TODO(x)
//#define TODO(x) std::cerr << x << std::endl;
#elif defined(_MSC_VER)
//#define TODO(x) #pragma message (x)
#define TODO(x)
#elif
#error "Cas imprévu !"
#endif

typedef unsigned int uint;
typedef unsigned long int ulong;

#endif
