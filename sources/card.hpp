//#ifndef CARD_HPP
//#define CARD_HPP
//#include <string>
//using namespace std;
//
//namespace ariel {
//    enum class Rank
//    {
//        ACE = 1,
//        TWO,
//        THREE,
//        FOUR,
//        FIVE,
//        SIX,
//        SEVEN,
//        EIGHT,
//        NINE,
//        TEN,
//        JACK,
//        QUEEN,
//        KING,
//        NO_RANK
//    };
//
//    enum class Suit
//    {
//        HEARTS,
//        SPADES,
//        DIAMONDS,
//        CLUBS
//    };
//
//    class card{
//        private:
//            Rank val;
//            Suit shape;
//
//        public:
//            card(int val, std::string shape);
//            void setVal(int val);
//            int getVal();
//            std::string getShape();
//            void setShape(std::string shape);
//            void showCard();
//    };
//}
//
//#endif
#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <string>

namespace ariel
{
    enum class Rank
    {
        ACE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        NO_RANK
    };

    enum class Suit
    {
        HEARTS,
        SPADES,
        DIAMONDS,
        CLUBS
    };

    class card
    {
    public:
        card();

        //Constructor
        card(Rank rank, Suit suit);
        card(const card &other) noexcept;
        card(card &&other) noexcept;
        card &operator=(const card &other) noexcept;
        card &operator=(card &&other) noexcept;

        //Destructor
        ~card();

        //Returns a string representation of the card
        std::string toString() const;

        //Compare method
        int compare(const card &other) const;

        //Getters
        Rank getRank() const { return rank; }
        Suit getSuit() const { return suit; }

        //Setters
        void setRank(Rank rank) { this->rank = rank; }
        void setSuit(Suit suit) { this->suit = suit; }

        static std::string suitToString(Suit suit);
        static std::string rankToString(Rank rank);

    private:
        Rank rank;
        Suit suit;
    };
}

#endif
