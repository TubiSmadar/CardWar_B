#include "player.hpp"

using namespace std;

namespace ariel{
        
    //Getters
    string Player::getName() const{
        return this->name;
    }

    int Player::cardesTaken() const{
        return this->cards_taken;
    }

    int Player::stacksize() const{
        return this->hand.size();
    }

    int Player::getInPlay() const{
        return this->in_play;
    }

    int Player::getTotalWinnings() const{
        return this->total_winning;
    }

    //Setters
    void Player::addToTotalWinnings(){
        this->total_winning += 1;
    }

    void Player::setInPlay(int in_play){
        this->in_play = in_play;
    }

    void Player::setCardsTaken(int num){
        this->cards_taken += num;
    }


    void Player::withdrawCard(Card& card){
        this->hand.push_back(card);
    }

    Card Player::playCard(){
        Card card =  this->hand.back();
        this->hand.pop_back();
        return card;
    }

    bool Player::operator==(const Player& other) const{
        if(this->name == other.getName()){
            return true;;
        }
        return false;
    }

    Player::Player(string name) : name(name){
        this->total_winning = 0;
        this->in_play = 0;
        this->hand = {};
        this->cards_taken = 0;
    }

Player::Player() {
    static int player_number = 0;
    player_number++;
    this->name = "player_" + to_string(player_number);

    this->total_winning = 0;
    this->in_play = 0;
    this->hand = {};
    this->cards_taken = 0;
}
Player::~Player() {}
        
}
