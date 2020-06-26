#include "Medic.h"

#include <memory>
#include <string>

#include "Character.h"
#include "GameException.h"

using mtm::Medic;

Medic::Medic(units_t health, units_t power, Team team, units_t range,
             units_t ammo)
        : Character(health, power, team, range, ammo) {
    type = MEDIC;
}

void Medic::move(GameBoard <Character>& board, const mtm::GridPoint& s_place,
                 const mtm::GridPoint& d_place) {
    if (GridPoint::distance(s_place, d_place) >= 5) {
        throw MoveTooFar();
    }
    if (board(d_place.row, d_place.col) != nullptr) {
        throw CellOccupied();
    }
    if (board.isWithinLimits(d_place) == false) {
        throw IllegalCell();
    }
    std::shared_ptr<Character> temp = board(s_place.row, s_place.col);
    board(d_place.row, d_place.col) = temp;
    board(s_place.row, s_place.col) = nullptr;
}

void Medic::reload() { ammo += 5; }

void Medic::attack(GameBoard <Character>& board, const mtm::GridPoint& s_place,
                   const mtm::GridPoint& d_place) {
    if (!board.isWithinLimits(d_place)) {
        throw IllegalCell();
    }
    if (GridPoint::distance(d_place, s_place) == 0) {
        throw IllegalTarget();
    }
    if (GridPoint::distance(d_place, s_place) > range) {
        throw OutOfRange();
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
    return std::shared_ptr<mtm::Character>(new Medic(health, power,
                                                     team, range, ammo));
}
