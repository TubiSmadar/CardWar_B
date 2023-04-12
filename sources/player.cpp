#include <stdexcept>
#include "player.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

    // copy constructor
    player::player(const player &other)
            : name(other.name), cards_stack(other.cards_stack), stats(other.stats), cards_taken(other.cards_taken)
    {
    }

// Move assignment operator
    player &player::operator=(player &&other) noexcept
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
    player::player(player &&other) noexcept
        : name(other.name), cards_stack(other.cards_stack), stats(other.stats), cards_taken(other.cards_taken)
        {}

// second constructor- deep copy constructor:
    player &player::operator=(const player &other)
    {
        if (this != &other)
        {
            name = other.name;
            cards_stack = other.cards_stack;
            stats = other.stats;
        }
        cout << "Player " << name << " was created!" << endl;
        return *this;
    }
// third constructor - by name
    player::player(string name)
    {
        if (name.empty())
        {
            throw invalid_argument("Player name cannot be empty!");
        }

        this->name = name;
        this->cards_stack = vector<card>();
        this->stats = PlayerStats();
        this->cards_taken = vector<card>();
        cout << "Player " << name << " is created!" << endl;
    }

// destructor - delete the player when the game is over
    player::~player()
    {}

// add cards to the player's cards_stack
    void player::addTakenCard(const card &card)
        {
            cards_taken.push_back(card);
        }
    void player::addCard(const card &card)
        {
            this->cards_stack.push_back(card);
            cards_num++;
        }

// return the card at the top of the player's stack
    card player::playCard()
        {
        // call check winner function
            if (cards_stack.empty())
                {
                    // Game over
                    throw invalid_argument("Player " + name + " has no more cards!");
                }
            card card = cards_stack.front();        // get the card from the top of the stack
            cards_stack.erase(cards_stack.begin()); // remove the card from the stack
            return card;
        }

// return the number of cards that the player has left
int player::cardsLeft() const
{
    return cards_stack.size();
}

string player::getName() const
{
    return this->name;
}

// counting the turns that the player won and play
void player::addTurnWon()
{
    this->stats.turnsPlayed++;
    this->stats.turnsWon++;
}

// counting the turns that the player lost and play
void player::addTurnLost()
{
    this->stats.turnsPlayed++;
    this->stats.turnsLost++;
}

// counting the turns that the player draw and play
void player::addTurnDraw()
{
    this->stats.turnsPlayed++;
    this->stats.turnsDraw++;
}

// return the player's information
string player::getStats() const
{

    string statsStr = "Player " + name + " stats:\n";
    statsStr += "Cards left: " + to_string(stats.cardsLeft) + "\n";
    statsStr += "Turns played: " + to_string(stats.turnsPlayed) + "\n";
    statsStr += "Turns won: " + to_string(stats.turnsWon) + "\n";
    statsStr += "Turns lost: " + to_string(stats.turnsLost) + "\n";
    statsStr += "Turns draw: " + to_string(stats.turnsDraw) + "\n";
    return statsStr;
}

// return the number of cards that the player has left
int player::stacksize() const
{
    int size = cards_stack.size();
    return size;
}

// return the number of turns that the player won
int player::getTurnsWon() const
{
    return stats.turnsWon;
}

// return the number of turns that the player lost
int player::getTurnsLost() const
{
    return stats.turnsLost;
}

// return the number of turns that ended in a draw
int player::getTurnsDraw() const
{
    return stats.turnsDraw;
}

// return the amount of cards this player has won.
int player::cardesTaken() const
{
    return this->cards_taken.size();
}

void player::printCardsStack() const
{
    if (cards_stack.empty())
    {
        cout << "Player " << name << " has no more cards!" << endl;
        return;
    }
    cout << "Player " << name << " cards stack:" << endl;
    for (std::vector<card>::size_type i = 0; i < cards_stack.size(); i++)
    {
        cout << cards_stack[i].toString() << endl;
    }
}

