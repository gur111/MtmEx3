#include <assert.h>
#include "Character.h"
#include "../Auxiliaries.h"
#include "GameBoard.h"
#include <functional>
#include <iostream>
#include <string>

using mtm::Character;

Character::Character(GameBoard s_matrix, units_t s_health, units_t s_power, Team s_team, units_t s_range,
                     units_t s_ammo) : {
    health = s_health;
    power = s_power;
    team = s_team;
    range = s_range;
    ammo = s_ammo;
}

