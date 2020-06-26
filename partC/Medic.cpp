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

void Medic::move(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                 const mtm::GridPoint& d_place) {
    if (GridPoint::distance(s_place, d_place) >= 5) {
        throw MoveTooFar();
    }
    if (board(d_place.row, d_place.col) != nullptr) {
        throw CellOccupied();
    }
    std::shared_ptr<Character> temp = board(s_place.row, s_place.col);
    board(d_place.row, d_place.col) = temp;
    board(s_place.row, s_place.col) = nullptr;
}

void Medic::reload() {
    ammo += 5;
}

void Medic::attack(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                   const mtm::GridPoint& d_place) {
    if (board(d_place.row, d_place.col)->team == nullptr) {
        throw IllegalTarget();
    }
    if (s_place.col > board.width() || s_place.row > board.height()) {
        throw IllegalCell();
    }
    if (GridPoint::distance(s_place, d_place) > range ||
        GridPoint::distance(s_place, d_place) > ceil(range / 2)) {
        throw OutOfRange();
    }
    if (GridPoint::distance(d_place, s_place)) {
        throw IllegalTarget();
    }
    if (board(d_place.row, d_place.col)->team == team) {
        board(d_place.row, d_place.col)->health += power;
    } else {
        if (ammo < 1) {
            throw OutOfAmmo();
        }
        board(d_place.row, d_place.col)->health -= power;
        ammo--;
    }
    if (board(d_place.row, d_place.col)->health <= 0) {
        board(d_place.row, d_place.col) = nullptr;
    }
}
