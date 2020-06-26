#include "Sniper.h"

#include <memory>
#include <string>

#include "Character.h"
#include "GameException.h"

using mtm::Sniper;

Sniper::Sniper(units_t health, units_t power, Team team, units_t range,
               units_t ammo, int s_counter)
    : Character(health, power, team, range, ammo, SNIPER) {
    counter = s_counter;
    type = SNIPER;
}

void Sniper::move(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                  const mtm::GridPoint& d_place) {
    if (GridPoint::distance(s_place, d_place) > 4) {
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

void Sniper::reload() { ammo += 2; }

void Sniper::shoot(mtm::GameBoard<Character>& board,
                   const mtm::GridPoint& s_place,
                   const mtm::GridPoint& d_place) {
    if (counter % 3 != 0) {
        board(d_place.row, d_place.col)->changeHealth(-power);
    } else {
        board(d_place.row, d_place.col)->changeHealth(-(2 * power));
    }
    if (board(d_place.row, d_place.col)->getHealth() <= 0) {
        board(d_place.row, d_place.col) = nullptr;
    }
    counter++;
}

void Sniper::attack(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                    const mtm::GridPoint& d_place) {
    if (not board.isWithinLimits(d_place)) {
        throw IllegalCell();
    }
    if (GridPoint::distance(s_place, d_place) > range ||
        GridPoint::distance(s_place, d_place) < ceil(range / 2)) {
        throw OutOfRange();
    }
    if (ammo < 1) {
        throw OutOfAmmo();
    }
    if (board(d_place.row, d_place.col) == nullptr ||
        board(d_place.row, d_place.col)->getTeam() == team) {
        throw IllegalTarget();
    }
    shoot(board, s_place, d_place);
}

std::shared_ptr<mtm::Character> mtm::Sniper::clone() const {
    return std::shared_ptr<Character>(
        new Sniper(health, power, team, range, ammo, counter));
}
