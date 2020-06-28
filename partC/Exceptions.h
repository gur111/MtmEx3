#ifndef MTMEX3_GAME_BASE_H
#define MTMEX3_GAME_BASE_H
#include <string>
#include <typeinfo>

#include "../Auxiliaries.h"

namespace mtm {

class Exception : public std::exception {};

class GameException : public Exception {
   protected:
    std::string error = "A game related error has occurred: ";

   public:
    std::string what() noexcept { return error + typeid(*this).name(); }
};

class IllegalArgument : public GameException {};
class IllegalCell : public GameException {};
class CellEmpty : public GameException {};
class MoveTooFar : public GameException {};
class CellOccupied : public GameException {};
class OutOfRange : public GameException {};
class OutOfAmmo : public GameException {};
class IllegalTarget : public GameException {};

};  // namespace mtm

#endif