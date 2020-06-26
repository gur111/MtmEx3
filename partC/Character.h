#ifndef MTMEX3_CHARACTER_H
#define MTMEX3_CHARACTER_H

#include <assert.h>

#include <functional>
#include <iostream>
#include <string>

#include "../Auxiliaries.h"
#include "GameBoard.h"

namespace mtm {
class Character {
   protected:
    CharacterType type;
    units_t health;
    units_t power;
    Team team;
    units_t range;
    units_t ammo;

   public:
    Character(units_t health, units_t power, Team team, units_t range,
              units_t ammo);
    virtual ~Character();
    virtual void move(GameBoard& board, const GridPoint& s_place,
                      const GridPoint& d_place) = 0;
    virtual void attack(GameBoard& board, const GridPoint& s_place,
                        const GridPoint& d_place) = 0;
    virtual void reload(GameBoard& board, const GridPoint& s_place) = 0;
    virtual std::shared_ptr<Character> clone() const = 0;
    CharacterType getType();
};
}  // namespace mtm
#endif  // MTMEX3_CHARACTER_H
