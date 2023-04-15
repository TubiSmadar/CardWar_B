#include<algorithm>
#include<ctime>
#include <random>
#include "game.hpp"

using namespace std;

namespace ariel{

    void Game::shuffleDeck(){
        random_device rd;
        mt19937 g(rd());
        std::shuffle(this->deck.begin(), this->deck.end(), g);
    }

    void Game::dealCards(){
        for(uint i = 0; i < this->deck.size(); i++){
            this->player1->withdrawCard(this->deck.at(i++));
            this->player2->withdrawCard(this->deck.at(i));
        }
        this->deck.clear();
        this->deck.shrink_to_fit();
    }

    void Game::generateGame(){
        int num[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
        string type[4] = {"Clubs", "Hearts", "Diamonds", "Spades"};
        
        for(int i = 0; i < 13; i++){
            for(int j = 0; j < 4; j++){
                this->deck.push_back(Card(num[i], type[j]));
            }
        }
        this->player1->setInPlay(true);
        this->player2->setInPlay(true);
        shuffleDeck();
        dealCards();
    }

   string Game::setLogString(string name1, Card card1, string name2, Card card2, int flag) {
        string msg = name1 + " played " + card1.toString() + " " + name2 + " played " + card2.toString() + ". ";

        if (flag == 0) {
            return msg + "Draw.";
        } else if (flag == 1) {
            return msg + name1 + " wins.";
        } else {
            return msg + name2 + " wins.";
        }
    }

int Game::play(string* document, int* cards_won, int* winner){
    if (this->player1->stacksize() == 0 || this->player2->stacksize() == 0){
        this->player1->setInPlay(0);
        this->player2->setInPlay(0);
        return 0;
    }

    Card player1_card = this->player1->playCard();
    Card player2_card = this->player2->playCard();
    string player1_name = this->player1->getName();
    string player2_name = this->player2->getName();
    *(cards_won) += 2;

    if (player1_card == player2_card) {
        *(document) += setLogString(player1_name, player1_card, player2_name, player2_card, 0);
        this->draws++;

        if (this->player1->stacksize() != 0 && this->player2->stacksize() != 0) {
            this->player1->playCard();
            this->player2->playCard();
            *(cards_won) += 2;
        }
        return 1;
    }
    else if (player1_card > player2_card) {
        *(document) += setLogString(player1_name, player1_card, player2_name, player2_card, 1);
        this->player1->setCardsTaken(*(cards_won));
        this->player1->addToTotalWinnings();
        *(winner) = 1;
        return 0;
    }
    else {
        *(document) += setLogString(player1_name, player1_card, player2_name, player2_card, 2);
        this->player2->setCardsTaken(*(cards_won));
        this->player2->addToTotalWinnings();
        *(winner) = 2;
        return 0;
    }
    return 1;
}

    Game::Game(Player& pl1, Player& pl2){
        if(pl1.getInPlay() != 0){
            throw new invalid_argument("player 1 is in a game!");
        }

        if(pl2.getInPlay() != 0){
            throw new invalid_argument("player 2 is in a game!");
        }

        this->player1 = &pl1;
        this->player2 = &pl2;
        this->deck = {};
        this->log = {};
        this->draws = 0;
        this->turns = 0;
        this->generateGame();
    }
    
    void Game::playTurn(){
        if(this->player1 == this->player2){
            throw new invalid_argument("Play with friends please!");
        }

        int turnWinner = 0;
        string turnDocument = "";
        int cardsWon = 0;

        if(this->turns >=26){
            throw new invalid_argument("Game ended");
        }

        bool turnFinished = false;
        while (!turnFinished) {
            this->turns++;

            int result = play(&turnDocument, &cardsWon, &turnWinner);

            if (result == 0) {
                // A player has won the turn
                turnFinished = true;
                string winnerName = (turnWinner == 1) ? this->player1->getName() : this->player2->getName();
                cout << winnerName << " wins the turn!" << endl;
            } else if (result == 1) {
                // A draw occurred
                cout << "Draw!" << endl;
            }
        }


        this->log.push_back(turnDocument);

        if(!turnWinner){
            this->player1->setCardsTaken(cardsWon / 2);
            this->player2->setCardsTaken(cardsWon / 2);
        }
    }

    void Game::printLastTurn(){
        if(this->log.size() == 0){
            throw new logic_error("Turn log is empty!");
        }
        cout << this->log.back() << endl;
    }

    void Game::playAll(){
        while(this->player1->getInPlay() != 0 || this->player2->getInPlay() != 0){
            if(this->turns < 26){
                this->playTurn();
            }
            else{
                break;
            }
        }

        if(this->turns != 26){
            this->turns = 26;
        }
    }

    void Game::printWiner(){
        if (this->player1->getTotalWinnings() > this->player2->getTotalWinnings()) {
            cout << this->player1->getName() << " won the match!" << endl;
        } else if (this->player1->getTotalWinnings() < this->player2->getTotalWinnings()) {
            cout << this->player2->getName() << " won the match!" << endl;
        } else {
            cout << "The match ended in a draw!" << endl;
        }
    }

    void Game::printLog(){
        if(this->log.size() == 0){
            throw new logic_error("Game log is empty!");
        }

        for(uint i = 0; i < this->log.size(); i++){
            cout << this->log.at(i) << endl;
        }
    }

    void Game::printStats(){
        cout << "-----------------------------------------------------------------------------------------------------------\n" << endl;
        cout << "Player name: " << this->player1->getName() << endl;
        cout << "Cards gained " << this->player1->cardesTaken() << endl;
        cout << "Cards left: " << this->player1->stacksize() << endl;
        cout << "Total winnings: " << this->player1->getTotalWinnings() << endl;
        cout << "Turns played: " << this->turns << endl;
        cout << "Win rate: " <<  float(this->player1->getTotalWinnings()) / float(this->turns) << "%" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------\n" << endl;
        cout << "Player name: " << this->player2->getName() << endl;
        cout << "Cards gained " << this->player2->cardesTaken() << endl;
        cout << "Cards left: " << this->player2->stacksize() << endl;
        cout << "Total winnings: " << this->player2->getTotalWinnings() << endl;
        cout << "Turns played: " << this->turns << endl;
        cout << "Win rate: " << float(this->player2->getTotalWinnings()) / float(this->turns) << "%" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------\n" << endl;
        cout << "Total draws: " << this->draws << endl;
    }
}
