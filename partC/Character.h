#ifndef MTMEX3_CHARACTER_H
#define MTMEX3_CHARACTER_H

#include <functional>
#include <iostream>
#include <string>
#include <assert.h>
#include "../Auxiliaries.h"
#include "GameBoard.h"

namespace mtm {
    class Character {
    protected:
        units_t health;
        units_t power;
        Team team;
        units_t range;
        units_t ammo;
        Character(GameBoard matrix, units_t health, units_t power, Team team, units_t range, units_t ammo);
        virtual ~Character();
        virtual void move(GameBoard& board, const GridPoint& s_place, const GridPoint& d_place) = 0;
        virtual void attack(GameBoard& board, const GridPoint& s_place, const GridPoint& d_place) = 0;
        virtual void reload(GameBoard& board, const GridPoint& s_place) = 0;
        virtual std::shared_ptr<Character> clone() const = 0;
    };
}
#endif //MTMEX3_CHARACTER_H
