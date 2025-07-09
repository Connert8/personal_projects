#ifndef CARD_H
#define CARD_H

#include <string>
#include "Suit.h"
#include "Rank.h"
using namespace std;

struct Card {
    Rank rank;
    Suit suit;

    //Constructors
    Card();
    Card(Suit s, Rank r);

    //Getters
    Rank getCardRank() const;
    Suit getCardSuit() const;

    //Setters
    void setCardRank(Rank r);
    void setCardSuit(Suit s);

    //Draws a card using random numbers
    Card drawCard();

    //Prints the card using enum value
    void printCard() const;

    //displays rank alone
    string printRank() const;

    //Displays suit alone
    string printSuit() const; 

};

#endif
