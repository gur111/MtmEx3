
#ifndef MTMEX3_GAME_BOARD_H
#define MTMEX3_GAME_BOARD_H
#include <memory>
#include <vector>

#include "../Auxiliaries.h"
#include "../partB/Matrix.h"
#include "GameException.h"

namespace mtm {

template <class T>
class GameBoard {
    std::vector<std::vector<std::shared_ptr<T>>> &data;
    int width_, height_;

   private:
    static Dimensions verifyDimensions(Dimensions dims);
     std::shared_ptr<T> &getCell(const GridPoint point);

   public:
    GameBoard(Dimensions dims);
    ~GameBoard();
    bool isWithinLimits(const GridPoint point) const;
    const int &width() const;
    const int &height() const;
    void set(const GridPoint point, std::shared_ptr<T> character);
    std::shared_ptr<T> get(const GridPoint point);
    std::shared_ptr<T> operator()(int i, int j);
    // const std::shared_ptr<Character> get(GridPoint point) const;
};
};  // namespace mtm

#endif
