#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>
#include <string>
using namespace std;

struct Player {
    vector<Card> hand;
    int playerchips;

    Player();
    Player (int c);

    //Getter
    int getPlayerChips() const;
    
    //Setter
    void setPlayerChips(int chips);

    void displayPlayerHand() const;

    void displayPlayerChips() const;

    void addChipsToPlayer(int chips);

    void removeChipsFromPlayer(int chips);

    void addCardToHand(Card card);

    void clearPlayerHand();

    bool checkPlayerHand();

    int addPlayerHand();

};


#endif