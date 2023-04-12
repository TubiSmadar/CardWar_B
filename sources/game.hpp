#ifndef GAME_HPP
#define GAME_HPP

#include "card.hpp"
#include "player.hpp"
#include <vector>
#include <string>
#include <array>

namespace ariel
{
    class game
    {
    private:
        std::vector<card> board_stack;
        std::array<player *, 2> players;
        player &player1;
        player &player2;
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
        game(player &first_player, player &second_player);
        game();
        game(game &&other) noexcept;
        game(const game &other);

        // destructor
        ~game();

        // assignment operators
        game &operator=(const game &other);
        game &operator=(game &&other) noexcept;

        //  methods:
        void playTurn();
        void playAll();
        void printLastTurn();
        void printWiner();
        void printLog();
        void printStats();
        int getRoundsPlayed() const;
        std::string getLog();
        const player &getWinner() const;
    };
}

#endif
