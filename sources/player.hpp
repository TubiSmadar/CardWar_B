
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

    class player
    {
    private:
        std::vector<card> cards_stack;
        std::vector<card> cards_taken;
        PlayerStats stats;
        std::string name;
        int cards_num = 0;


    public:
        // default constructor
        player() = default;
        player(const player &other);
        player &operator=(const player &other);
        player(std::string name);
        void addCard(const card &card);
        void addTakenCard(const card &card);
        card playCard();
        int cardsLeft() const; // return the number of cards in the player's deck
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
        ~player();

        //Move constructor
        player(player &&other) noexcept;

        //Move assignment operator
        player &operator=(player &&other) noexcept;
    };
}

#endif
