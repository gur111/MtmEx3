#include "Soldier.h"

#include <memory>
#include <string>

#include "Character.h"
#include "GameException.h"
#define ADD_AMMO 3
#define MAX_RANGE 3
#define DECREASE_POWER 2
#define SPLASH_ZONE 3
using mtm::Soldier;

Soldier::Soldier(units_t health, units_t power, Team team, units_t range,
                 units_t ammo)
    : Character(health, power, team, range, ammo, SOLDIER) {
    type = SOLDIER;
}

void Soldier::move(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                   const mtm::GridPoint& d_place) {
    if (GridPoint::distance(s_place, d_place) > MAX_RANGE) {
        throw MoveTooFar();
    }
    if (board.isWithinLimits(d_place) == false) {
        throw IllegalCell();
    }
    if (board(d_place.row, d_place.col) != nullptr) {
        throw CellOccupied();
    }
    std::shared_ptr<Character> temp = board(s_place.row, s_place.col);
    board(d_place.row, d_place.col) = temp;
    board(s_place.row, s_place.col) = nullptr;
}

void Soldier::reload() { ammo += ADD_AMMO; }

void Soldier::shoot(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                    const mtm::GridPoint& d_place) {
    if (d_place == s_place) {
        board(d_place.row, d_place.col)->changeHealth(-power);
    } else {
        board(d_place.row, d_place.col)
            ->changeHealth(-((power + 1) / DECREASE_POWER));
    }
    if (board(d_place.row, d_place.col)->getHealth() <= 0) {
        board(d_place.row, d_place.col) = nullptr;
    }
}

void Soldier::attack(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                     const mtm::GridPoint& d_place) {
    if (!board.isWithinLimits(d_place)) {
        throw IllegalCell();
    }
    if ((s_place.row != d_place.row && s_place.col != d_place.col) ||
        GridPoint::distance(s_place, d_place) > range) {
        throw OutOfRange();
    }
    if (ammo < 1) {
        throw OutOfAmmo();
    }
    ammo--;
    GridPoint point(0, 0);
    for (point.row; point.row < board.height(); point.row++) {
        for (point.col = 0; point.col < board.width(); point.col++) {
            if (GridPoint::distance(point, d_place) <=
                    ((range + 1) / SPLASH_ZONE) &&
                board(point.row, point.col) != nullptr &&
                board(point.row, point.col)->getTeam() != team) {
                shoot(board, d_place, point);
            }
        }
    }
}

std::shared_ptr<mtm::Character> Soldier::clone() const {
    return std::shared_ptr<Character>(
        new Soldier(health, power, team, range, ammo));
}
