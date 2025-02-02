#include "Medic.h"

#include <memory>
#include <string>

#include "Character.h"
#include "Exceptions.h"
#define ADD_AMMO 5
#define DEFAULT_MEDIC_SPEED 5

using mtm::Medic;

Medic::Medic(units_t health, units_t power, Team team, units_t range,
             units_t ammo)
    : Character(health, power, team, range, ammo, MEDIC, DEFAULT_MEDIC_SPEED) {}

void Medic::reload() { ammo += ADD_AMMO; }

void Medic::attack(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                   const mtm::GridPoint& d_place) {
    if (!board.isWithinLimits(d_place)) {
        throw IllegalCell();
    }
    if (GridPoint::distance(d_place, s_place) > range) {
        throw OutOfRange();
    }
    if (board(d_place.row, d_place.col) == nullptr ||
        GridPoint::distance(d_place, s_place) == 0) {
        throw IllegalTarget();
    }
    if (board(d_place.row, d_place.col)->getTeam() == team) {
        board(d_place.row, d_place.col)->changeHealth(power);
    } else {
        if (ammo < 1) {
            throw OutOfAmmo();
        }
        board(d_place.row, d_place.col)->changeHealth(-power);
        ammo--;
    }
    if (board(d_place.row, d_place.col)->getHealth() <= 0) {
        board(d_place.row, d_place.col) = nullptr;
    }
}

std::shared_ptr<mtm::Character> Medic::clone() const {
    return std::shared_ptr<mtm::Character>(
        new Medic(health, power, team, range, ammo));
}
