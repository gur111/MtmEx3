
#include "GameBoard.h"

namespace mtm {

GameBoard::GameBoard(Dimensions dims) {
    if (dims.getRow() <= 0 || dims.getCol() <= 0) {
        throw IllegalArgument();
    }
}

const int &GameBoard::height() const { return height_; }
const int &GameBoard::width() const { return width_; }

std::shared_ptr<Character> &GameBoard::getCell(const GridPoint point) {
    if (point.row >= height() || point.col >= width()) {
        throw IllegalCell();
    }
    return data[point.row][point.col];
}

void GameBoard::set(const GridPoint point, std::shared_ptr<Character> character) {
    getCell(point) = character;
}

std::shared_ptr<Character> GameBoard::get(const GridPoint point) {
    return getCell(point);
}

std::shared_ptr<Character> GameBoard::operator()(int i, int j) {
    return this->get(GridPoint(i, j));
}

// const std::shared_ptr<Character> GameBoard::get(GridPoint point) const{
//     return getCell(point);
// }

};  // namespace mtm