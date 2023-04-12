#include "Card.hpp"
#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include "Game.hpp"
#include <iomanip>

using namespace std;

namespace ariel
{
    // constructors:
    //player c'tor
    Game::Game(Player &first_player, Player &second_player) : winner(-1), player1(first_player), player2(second_player)
    {

        this->roundsPlayed = 0;
        cout <<"preparing the game...\n"
             << endl;
        // fill the middle stack with cards
        for (int rank = 1; rank < 14; rank++)
        {
            for (int suit = 0; suit < 4; suit++)
            {
                Suit cardSuit = static_cast<Suit>(suit);
                Rank cardRank = static_cast<Rank>(rank);
                Card card(cardRank, cardSuit);
                board_stack.push_back(card);
            }
        }

        // shuffle
        cout << "Shuffling the cards...\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(std::begin(board_stack), std::end(board_stack), gen);
        cout << "Dealing the cards...\n";

        // split cards
        players[0] = &first_player;
        players[1] = &second_player;

        int i = 0;
        while (i < board_stack.size())
        {
            players[0]->addCard(board_stack[i]);
            players[1]->addCard(board_stack[i + 1]);
            i+=2;
        }
        // clear the middle stack
        board_stack.clear();
        cout << "--------------------  The game is ready  ------------------------\n";
    }

    //  default constructor
    Game::Game() : winner(-1), player1(*new Player("player1")), player2(*new Player("player2")) {}

    // move assignment operator (rvalue reference)
    Game &Game::operator=(Game &&other) noexcept
{
    if (this != &other)
    {
        board_stack = std::move(other.board_stack);
        players[0] = std::move(other.players[1]);
        players[1] = std::move(other.players[2]);
        mainLog = std::move(other.mainLog);
        lastTurn = std::move(other.lastTurn);
        winner = other.winner;
        roundsPlayed = other.roundsPlayed;
    }
    return *this;
}
// Move constructor
    Game::Game(Game &&other) noexcept
        : board_stack(std::move(other.board_stack)),
        players(std::move(other.players)),
        player1(other.player1),
        player2(other.player2),
        mainLog(std::move(other.mainLog)),
        lastTurn(std::move(other.lastTurn)),
        winner(other.winner),
        roundsPlayed(other.roundsPlayed) {}
// Copy constructor
    Game::Game(const Game &other)
        : board_stack(other.board_stack),
          player1(*other.players[0]),
          player2(*other.players[1]),
          mainLog(other.mainLog),
          lastTurn(other.lastTurn),
          winner(other.winner),
          roundsPlayed(other.roundsPlayed)
        {
            players = {&player1, &player2};
        }
// Copy assignment operator
    Game &Game::operator=(const Game &other)
    {
        if (this != &other)
        {
            board_stack = other.board_stack;
            player1 = *other.players[0];
            player2 = *other.players[1];
            mainLog = other.mainLog;
            lastTurn = other.lastTurn;
            winner = other.winner;
            roundsPlayed = other.roundsPlayed;
            players = {&player1, &player2};
        }
        return *this;
    }

// destructor:
    Game::~Game() {}

// creating the cards and filling the middle_stack
void Game::fillCards()
{
    for (int rank = 1; rank <= 13; rank++)
    {
        for (int suit = 0; suit < 4; suit++)
        {
            Card card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            board_stack.push_back(card);
        }
    }
}

// shuffling the cards:
void Game::shuffleDeck()
{

    random_device rd;
    mt19937 g(rd());
    shuffle(this->board_stack.begin(), this->board_stack.end(), g);
}

// splitting the cards between the players:
void Game::splitCards()
{
    for (unsigned int i = 0; i < 52; i++)
    {
        if (i % 2 == 0)
        {
            player1.addCard(board_stack[i]);
        }
        else
        {
            player2.addCard(board_stack[i]);
        }
    }
}
void Game::playAll()
{
    std::cout << "Each player has: " << player1.stacksize() << " cards" << std::endl;
    std::cout << "In the middle stack there are:  " << board_stack.size() << " cards" << std::endl;
    while (winner == -1 && roundsPlayed < 27)
    {

        playTurn();
        checkWin();
    }
    checkWin();
}

// playing a turn:
void Game::playTurn()
{

    // error
    if (player1.getName() == player2.getName())
    {
        throw std::invalid_argument("Players cannot have the same name!");
    }
    roundsPlayed++;

    // print the turn number
    std::cout << "Turn number: " << roundsPlayed << std::endl;
    std::cout << "\n";
    checkWin();

    // every player put in the board stack the card
    board_stack.push_back(player1.playCard());
    board_stack.push_back(player2.playCard());

    // print the cards
    std::cout << player1.getName() << " card:   " << board_stack[board_stack.size()-2].toString() << "\n" <<player2.getName() << " card: " << board_stack[board_stack.size()-1].toString() << std::endl;



    // select turn winner
    if (board_stack[board_stack.size() - 2].compare(board_stack[board_stack.size() - 1]) > 0) // player1 wins
    {
        player1.addTurnWon();
        player2.addTurnLost();
        mainLog += player1.getName() + " played " + board_stack[board_stack.size() - 1].toString() + "\n" + player2.getName() + " played " + board_stack[board_stack.size() - 2].toString() + " - " + player1.getName() + " won the turn" + "\n\n";

        // Display the winner of the turn
        std::cout << "Winner of the turn: " << player1.getName() << std::endl;

        // add the cards to the winner
        for (int i = 0; i < board_stack.size(); i++)
        {
            player1.addTakenCard(board_stack[i]);
        }

        checkWin();
        // clear the middle stack
        board_stack.clear();
        // go back to the beginning of the function
        return;
    }
    else if (board_stack[board_stack.size() - 2].compare(board_stack[board_stack.size() - 1]) < 0) // player1 wins // player2 wins
    {
        player2.addTurnWon();
        // print the winner of the turn
        // Display the winner of the turn
        mainLog += player1.getName() + " played: " + board_stack[board_stack.size() - 1].toString() + "\n" + player2.getName() + " played: " + board_stack[board_stack.size() - 1].toString() + "\n" + player2.getName() + " won the turn" + "\n\n";

        std::cout << "Winner of the turn: " << player2.getName() << std::endl;

        // add the cards to the winner
        for (int i = 0; i < board_stack.size(); i++)
        {
            player2.addTakenCard(board_stack[i]);
        }

        checkWin();
        // clear the middle stack
        board_stack.clear();
        // go back to the beginning of the function
        return;
    }
    // if the cards are equal - war
    {
        checkWin();
        // update the draw counter
        player1.addTurnDraw();
        player2.addTurnDraw();
        mainLog += player1.getName() + " played " + board_stack[board_stack.size() - 1].toString() + "\n" + player2.getName() + " played " + board_stack[board_stack.size() - 1].toString() + " - " + "WAR" + "\n\n";

        // tie_war();
        std::cout << "Tie!!!!!!\n";
        // declare the cards
        int tie_seq = 1;
        roundsPlayed++;

        while (roundsPlayed <= 26 && player1.stacksize() > 0 && player2.stacksize() > 0)
        {

            // print the turn number
            std::cout << "Turn number: " << roundsPlayed << std::endl;
            // print the tie sequence
            std::cout << "Tie sequence: " << tie_seq << std::endl;

            // every player put in the middle stack two cards

            for (int i = 0; i < 2; i++)
            {
                if (player1.stacksize() == 0 || player2.stacksize() == 0)
                {
                    while (board_stack.size() > 0)
                    {
                        player1.addTakenCard(board_stack[board_stack.size() - 1]);
                        board_stack.pop_back();
                        player2.addTakenCard(board_stack[board_stack.size() - 1]);
                        board_stack.pop_back();
                    }
                    break;
                }
                board_stack.push_back(player1.playCard());
                board_stack.push_back(player2.playCard());
            }


            // declare who wins the turn
            // if player1 wins
            if (board_stack[board_stack.size() - 2].compare(board_stack[board_stack.size() - 1]) > 0)
            {
                player1.addTurnWon();

                // Display the winner of the turn
                std::cout << "Winner of the turn: " << player1.getName() << std::endl;

                for (int i = 0; i < board_stack.size(); i++)
                {
                    player1.addTakenCard(board_stack[static_cast<std::vector<Card>::size_type>(i)]);
                }
                board_stack.clear();
                mainLog += player1.getName() + " played " + board_stack[board_stack.size() - 2].toString() + "\n" + player2.getName() + " played " + board_stack[board_stack.size() - 1].toString() + " - " + player1.getName() + " won the turn" + "\n\n";
                checkWin();
                break;
            }

                // the winner of the turn is player2
            else if (board_stack[board_stack.size() - 2].compare(board_stack[board_stack.size() - 1]) < 0)
            {
                player2.addTurnWon();
                // print the winner of the turn
                // Display the winner of the turn
                std::cout << "Winner of the turn: " << player2.getName() << std::endl;

                for (int i = 0; i < board_stack.size(); i++)
                {
                    player2.addTakenCard(board_stack[static_cast<std::vector<Card>::size_type>(i)]);
                }
                board_stack.clear();
                mainLog += player1.getName() + " played " + board_stack[board_stack.size() - 2].toString() + "\n" + player2.getName() + " played " + board_stack[board_stack.size() - 1].toString() + " - " + player2.getName() + " won the turn" + "\n\n";
                checkWin();
                break;
            }
            else // if the cards are equal - continue
            {
                checkWin();

                // update the draw counter
                player1.addTurnDraw();
                player2.addTurnDraw();
                mainLog += player1.getName() + " played " + board_stack[board_stack.size() - 2].toString() + "\n" + player2.getName() + " played " + board_stack[board_stack.size() - 1].toString() + " - " + "WAR" + "\n\n";

                tie_seq++;
            }
        }

        // if the game ends in a tie, return
        if (roundsPlayed == 26 && player1.stacksize() > 0 && player2.stacksize() > 0)
        {
            std::cout << "The game ended in a tie!" << std::endl;
            checkWin();
        }
    }
}
void Game::printLastTurn()
{
    if (roundsPlayed == 0)
    {
        std::cout << "No turns have been played yet." << std::endl;
    }
    else
    {
        // print last turn
        std::cout << "Turn number: " << roundsPlayed << std::endl;
        cout << lastTurn << endl;
    }
}
void Game::printWiner()
{
    if (player1.stacksize() == 0 || player2.stacksize() == 0 || roundsPlayed == 26)
    {

        if (player1.cardesTaken() > player2.cardesTaken())
        {
            std::cout << "The winner is: \n";
            std::cout << "             *** " << player1.getName() << " ***\n" << std::endl;

        }
        else if (player1.cardesTaken() < player2.cardesTaken())
        {
            std::cout << "The winner is: \n";
            std::cout << "             *** " << player2.getName() << " ***\n" << std::endl;
        }
        else
        {
            std::cout << "The game ended in a tie!" << std::endl;
        }
    }
    else
    {
        std::cout << "No winner declared yet!" << std::endl;
    }
}

// printing the log:
void Game::printLog()
{
    if (mainLog.empty())
    {
        std::cout << "No log entries to print." << std::endl;
        return;
    }

    std::cout << "Game log: \n";
    std::cout << std::endl
              << mainLog;
}

// Member function to get the winner
const Player &Game::getWinner() const
{
    if (winner == 1)
    {
        return *players[0];
    }
    else if (winner == 2)
    {
        return *players[1];
    }
    else
    {
        throw std::logic_error("No winner yet!");
    }
}

void Game::printStats()
{

    const int NUM_PLAYERS = 2;
    std::cout << "game statistics: \n";
    std::cout << std::endl;

    if (board_stack.size() > 0)
    {
        // divide it between the players
        for (board_stack.size(); board_stack.size()>0 ;)
        {
            player1.addTakenCard(board_stack[board_stack.size() - 1]);
            if (board_stack.size() >= 1)
                player2.addTakenCard(board_stack[board_stack.size() - 2]);
        }

        board_stack.clear();
    }

    // Introduce the players
    cout << "Players played: " << endl;
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        Player player = (i == 0) ? player1 : player2;
        cout << "   - " << player.getName() << endl;
    }
    cout << "********************************************************" << endl
         << endl;

    // Reveal the rounds results
    cout << "Round won:" << endl;
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        Player player = (i == 0) ? player1 : player2;
        cout << "   - " << player.getName() << " won " << player.getTurnsWon() << " rounds" << endl;
    }
    cout << "And there were " << player1.getTurnsDraw() << " ties!" << endl;
    cout << "********************************************************" << endl
         << endl;

    // Display the remaining cards
    cout << "Cards left:" << endl;
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        Player player = (i == 0) ? player1 : player2;


        cout << "   - " << player.getName() << " has " << player.stacksize() << " cards left" << endl;
    }
    cout << "in the board card stack, there are " << board_stack.size() << " cards" << endl;

    cout << "********************************************************" << endl
         << endl;

    // Announce the final results
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        Player player = (i == 0) ? player1 : player2;
        cout << "   - " << player.getName() << " took " << player.cardesTaken() << " cards in total!" << endl;
    }
    cout << endl;
    cout << "********************************************************" << endl
         << endl;
}

// return game log:
std::string Game::getLog()
{
    return mainLog;
}

// checking if the game is over- if one of the players has no cards or if pass 26 rounds:
void Game::checkWin()
{
    // if pass 26 round or one of the players has no cards
    if (roundsPlayed > 26 || player1.stacksize() == 0 || player2.stacksize() == 0)
    {
        if (board_stack.size() > 0)
        {

            if (player1.cardesTaken() + player2.cardesTaken() < 52)
            {
                // divide it between the players
                for (board_stack.size(); board_stack.size()>0 ;)
                {
                    player1.addTakenCard(board_stack[board_stack.size() - 1]);
                    if (board_stack.size() >= 1)
                        player2.addTakenCard(board_stack[board_stack.size() - 2]);
                }
            }
            board_stack.clear();
        }
        {
            // divide it between the players
            for (board_stack.size(); board_stack.size()>0 ;)
            {
                player1.addTakenCard(board_stack[board_stack.size() - 1]);
                if (board_stack.size() >= 1)
                    player2.addTakenCard(board_stack[board_stack.size() - 2]);
            }
            board_stack.clear();
        }
        // print line
        cout << "********************************************************" << endl;
        cout << "*** The game is over ***" << endl;

        // print every player's cards
        cout << "Player 1 cards taken: " << player1.cardesTaken() << endl;
        player1.cardesTaken();
        cout << "Player 2 cards taken: " << player2.cardesTaken() << endl;
        // print the middle cards
        cout << "Board cards: " << board_stack.size() << endl;
        cout << "********************************************************" << endl;

        if (player1.cardesTaken() > player2.cardesTaken())
        {
            winner = 0;
            printWiner();
        }
        else if (player1.cardesTaken() < player2.cardesTaken())
        {
            winner = 1;
            printWiner();
        }
        else
        {
            winner = 5;
            printWiner();
        }
    }
        // if no winner yet
    else
    {
        winner = -1;
        return;
    }
}

// returning the number of rounds played:
int Game::getRoundsPlayed() const
{
    return roundsPlayed - 1;
}

}
