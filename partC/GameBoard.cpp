
#include "GameBoard.h"

namespace mtm {

static Dimensions verifyDimensions(Dimensions dims) {
    if (dims.getRow() <= 0 || dims.getCol() <= 0) {
        throw IllegalArgument();
    }
    return dims;
}

template <class T>
GameBoard<T>::GameBoard(Dimensions dims)
    : data(*(new std::vector<std::vector<std::shared_ptr<T>>>(
          verifyDimensions(dims).getRow(),
          std::vector<std::shared_ptr<T>>(verifyDimensions(dims).getCol(),
                                          nullptr)))) {}

template <class T>
GameBoard<T>::~GameBoard() {
    delete &data;
}

template <class T>
const int &GameBoard<T>::height() const {
    return height_;
}

template <class T>
const int &GameBoard<T>::width() const {
    return width_;
}

template <class T>
std::shared_ptr<T> &GameBoard<T>::getCell(const GridPoint point) {
    if (point.row >= height() || point.col >= width()) {
        throw IllegalCell();
    }
    return data[point.row][point.col];
}

template <class T>
void GameBoard<T>::set(const GridPoint point, std::shared_ptr<T> character) {
    getCell(point) = character;
}

template <class T>
std::shared_ptr<T> GameBoard<T>::get(const GridPoint point) {
    return getCell(point);
}

template <class T>
std::shared_ptr<T> GameBoard<T>::operator()(int i, int j) {
    return this->get(GridPoint(i, j));
}

template <class T>
bool GameBoard<T>::isWithinLimits(const GridPoint point) const {
    return point.col > width() || point.row > height() || point.row < 0 ||
           point.col < 0;
}

// const std::shared_ptr<T> GameBoard::get(GridPoint point) const{
//     return getCell(point);
// }

};  // namespace mtm