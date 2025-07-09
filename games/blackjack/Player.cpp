#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std; 

vector<Card> hand;
int playerchips;

Player::Player() : playerchips(0) {}
Player::Player (int c) : playerchips(c) {}

//Getter
int Player::getPlayerChips() const {return playerchips;}

//Setter
void Player::setPlayerChips(int chips) { playerchips = chips; }

void Player::displayPlayerHand() const {
    for (const auto& h : hand) {
        cout << h.printRank() << " of " << h.printSuit() << "\n";
    }
}

void Player::displayPlayerChips() const {
    cout << "You have " << playerchips << " chips.\n";
}

void Player::addChipsToPlayer(int chips) {
    playerchips = playerchips + chips;
}

void Player::removeChipsFromPlayer(int chips) {
    playerchips = playerchips - chips;
}

void Player::addCardToHand(Card card) {
    hand.push_back(card);
}

void Player::clearPlayerHand() {
    hand.clear();
}

bool Player::checkPlayerHand() {
    Rank rank;
    int total = 0;

    for (size_t i = 0; i < hand.size(); i++) {

        rank = hand[i].getCardRank();

        switch(rank) {
            case ACE: //!! make ace also equal 11
                total += 1;
                break;
            case TWO:
                total += 2;
                break;
            case THREE:
                total += 3;
                break;
            case FOUR:
                total += 4;
                break;
            case FIVE:
                total += 5;
                break;
            case SIX:
                total += 6;
                break;
            case SEVEN:
                total += 7;
                break;
            case EIGHT:
                total += 8;
                break;
            case NINE:
                total += 9;
                break;
            case TEN:
                total += 10;
                break;
            case JACK:
                total += 10;
                break;
            case QUEEN:
                total += 10;
                break;
            case KING:
                total += 10;
                break;
            default:
                cout << "-Error in finding Rank-";
                return 0;


        };
    }

    if (total > 21) {return false;}
    else {return true;}
}

int Player::addPlayerHand() {
    Rank rank;
    int total = 0;

    for (size_t i = 0; i < hand.size(); i++) {

        rank = hand[i].getCardRank();

        switch(rank) {
            case ACE: //!! make ace also equal 11
                total += 1;
                break;
            case TWO:
                total += 2;
                break;
            case THREE:
                total += 3;
                break;
            case FOUR:
                total += 4;
                break;
            case FIVE:
                total += 5;
                break;
            case SIX:
                total += 6;
                break;
            case SEVEN:
                total += 7;
                break;
            case EIGHT:
                total += 8;
                break;
            case NINE:
                total += 9;
                break;
            case TEN:
                total += 10;
                break;
            case JACK:
                total += 10;
                break;
            case QUEEN:
                total += 10;
                break;
            case KING:
                total += 10;
                break;
            default:
                cout << "-Error in finding Rank-";
                return 0;

        };
    }

    return total;

}