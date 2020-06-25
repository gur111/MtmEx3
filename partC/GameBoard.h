
#ifndef MTMEX3_GAME_BOARD_H
#define MTMEX3_GAME_BOARD_H
#include <memory>
#include <vector>

#include "../Auxiliaries.h"
#include "Character.h"
#include "GameException.h"

namespace mtm {
class GameBoard {
    std::vector<std::vector<std::shared_ptr<Character>>> data;
    int width_, height_;

   private:
    std::shared_ptr<Character> &getCell(const GridPoint point);

   public:
    GameBoard(Dimensions dims);
    const int &width() const;
    const int &height() const;
    void set(const GridPoint point, std::shared_ptr<Character> character);
    std::shared_ptr<Character> get(const GridPoint point);
    std::shared_ptr<Character> operator()(int i, int j);
    // const std::shared_ptr<Character> get(GridPoint point) const;
};
};  // namespace mtm

#endif
