#include <stdexcept>
#include "Player.hpp"
#include "Card.hpp"

using namespace std;
using namespace ariel;

    // copy constructor
    Player::Player(const Player &other)
            : name(other.name), cards_stack(other.cards_stack), stats(other.stats), cards_taken(other.cards_taken)
    {
    }

// Move assignment operator
Player &Player::operator=(Player &&other) noexcept
        {
            if (this != &other)
                {
                    name = other.name;
                    cards_stack = other.cards_stack;
                    stats = other.stats;
                    cards_taken = other.cards_taken;
                }
            return *this;
        }
// Move constructor
Player::Player(Player &&other) noexcept
        : name(other.name), cards_stack(other.cards_stack), stats(other.stats), cards_taken(other.cards_taken)
        {}

// second constructor- deep copy constructor:
Player &Player::operator=(const Player &other)
    {
        if (this != &other)
        {
            name = other.name;
            cards_stack = other.cards_stack;
            stats = other.stats;
        }
        cout << "Player " << name << " is created!" << endl;
        return *this;
    }

    Player::Player(string name)
    {
        if (name.empty())
        {
            throw invalid_argument("Player name cannot be empty!");
        }

        this->name = name;
        this->cards_stack = vector<Card>();
        this->stats = PlayerStats();
        this->cards_taken = vector<Card>();
        cout << "Player " << name << " is created!" << endl;
    }

// destructor - delete the player when the game is over
Player::~Player()
    {}

// add cards to the player's cards_stack
    void Player::addTakenCard(const Card &card)
        {
            cards_taken.push_back(card);
        }
    void Player::addCard(const Card &card)
        {
            this->cards_stack.push_back(card);
            cards_num++;
        }

// return the card at the top of the player's stack
Card Player::playCard()
        {
        // call check winner function
            if (cards_stack.empty())
                {
                    // Game over
                    throw invalid_argument("Player " + name + " has no more cards!");
                }
            Card card = cards_stack.front();        // get the card from the top of the stack
            cards_stack.erase(cards_stack.begin()); // remove the card from the stack
            return card;
        }

// return the number of cards that the player has left
int Player::cardsLeft() const
{
    return cards_stack.size();
}

string Player::getName() const
{
    return this->name;
}

// Counter for winner turn
void Player::addTurnWon()
{
    this->stats.turnsPlayed++;
    this->stats.turnsWon++;
}

// Counter for loser turn
void Player::addTurnLost()
{
    this->stats.turnsPlayed++;
    this->stats.turnsLost++;
}

// Counter for draw turn
void Player::addTurnDraw()
{
    this->stats.turnsPlayed++;
    this->stats.turnsDraw++;
}

// return the player's info
string Player::getStats() const
{

    string statsStr = "Player " + name + " stats:\n";
    statsStr += "Cards left: " + to_string(stats.cardsLeft) + "\n";
    statsStr += "Turns played: " + to_string(stats.turnsPlayed) + "\n";
    statsStr += "Turns won: " + to_string(stats.turnsWon) + "\n";
    statsStr += "Turns lost: " + to_string(stats.turnsLost) + "\n";
    statsStr += "Draw turns: " + to_string(stats.turnsDraw) + "\n";
    return statsStr;
}

// return the number of cards that the player has left
int Player::stacksize() const
{
    int size = cards_stack.size();
    return size;
}

// Winner counter getter
int Player::getTurnsWon() const
{
    return stats.turnsWon;
}

// Loser counter getter
int Player::getTurnsLost() const
{
    return stats.turnsLost;
}

// Draw counter getter
int Player::getTurnsDraw() const
{
    return stats.turnsDraw;
}

// Cards taken getter
int Player::cardesTaken() const
{
    return this->cards_taken.size();
}

void Player::printCardsStack() const
{
    if (cards_stack.empty())
    {
        cout << "Player " << name << " has no more cards!" << endl;
        return;
    }
    cout << "Player " << name << " cards stack:" << endl;
    for (std::vector<Card>::size_type i = 0; i < cards_stack.size(); i++)
    {
        cout << cards_stack[i].toString() << endl;
    }
}

