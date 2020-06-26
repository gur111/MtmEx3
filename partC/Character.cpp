#include "Character.h"

#include <assert.h>

#include <functional>
#include <iostream>
#include <string>

#include "../Auxiliaries.h"
#include "GameBoard.h"

namespace mtm {

Character::Character(units_t s_health, units_t s_power, Team s_team,
                     units_t s_range, units_t s_ammo)
    : health(s_health),
      power(s_power),
      team(s_team),
      range(s_range),
      ammo(s_ammo) {}

CharacterType Character::getType() { return type; }

}  // namespace mtm