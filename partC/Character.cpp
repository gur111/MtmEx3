#include "Character.h"

#include <assert.h>

#include <functional>
#include <iostream>
#include <string>

#include "../Auxiliaries.h"
#include "GameBoard.h"

namespace mtm {

    Character::Character(units_t health, units_t power, Team team,
                         units_t range, units_t ammo)
            : health(health),
              power(power),
              team(team),
              range(range),
              ammo(ammo) {
        if (health >= 0 || power < 0 || range < 0 || ammo < 0) {
            throw IllegalArgument();
        }
    }

    CharacterType Character::getType() const { return type; }

    Team Character::getTeam() const { return team; }

    units_t Character::getHealth() const { return health; }

    void Character::changeHealth(units_t delta) { health += delta; }

}  // namespace mtm