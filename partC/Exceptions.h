#ifndef MTMEX3_GAME_BASE_H
#define MTMEX3_GAME_BASE_H
#include <string>
#include <typeinfo>
#include <iostream>

#define DEFAULT_ERROR_PREFIX "A game related error has occurred: "

#include "../Auxiliaries.h"

namespace mtm {

class Exception : public std::exception {};

class GameException : public Exception {
   protected:
    std::string error = "";

   public:
    const char* what() const noexcept {
        return (error + typeid(*this).name()).c_str();
    }
};

class IllegalArgument : public GameException {
   public:
    const char* what() const noexcept {
        return DEFAULT_ERROR_PREFIX "IllegalArgument";
    }
};
class IllegalCell : public GameException {
       public:
    const char* what() const noexcept {
        return DEFAULT_ERROR_PREFIX "IllegalCell";
    }
};
class CellEmpty : public GameException {
       public:
    const char* what() const noexcept {
        return DEFAULT_ERROR_PREFIX "CellEmpty";
    }
};
class MoveTooFar : public GameException {
       public:
    const char* what() const noexcept {
        return DEFAULT_ERROR_PREFIX "MoveTooFar";
    }
};
class CellOccupied : public GameException {
       public:
    const char* what() const noexcept {
        return DEFAULT_ERROR_PREFIX "CellOccupied";
    }
};
class OutOfRange : public GameException {
       public:
    const char* what() const noexcept {
        return DEFAULT_ERROR_PREFIX "OutOfRange";
    }
};
class OutOfAmmo : public GameException {
       public:
    const char* what() const noexcept {
        return DEFAULT_ERROR_PREFIX "OutOfAmmo";
    }
};
class IllegalTarget : public GameException {
       public:
    const char* what() const noexcept {
        return DEFAULT_ERROR_PREFIX "IllegalTarget";
    }
};

}  // namespace mtm

#endif