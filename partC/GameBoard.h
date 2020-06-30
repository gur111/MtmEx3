
#ifndef MTMEX3_GAME_BOARD_H
#define MTMEX3_GAME_BOARD_H
#include <memory>
#include <vector>

#include "../Auxiliaries.h"
#include "../partB/Matrix.h"
#include "Exceptions.h"

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
    void reshape(const Dimensions dims);
    bool isWithinLimits(const GridPoint point) const;
    const int &width() const;
    const int &height() const;
    void set(const GridPoint point, std::shared_ptr<T> character);
    std::shared_ptr<T> &get(const GridPoint point);
    std::shared_ptr<T> &operator()(int i, int j);
    // const std::shared_ptr<Character> get(GridPoint point) const;
};

template <class T>
Dimensions GameBoard<T>::verifyDimensions(Dimensions dims) {
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
                                          nullptr)))),
      width_(dims.getRow()),
      height_(dims.getCol()) {}

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
    if (not isWithinLimits(point)) {
        throw IllegalCell();
    }
    return data[point.row][point.col];
}

template <class T>
void GameBoard<T>::set(const GridPoint point, std::shared_ptr<T> character) {
    getCell(point) = character;
}

template <class T>
std::shared_ptr<T> &GameBoard<T>::get(const GridPoint point) {
    return getCell(point);
}

template <class T>
std::shared_ptr<T> &GameBoard<T>::operator()(int i, int j) {
    return this->getCell(GridPoint(i, j));
}

template <class T>
bool GameBoard<T>::isWithinLimits(const GridPoint point) const {
    return point.col < width() && point.row < height() && point.row >= 0 &&
           point.col >= 0;
}

template <class T>

void GameBoard<T>::reshape(const Dimensions dims) {
    verifyDimensions(dims);
    data.resize(dims.getRow(),
                std::vector<std::shared_ptr<T>>(dims.getCol(), nullptr));

    for (int i = 0; i < std::min(dims.getRow(), height()); i++) {
        data[i].resize(dims.getCol(), nullptr);
    }

    height_ = dims.getRow();
    width_ = dims.getCol();
}

}  // namespace mtm

#endif
