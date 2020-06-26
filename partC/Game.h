#ifndef MTMEX3_GAME_H
#define MTMEX3_GAME_H
#include <memory>

#include "../Auxiliaries.h"
#include "Character.h"
#include "GameBoard.h"
#include "GameException.h"

namespace mtm {
class Game {
    GameBoard<Character>& board;

   private:
    std::shared_ptr<Character> getCharacter(const GridPoint& point);
    friend std::ostream& operator<<(std::ostream& os, const Game& game);

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

};  // namespace mtm

#endif  // MTMEX3_GAME_H