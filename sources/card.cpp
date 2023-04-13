#include "card.hpp"
#include <sstream>

using namespace std;

namespace ariel
{

    Card::Card() : rank(Rank::NO_RANK), suit(Suit::HEARTS) {}

    Card::Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

    Card::Card(const Card &other) noexcept : rank(other.rank), suit(other.suit) {}

    Card::Card(Card &&other) noexcept : rank(other.rank), suit(other.suit) {}

    Card &Card::operator=(const Card &other) noexcept
            {
                if (this != &other)
                    {
                        rank = other.rank;
                        suit = other.suit;
                    }
                return *this;
            }



    Card &Card::operator=(Card &&other) noexcept
        {
            if (this != &other)
                {
                    rank = other.rank;
                    suit = other.suit;
                }
            return *this;
        }

    Card::~Card() {}


int Card::compare(const Card &other) const
{
    if (rank == Rank::ACE && other.rank != Rank::ACE)
    {
        return 1;
    }
    else if (rank != Rank::ACE && other.rank == Rank::ACE)
    {
        return -1;
    }
    else if (rank == Rank::TWO && other.rank != Rank::TWO)
    {
        return -1;
    }
    else if (rank != Rank::TWO && other.rank == Rank::TWO)
    {
        return 1;
    }
    else if (rank == other.rank)
    {
        return 0;
    }
    else if (rank > other.rank)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// Used GPT for this representation
    std::string Card::toString() const
{
    std::stringstream ss;
    std::string rank_str, suit_str;

    switch (rank)
    {
        case Rank::ACE:
            rank_str = "A";
            break;
        case Rank::TWO:
            rank_str = "2";
            break;
        case Rank::THREE:
            rank_str = "3";
            break;
        case Rank::FOUR:
            rank_str = "4";
            break;
        case Rank::FIVE:
            rank_str = "5";
            break;
        case Rank::SIX:
            rank_str = "6";
            break;
        case Rank::SEVEN:
            rank_str = "7";
            break;
        case Rank::EIGHT:
            rank_str = "8";
            break;
        case Rank::NINE:
            rank_str = "9";
            break;
        case Rank::TEN:
            rank_str = "10";
            break;
        case Rank::JACK:
            rank_str = "J";
            break;
        case Rank::QUEEN:
            rank_str = "Q";
            break;
        case Rank::KING:
            rank_str = "K";
            break;
        default:
            rank_str = "?";
            break;
    }

    switch (suit)
    {
        case Suit::SPADES:
            suit_str = "♠";
            break;
        case Suit::HEARTS:
            suit_str = "♥";
            break;
        case Suit::DIAMONDS:
            suit_str = "♦";
            break;
        case Suit::CLUBS:
            suit_str = "♣";
            break;
        default:
            suit_str = "?";
            break;
    }

    ss << rank_str << suit_str;
    return ss.str();
}
}
