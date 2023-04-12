//#ifndef GAME_H
//#define GAME_H
//
//#include <string>
//#include "Player.hpp"
//#include "Card.hpp"
//using namespace std;
//
//namespace ariel {
//class Game
//{
//    private:
//        Player& p1;
//        Player& p2;
//
//    public:
//        Game(Player& p1, Player& p2);
//        ~Game();
//
//        void playTurn();
//        void printLastTurn();
//        void playAll();
//        void printWiner();
//        void printLog();
//        void printStats();
//};
//}
//#endif
#ifndef GAME_HPP
#define GAME_HPP

#include "card.hpp"
#include "player.hpp"
#include <vector>
#include <string>
#include <array>

namespace ariel
{
    class Game
    {
    private:
        std::vector<Card> board_stack;
        std::array<Player *, 2> players;
        Player &player1;
        Player &player2;
        std::string mainLog;
        std::string lastTurn;

        int winner;
        int roundsPlayed;
        void fillCards();
        void shuffleDeck();
        void splitCards();
        void checkWin();
        void tie_war();

    public:
        // constructors:
        Game(Player &first_player, Player &second_player);
        Game();
        Game(Game &&other) noexcept;
        Game(const Game &other);

        // destructor
        ~Game();

        // assignment operators - copy and move
        Game &operator=(const Game &other);
        Game &operator=(Game &&other) noexcept;

        //  methods:
        void playTurn();
        void playAll();
        void printLastTurn();
        void printWiner();
        void printLog();
        void printStats();
        int getRoundsPlayed() const;
        std::string getLog();
        const Player &getWinner() const;
    };
}

#endif // GAME_HPP
