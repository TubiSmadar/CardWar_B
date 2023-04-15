#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <string>
using namespace std;

namespace ariel{
    class Card
    {
        private:
            int value;
            string symbol;
            
        public:
            //Constructors
            Card(int value, const string& symbol);
            Card();
            ~Card();
            
            //Operators
            bool operator==(const Card&) const;
            bool operator>(const Card&) const;

            //Methods
            string toString();
    };
    
} 

#endif
