#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include "player.hpp"
#include "card.hpp"
using namespace std;

namespace ariel{
    class Game
    {
        private:
            Player *player1;
            Player *player2;
            vector<Card> deck;
            vector<string> log;
            int draws;
            int  turns;
            void shuffleDeck();
            void dealCards();
            void generateGame();
            int play(string*, int*, int*);
            string setLogString(string, Card, string, Card, int);
        public:
            //Constructors
            Game(Player&, Player&);

            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();
    };
}

#endif
