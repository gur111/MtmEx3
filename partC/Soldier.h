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
    class Soldier : public Character {
    private:
        void shoot(GameBoard<Character>& board, const GridPoint& s_place, const GridPoint& d_place);
    public:
        Soldier(units_t health, units_t power, Team team, units_t range, units_t ammo);
        ~Soldier();
        void move(GameBoard<Character>& board, const GridPoint& s_place, const GridPoint& d_place) override;
        void attack(GameBoard<Character>& board, const GridPoint& s_place, const GridPoint& d_place) override;
        void reload() override;
        std::shared_ptr<Character> clone() const override;
    };
}
#endif //MTMEX3_SOLDIER_H
