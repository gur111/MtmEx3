#ifndef MTMEX3_GAME_H
#define MTMEX3_GAME_H
#include <memory>

#include "Auxiliaries.h"
#include "Character.h"
#include "GameBoard.h"
#include "Exceptions.h"

namespace mtm {
class Game {
    GameBoard<Character>& board;

   private:
    std::shared_ptr<Character> getCharacter(const GridPoint& point);
    // Yes, it returns a reference to heap
    GameBoard<Character>& cloneBoard() const;
    static void copyBoardToBoard(GameBoard<Character>& dest_board,
                                 GameBoard<Character>& src_board);
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
                      std::shared_ptr<Character> character);
    void move(const GridPoint& src_coordinates,
              const GridPoint& dst_coordinates);
    void attack(const GridPoint& src_coordinates,
                const GridPoint& dst_coordinates);
    void reload(const GridPoint& coordinates);
    bool isOver(Team* winningTeam = NULL) const;

    // Functions (Static Methods)
    static std::shared_ptr<Character> makeCharacter(CharacterType type,
                                                    Team team, units_t health,
                                                    units_t ammo, units_t range,
                                                    units_t power);
};

std::ostream& operator<<(std::ostream& os, const Game& game);

}  // namespace mtm

#endif  // MTMEX3_GAME_H