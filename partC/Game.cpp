#include "Game.h"

#include <iostream>

namespace mtm {

Game::Game(int height, int width)
    : board(new GameBoard(Dimensions(height, width))) {}

Game::Game(const Game& game)
    : board(new GameBoard(
          Dimensions(game.board->height(), game.board->width()))) {
    for (int i; i < game.board->height(); i++) {
        for (int j; j < game.board->width(); j++) {
            GridPoint point(i, j);
            board->set(point, game.board->get(point)->clone());
        }
    }
}

Game::~Game() { delete board; }

std::ostream& operator<<(std::ostream& os, const Game& game) {
    return printGameBoard(os, game.begin(), game.end(), game.width());
    // TODO: Print health and stuff
}

std::shared_ptr<Character> Game::getCharacter(const GridPoint& point) {
    std::shared_ptr<Character> character = board->get(point);
    if (character == nullptr) {
        throw CellEmpty();
    }
    return character;
}

void Game::attack(const GridPoint& src_coordinates,
                  const GridPoint& dst_coordinates) {
    std::shared_ptr<Character> character = getCharacter(src_coordinates);
    character->attack(src_coordinates, dst_coordinates);
}

void Game::move(const GridPoint& src_coordinates,
                const GridPoint& dst_coordinates) {
    std::shared_ptr<Character> character = getCharacter(src_coordinates);

    character->move(src_coordinates, dst_coordinates);
}

void Game::reload(const GridPoint& coordinate) {
    std::shared_ptr<Character> character = getCharacter(coordinate);
    character->reload(coordinate);
}

bool isOver(Team* winningTeam = NULL) const {
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

};  // namespace mtm