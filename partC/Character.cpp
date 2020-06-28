#include "Character.h"

#include <assert.h>

#include <functional>
#include <iostream>
#include <string>

#include "../Auxiliaries.h"
#include "GameBoard.h"

namespace mtm {

    Character::Character(units_t health, units_t power, Team team,
                         units_t range, units_t ammo, CharacterType type)
            : health(health),
              power(power),
              team(team),
              range(range),
              ammo(ammo),
              type(type){
        if (health <= 0 || power < 0 || range < 0 || ammo < 0) {
            throw IllegalArgument();
        }
    }

    CharacterType Character::getType() const { return type; }

    Team Character::getTeam() const { return team; }

    units_t Character::getHealth() const { return health; }

    void Character::changeHealth(units_t delta) { health += delta; }

    Character::Character(const Character& other) {
        (*this) = other;
    }

    void Character::move(GameBoard<Character>& board, const GridPoint& s_place, const GridPoint& d_place) {
        if (GridPoint::distance(s_place, d_place) > speed) {
            throw MoveTooFar();
        }
        if (!board.isWithinLimits(d_place)) {
            throw IllegalCell();
        }
        if (board(d_place.row, d_place.col) != nullptr) {
            throw CellOccupied();
        }
        std::shared_ptr<Character> temp = board(s_place.row, s_place.col);
        board(d_place.row, d_place.col) = temp;
        board(s_place.row, s_place.col) = nullptr;
    }


}  // namespace mtm