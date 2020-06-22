#ifndef MTMEX3_GAME_H
#define MTMEX3_GAME_H
#include <memory>

#include "../Auxiliaries.h"
#include "Character.h"

namespace mtm {
class Game {
   public:
    // Ctors and Dtor
    Game(int height, int width);
    Game(const Game& other);
    ~Game();

    // Operators
    Game& operator=(const Game& other);

    // Methods
    void addCharacter(const GridPoint& coordinates,
                      std::shared_ptr<Character> character);
    void move(const GridPoint& src_coordinates,
              const GridPoint& dst_coordinates);
    void attack(const GridPoint& src_coordinates,
                const GridPoint& dst_coordinates);
    void reload(const GridPoint& coordinates);
    bool isOver(Team* winningTeam = NULL) const;

    // Iterations
    class iterator;
    class const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // Functions (Static Methods)
    static std::shared_ptr<Character> makeCharacter(CharacterType type,
                                                    Team team, units_t health,
                                                    units_t ammo, units_t range,
                                                    units_t power);

    // Exceptions
    class IllegalArgument;
    class IllegalCell;
    class CellEmpty;
    class MoveTooFar;
    class CellOccupied;
    class OutOfRange;
    class OutOfAmmo;
    class IllegalTarget;
};
};  // namespace mtm

#endif  // MTMEX3_GAME_H