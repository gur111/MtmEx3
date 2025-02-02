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
    units_t health;
    units_t power;
    Team team;
    units_t range;
    units_t ammo;
    CharacterType type;
    units_t speed;

   public:
    Character(units_t health, units_t power, Team team, units_t range,
              units_t ammo, CharacterType type, units_t speed);
    virtual ~Character() = default;
    void move(GameBoard<Character>& board, const GridPoint& s_place,
              const GridPoint& d_place);
    virtual void attack(GameBoard<Character>& board, const GridPoint& s_place,
                        const GridPoint& d_place) = 0;
    virtual void changeHealth(units_t delta);
    virtual units_t getHealth() const;
    virtual void reload() = 0;
    virtual std::shared_ptr<Character> clone() const = 0;
    CharacterType getType() const;
    virtual Team getTeam() const;
    Character(const Character& other);
};
}  // namespace mtm
#endif  // MTMEX3_CHARACTER_H
