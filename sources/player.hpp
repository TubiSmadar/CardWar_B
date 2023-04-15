#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string.h>
#include<vector>
#include "card.hpp"
using namespace std;

namespace ariel{
    class Player
    {
        private:
            const string name;
            int total_winning;
            int in_play;
            int cards_taken;
            vector<Card> hand;


        public:
            //Constructors:
            Player(string);
            Player();
        
            //Getters
            string getName() const;
            int stacksize() const;
            int cardesTaken() const;
            int getInPlay() const;
            int getTotalWinnings() const;
            
            //Setters
            void addToTotalWinnings();
            void setInPlay(int);
            void setCardsTaken(int);
        
            //Methods
            void withdrawCard(Card&);
            Card playCard();
        
            //Operator
            bool operator==(const Player& other) const;
    };
}

#endif
