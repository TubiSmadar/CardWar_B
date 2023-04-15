#include "card.hpp"
#include <random>

using namespace std;

namespace ariel{

    bool Card::operator==(const Card& other) const{
        return (this->value == other.value );
    }

    bool Card::operator>(const Card& other) const{
    if (this->value == 1) {
        return (other.value != 1 && other.value != 2);
    } else if (this->value == 2) {
        return true;
    } else {
        return (this->value > other.value && other.value != 1);
    }
    }

    string Card::toString(){
        switch (this->value){
        case 2:
            return to_string(this->value) + " of " + this->symbol;
                
        case 3:
            return to_string(this->value) + " of " + this->symbol;

        case 4:
            return to_string(this->value) + " of " + this->symbol;

        case 5:
            return to_string(this->value) + " of " + this->symbol;

        case 6 :
            return to_string(this->value) + " of " + this->symbol;

        case 7: 
            return to_string(this->value) + " of " + this->symbol;

        case 8: 
            return to_string(this->value) + " of " + this->symbol;

        case 9: 
            return to_string(this->value) + " of " + this->symbol;

        case 10:
            return to_string(this->value) + " of " + this->symbol;
        
        case 11:
            return "Jack of " + this->symbol;

        case 12:
            return "Queen of " + this->symbol;
        
        case 13:
            return "King of " + this->symbol;
        
        case 1:
            return "Ace of " + this->symbol;
        }

        return "";
    }

    Card::Card(int value, const string& symbol) : 
    value(value), symbol(symbol){}

    Card::Card() : value(6), symbol("Clubs"){}
    
    Card::~Card() {}
}
