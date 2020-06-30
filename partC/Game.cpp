#include "Game.h"

#include <iostream>

#include "Medic.h"
#include "Sniper.h"
#include "Soldier.h"

namespace mtm {

Game::Game(int height, int width)
    : board(*(new GameBoard<Character>(Dimensions(height, width)))) {}

Game::Game(const Game& game) : board(game.cloneBoard()) {}

void Game::copyBoardToBoard(GameBoard<Character>& dest_board,
                            GameBoard<Character>& src_board) {
    assert(dest_board.width() == src_board.width() &&
           dest_board.height() == src_board.height());
    for (int i = 0; i < dest_board.height(); i++) {
        for (int j = 0; j < dest_board.width(); j++) {
            std::shared_ptr<Character> src_char = src_board(i, j);
            dest_board(i, j) =
                src_char == nullptr ? nullptr : src_char->clone();
        }
    }
}

GameBoard<Character>& Game::cloneBoard() const {
    GameBoard<Character>& cloned =
        *(new GameBoard<Character>(Dimensions(board.height(), board.width())));
    copyBoardToBoard(cloned, board);

    return cloned;
}

Game& Game::operator=(const Game& other) {
    this->board.reshape(Dimensions(other.board.height(), other.board.width()));

    copyBoardToBoard(board, other.board);

    return *this;
}

Game::~Game() { delete &board; }

std::ostream& operator<<(std::ostream& os, const Game& game) {
    std::string str = "";
    for (int i = 0; i < game.board.height(); i++) {
        for (int j = 0; j < game.board.width(); j++) {
            std::shared_ptr<Character> character = game.board(i, j);
            if (character == nullptr) {
                str += " ";
                continue;
            }
            switch (character->getType()) {
                case SOLDIER:
                    str += character->getTeam() == CPP ? "S" : "s";
                    break;
                case MEDIC:
                    str += character->getTeam() == CPP ? "M" : "m";
                    break;
                case SNIPER:
                    str += character->getTeam() == CPP ? "N" : "n";
                    break;
                default:
                    assert(false);
            }
        }
    }
    return printGameBoard(os, &str[0], &str[0] + str.length(),
                          game.board.width());
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
    // So it would first throw an error on the IllegalCell even though it makes
    // no sense to force order between CellEmpty and IllegalCell. Since we first
    // of all want to get the Character. CellEmpty (on src) logically should be
    // thrown before IllegalCell (on dst) since it makes sense in this structure
    // and make sense in general to verify the soruce and only then the dst.
    // Anyways, here is the ugly workaround.
    board.get(dst_coordinates);
    std::shared_ptr<Character> character = getCharacter(src_coordinates);
    character->attack(board, src_coordinates, dst_coordinates);
}

void Game::move(const GridPoint& src_coordinates,
                const GridPoint& dst_coordinates) {
    board.get(dst_coordinates);
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
    std::shared_ptr<Character> character;

    for (int i = 0; i < board.height(); i++) {
        for (int j = 0; j < board.width(); j++) {
            character = board(i, j);
            if (character != nullptr) {
                isCppDead = isCppDead && character->getTeam() != CPP;
                isPythonDead = isPythonDead && character->getTeam() != PYTHON;
            }
        }
    }

    if (isPythonDead == isCppDead) {
        isPythonDead = isCppDead = false;
    }

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

void Game::addCharacter(const GridPoint& coordinates,
                        std::shared_ptr<Character> character) {
    if (character == nullptr) {
        throw IllegalArgument();
    }
    if (board.get(coordinates) != nullptr) {
        throw CellOccupied();
    }

    board.set(coordinates, character);
}

std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                                               units_t health, units_t ammo,
                                               units_t range, units_t power) {
    switch (type) {
        case SOLDIER:
            return std::shared_ptr<Character>(
                new Soldier(health, power, team, range, ammo));
        case MEDIC:
            return std::shared_ptr<Character>(
                new Medic(health, power, team, range, ammo));
        case SNIPER:
            return std::shared_ptr<Character>(
                new Sniper(health, power, team, range, ammo));
        default:
            throw IllegalArgument();
    }
}

};  // namespace mtm