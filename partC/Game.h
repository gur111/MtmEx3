#ifndef MTMEX3_GAME_H
#define MTMEX3_GAME_H
#include <memory>

#include "../Auxiliaries.h"
#include "Character.h"
#include "GameBoard.h"
#include "GameException.h"

namespace mtm {
class Game {
    GameBoard& board;

   private:
    std::shared_ptr<Character> getCharacter(const GridPoint& point);

   public:
    // Ctors and Dtor
    Game(int height, int width);
    Game(const Game& other);
    ~Game();

    // Operators
    Game& operator=(const Game& other);  // TODO

    // Methods
    void addCharacter(const GridPoint& coordinates,
                      std::shared_ptr<Character> character);  // TODO
    void move(const GridPoint& src_coordinates,
              const GridPoint& dst_coordinates);
    void attack(const GridPoint& src_coordinates,
                const GridPoint& dst_coordinates);
    void reload(const GridPoint& coordinates);
    bool isOver(Team* winningTeam = NULL) const;

    // Iterations
    class iterator;
    class const_iterator;
    iterator begin();              // TODO
    iterator end();                // TODO
    const_iterator begin() const;  // TODO
    const_iterator end() const;    // TODO

    // Functions (Static Methods)
    static std::shared_ptr<Character> makeCharacter(CharacterType type,
                                                    Team team, units_t health,
                                                    units_t ammo, units_t range,
                                                    units_t power);  // TODO
};

std::ostream& operator<<(std::ostream& os, const Game& game);  // TODO
class Game::iterator {
    int index;
    Game* game;
    iterator(Game* game, int index);

    friend class Game;

   public:
    std::shared_ptr<Character> operator*() const;
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& it) const;
    bool operator!=(const iterator& it) const;
    iterator(const iterator&) = default;
    iterator& operator=(const iterator&) = default;
};
class Game::const_iterator {
    int index;
    const Game* game;
    const_iterator(const Game* game, int index);

    friend class Game;

   public:
    std::shared_ptr<Character> operator*() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& it) const;
    bool operator!=(const const_iterator& it) const;
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;
};
};  // namespace mtm

#endif  // MTMEX3_GAME_H