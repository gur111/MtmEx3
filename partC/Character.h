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
        GameBoard matrix;
        units_t health;
        units_t power;
        Team type;
        units_t range;
        units_t ammo;
        Character(GameBoard matrix, units_t health, units_t power, units_t range, units_t ammo);
        virtual ~Character();
        virtual void move(const GridPoint& s_place,const GridPoint& d_place) = 0;
        virtual void attack(const GridPoint& s_place,const GridPoint& d_place) = 0;
        virtual void reload(const GridPoint& s_place) = 0;
        virtual void shoot(const GridPoint& s_place,const GridPoint& d_place, units_t damage) = 0
        virtual *Character clone() const = 0;
    };
}
#endif //MTMEX3_CHARACTER_H
