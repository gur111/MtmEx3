#include "Soldier.h"

#include <algorithm>
#include <memory>
#include <string>

#include "Character.h"
#include "Exceptions.h"
#define ADD_AMMO 3
#define DECREASE_POWER 2
#define SPLASH_ZONE 3

namespace mtm {
Soldier::Soldier(units_t health, units_t power, Team team, units_t range,
                 units_t ammo)
    : Character(health, power, team, range, ammo, SOLDIER) {
    type = SOLDIER;
    speed = 3;
}

void Soldier::reload() { ammo += ADD_AMMO; }

void Soldier::shoot(GameBoard<Character>& board, const GridPoint& place) {
    board(place.row, place.col)->changeHealth(-((power + 1) / DECREASE_POWER));

    if (board(place.row, place.col)->getHealth() <= 0) {
        board(place.row, place.col) = nullptr;
    }
}

void Soldier::attack(GameBoard<Character>& board, const GridPoint& s_place,
                     const GridPoint& d_place) {
    if (not board.isWithinLimits(d_place)) {
        throw IllegalCell();
    } else if ((s_place.row != d_place.row && s_place.col != d_place.col) ||
               GridPoint::distance(s_place, d_place) > range) {
        throw OutOfRange();
    } else if (ammo < 1) {
        throw OutOfAmmo();
    }
    ammo--;
    GridPoint point(0, 0);
    const int min_col = std::max(0, d_place.col - SPLASH_ZONE);
    const int max_col = std::min(board.width() - 1, d_place.col + SPLASH_ZONE);
    for (point.col = min_col; point.col <= max_col; point.col++) {
        const int row_splash = SPLASH_ZONE - std::abs(point.col - d_place.col);
        const int min_row = std::max(0, d_place.row - row_splash);
        const int max_row =
            std::min(board.height() - 1, d_place.row + row_splash);
        for (point.row = min_row; point.col < max_row; point.col++) {
            if (board.get(point) != nullptr &&
                board.get(point)->getTeam() != team) {
                shoot(board, point);
            }
        }
    }

    if (board.get(d_place) != nullptr &&
        board.get(d_place)->getTeam() != team) {
        shoot(board, d_place);
    }
}

std::shared_ptr<Character> Soldier::clone() const {
    return std::shared_ptr<Character>(
        new Soldier(health, power, team, range, ammo));
}
}  // namespace mtm