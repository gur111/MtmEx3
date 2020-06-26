#include "Soldier.h"

#include <memory>
#include <string>

#include "Character.h"
#include "GameException.h"

using mtm::Soldier;

Soldier::Soldier(units_t health, units_t power, Team team, units_t range,
                 units_t ammo)
    : Character(health, power, team, range, ammo) {
    type = SOLDIER;
}

void Soldier::move(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                   const mtm::GridPoint& d_place) {
    if (GridPoint::distance(s_place, d_place) >= 3) {
        throw MoveTooFar();
    }
    if (board(d_place.row, d_place.col) != nullptr) {
        throw CellOccupied();
    }
    std::shared_ptr<Character> temp = board(s_place.row, s_place.col);
    board(d_place.row, d_place.col) = temp;
    board(s_place.row, s_place.col) = nullptr;
}

void Soldier::reload(GameBoard<Character>& board, const mtm::GridPoint& s_place) {
    if (s_place.col > board.width() || s_place.row > board.height()) {
        throw IllegalCell();
    }
    ammo += 3;
}

void Soldier::shoot(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                    const mtm::GridPoint& d_place) {
    if (d_place.row == s_place.row && d_place.col == s_place.col) {
        board(d_place.row, d_place.col)->health -= ceil(power / 2);
    } else {
        board(d_place.row, d_place.col)->health -= power;
    }
    if (board(d_place.row, d_place.col)->health <= 0) {
        board(d_place.row, d_place.col) = nullptr;
    }
}

void Soldier::attack(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                     const mtm::GridPoint& d_place) {
    if (s_place.col > board.width() || s_place.row > board.height()) {
        throw IllegalCell();
    }
    if (ammo < 1) {
        throw OutOfAmmo();
    }
    if (s_place.row != d_place.row && s_place.col != d_place.col) {
        throw OutOfRange();
    }
    if (GridPoint::distance(s_place, d_place) > range) {
        throw OutOfRange();
    }
    ammo--;
    GridPoint point(0, 0);
    for (point.row; point.row < board.height(); point.row++) {
        for (point.col = 0; point.col < board.width(); point.col++) {
            if (GridPoint::distance(point, d_place) <= ceil(range / 3) &&
                board(point.row, point.col)->team != team &&
                board(point.row, point.col) != nullptr) {
                shoot(board, s_place, point);
            }
        }
    }
}
