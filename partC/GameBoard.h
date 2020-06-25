
#ifndef MTMEX3_GAME_BOARD_H
#define MTMEX3_GAME_BOARD_H
#include <memory>
#include <vector>

#include "../Auxiliaries.h"
#include "Character.h"
#include "GameException.h"

namespace mtm {
class GameBoard {
    std::vector<std::vector<std::shared_ptr<Character>>> board;
    int width_, height_;

   private:
    std::shared_ptr<Character> &getCell(GridPoint point);

   public:
    const int &width() const;
    const int &height() const;
    void set(GridPoint point, std::shared_ptr<Character> character);
    std::shared_ptr<Character> get(GridPoint point);
    // const std::shared_ptr<Character> get(GridPoint point) const;
};
};  // namespace mtm

#endif
