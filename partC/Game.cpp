#include "Game.h"

#include <iostream>

namespace mtm {

Game::Game(int height, int width)
    : board(*(new GameBoard<Character>(Dimensions(height, width)))) {}

Game::Game(const Game& game)
    : board(*(new GameBoard<Character>(
          Dimensions(game.board.height(), game.board.width())))) {
    for (int i; i < game.board.height(); i++) {
        for (int j; j < game.board.width(); j++) {
            GridPoint point(i, j);
            board.set(point, game.board.get(point)->clone());
        }
    }
}

Game::~Game() { delete &board; }

std::ostream& operator<<(std::ostream& os, const Game& game) {
    std::string str(game.board.height() * game.board.width(), ' ');
    for (int i; i < game.board.height(); i++) {
        for (int j; j < game.board.width(); j++) {
            switch (game.board(i, j)->getType()) {
                case SOLDIER:
                    str += "S";
                    break;
                case MEDIC:
                    str += "M";
                    break;
                case SNIPER:
                    str += "N";
                    break;
                default:
                    str += " ";
            }
        }
    }
    return printGameBoard(os, &str[0], &str[str.length() - 1],
                          game.board.width());
    // TODO: Print health and 8stuff
}

std::shared_ptr<Character> Game::getCharacter(const GridPoint& point) {
    std::shared_ptr<Character> character = board.get(point);
    if (character == nullptr) {
        throw CellEmpty();
    }
    return character;
}

void Game::attack(const GridPoint& src_coordinates,
                  const GridPoint& dst_coordinates) {
    std::shared_ptr<Character> character = getCharacter(src_coordinates);
    character->attack(board, src_coordinates, dst_coordinates);
}

void Game::move(const GridPoint& src_coordinates,
                const GridPoint& dst_coordinates) {
    std::shared_ptr<Character> character = getCharacter(src_coordinates);

    character->move(board, src_coordinates, dst_coordinates);
}

void Game::reload(const GridPoint& coordinate) {
    std::shared_ptr<Character> character = getCharacter(coordinate);
    character->reload();
}

bool Game::isOver(Team* winningTeam) const {
    // Pun intended
    bool isPythonDead = true, isCppDead = true;

    for (std::shared_ptr<Character> character : *this) {
        if (character != nullptr) {
            isCppDead = isCppDead && character->getTeam() != CPP;
            isPythonDead = isPythonDead && character->getTeam() != PYTHON;
        }
    }
    assert(!isPythonDead || !isCppDead);
    if (winningTeam) {
        if (isPythonDead) {
            *winningTeam = CPP;
        }
        if (isCppDead) {
            *winningTeam = PYTHON;
        }
    }
    return isPythonDead || isCppDead;
}

// ITERATORS

// // Constructors
// Game::const_iterator::const_iterator(const Game* game, int index)
//     : index(index), game(game) {}
// Game::iterator::iterator(Game* game, int index) : index(index), game(game) {}

// // Begin/end
// Game::iterator Game::begin() { return Game::iterator(this, 0); }
// Game::iterator Game::end() {
//     return Game::iterator(this, board.height() * board.width());
// }

// Game::const_iterator Game::begin() const {
//     return Game::const_iterator(this, 0);
// }
// Game::const_iterator Game::end() const {
//     return Game::const_iterator(this, board.height() * board.width());
// }

// // Comparisons
// bool Game::iterator::operator==(const Game::iterator& it) const {
//     assert(game == it.game);
//     return it.index == this->index;
// }

// bool Game::const_iterator::operator==(const Game::const_iterator& it) const {
//     assert(game == it.game);
//     return it.index == this->index;
// }

// bool Game::iterator::operator!=(const Game::iterator& it) const {
//     return not(*this == it);
// }
// bool Game::const_iterator::operator!=(const Game::const_iterator& it) const {
//     return not(*this == it);
// }

// // Operator *
// std::shared_ptr<Character> Game::iterator::operator*() const {
//     if (index >= game->board.width() * game->board.height()) {
//         throw IllegalCell();
//     }
//     int x = index / game->board.width(), y = index % game->board.width();
//     GameBoard board = game->board;
//     return board(3, 1);
// }

};  // namespace mtm