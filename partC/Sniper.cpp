#include "Sniper.h"
#include "Character.h"
#include <string>
#include <memory>
#include "GameException.h"

using mtm::Sniper;

Sniper::Sniper(units_t health, units_t power, Team team, units_t range, units_t ammo, int s_counter) :
        Character(health, power, team, range, ammo) {
    counter = s_counter;
    type = SNIPER;
}

void Sniper::move(GameBoard<Character>& board, const mtm::GridPoint& s_place, const mtm::GridPoint& d_place) {
    if (GridPoint::distance(s_place, d_place) >= 4) {
        throw MoveTooFar();
    }
    if (board(d_place.row, d_place.col) != nullptr) {
        throw CellOccupied();
    }
    std::shared_ptr<Character> temp = board(s_place.row, s_place.col);
    board(d_place.row, d_place.col) = temp;
    board(s_place.row, s_place.col) = nullptr;
}

void Sniper::reload() {
    ammo += 2;
}

void Sniper::shoot(mtm::GameBoard<Character>& board, const mtm::GridPoint& s_place, const mtm::GridPoint& d_place) {
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

void Sniper::attack(GameBoard<Character>& board, const mtm::GridPoint& s_place, const mtm::GridPoint& d_place) {
    if (board(d_place.row, d_place.col) == nullptr) {
        throw IllegalTarget();
    }
    if (d_place.col > board.width() || d_place.row > board.height()) {
        throw IllegalCell();
    }
    if (ammo < 1) {
        throw OutOfAmmo();
    }
    if (GridPoint::distance(s_place, d_place) > range ||
        GridPoint::distance(s_place, d_place) < ceil(range / 2)) {
        throw OutOfRange();
    }
    if (board(d_place.row, d_place.col)->getTeam() == team) {
        throw IllegalTarget();
    }

}
