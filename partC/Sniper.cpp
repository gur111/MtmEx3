#include "Sniper.h"

#include <memory>
#include <string>

#include "Character.h"
#include "Exceptions.h"
#define ADD_AMMO 2
#define TIMES_FOR_BOOST 3
#define INCREASE_RATE 2
#define MINIMUM_RANGE 2
#define DEFAULT_SNIPER_SPEED 4
using mtm::Sniper;

Sniper::Sniper(units_t health, units_t power, Team team, units_t range,
               units_t ammo, int s_counter)
    : Character(health, power, team, range, ammo, SNIPER,
                DEFAULT_SNIPER_SPEED) {
    counter = s_counter;
}

void Sniper::reload() { ammo += ADD_AMMO; }

void Sniper::shoot(mtm::GameBoard<Character>& board,
                   const mtm::GridPoint& s_place,
                   const mtm::GridPoint& d_place) {
    if (++counter == TIMES_FOR_BOOST) {
        board(d_place.row, d_place.col)->changeHealth(-(INCREASE_RATE * power));
    } else {
        board(d_place.row, d_place.col)->changeHealth(-power);
    }
    if (board(d_place.row, d_place.col)->getHealth() <= 0) {
        board(d_place.row, d_place.col) = nullptr;
    }
    ammo--;
    counter %= TIMES_FOR_BOOST;
}

void Sniper::attack(GameBoard<Character>& board, const mtm::GridPoint& s_place,
                    const mtm::GridPoint& d_place) {
    if (not board.isWithinLimits(d_place)) {
        throw IllegalCell();
    }
    if (GridPoint::distance(s_place, d_place) > range ||
        GridPoint::distance(s_place, d_place) < ((range + 1) / MINIMUM_RANGE)) {
        throw OutOfRange();
    }
    if (ammo <= 0) {
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
