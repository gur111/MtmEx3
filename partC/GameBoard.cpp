
#include "GameBoard.h"

namespace mtm {

const int &GameBoard::height() const { return height_; }
const int &GameBoard::width() const { return width_; }

std::shared_ptr<Character> &GameBoard::getCell(GridPoint point) {
    if (point.row >= height() || point.col >= width()) {
        throw IllegalCell();
    }
    return board[point.row][point.col];
}

void GameBoard::set(GridPoint point, std::shared_ptr<Character> character) {
    getCell(point) = character;
}

std::shared_ptr<Character> GameBoard::get(GridPoint point) {
    return getCell(point);
}

// const std::shared_ptr<Character> GameBoard::get(GridPoint point) const{
//     return getCell(point);
// }

};  // namespace mtm