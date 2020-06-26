#ifndef MTMEX3_SOLDIER_H
#define MTMEX3_SOLDIER_H

#include <assert.h>
#include "Character.h"
#include "../Auxiliaries.h"
#include "GameBoard.h"
#include <functional>
#include <iostream>
#include <string>

namespace mtm {
    class Sniper : public Character {
    private:
        void shoot(GameBoard& board, const GridPoint& s_place, const GridPoint& d_place;
        int counter;
    public:
        Sniper(units_t health, units_t power, Team team, units_t range, units_t ammo, int counter);
        ~Sniper();
        void move(GameBoard& board, const GridPoint& s_place, const GridPoint& d_place) override;
        void attack(GameBoard& board, const GridPoint& s_place, const GridPoint& d_place) override;
        void reload(GameBoard& board, const GridPoint& s_place) override;
    };
}
#endif //MTMEX3_SOLDIER_H
