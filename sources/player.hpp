
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "card.hpp"

namespace ariel
{
    //got help from Maya Rom in this struct part
    struct PlayerStats
    {
        // initializing the stats:
        int cardsLeft = 0;
        int turnsPlayed = 0;
        int turnsWon = 0;
        int turnsLost = 0;
        int turnsDraw = 0;
    };

    class Player
    {
    private:
        std::vector<Card> cards_stack;
        std::vector<Card> cards_taken;
        PlayerStats stats;
        std::string name;
        int cards_num = 0;


    public:
        // default constructor
        Player() = default;
        Player(const Player &other);
        Player &operator=(const Player &other);
        Player(std::string name);
        void addCard(const Card &card);
        void addTakenCard(const Card &card);
        Card playCard();
        int cardsLeft() const; // return the number of cards in the Player's deck
        std::string getName() const;
        void addTurnWon();
        void addTurnLost();
        void addTurnDraw();
        std::string getStats() const;
        int stacksize() const;
        int getTurnsWon() const;
        int getTurnsLost() const;
        int getTurnsDraw() const;
        int cardesTaken() const;
        //print cards_stack
        void printCardsStack() const;
        //destructor
        ~Player();

        //Move constructor
        Player(Player &&other) noexcept;

        //Move assignment operator
        Player &operator=(Player &&other) noexcept;
    };
}

#endif
