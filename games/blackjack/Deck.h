#ifndef DECK_H
#define DECK_H

#include <string>
#include <vector>
#include "Card.h"
using namespace std;

struct Deck {
    vector<Card> cards;

    //Constructor
    Deck();

    //Method for initializing the deck based on how many cards are input
    Deck(int size);

    void populateDeck(int size);

    void clearDeck();

    int countCardsInDeck();

    bool checkForEmptyDeck();

    void addCardToDeck(Card card);

    void subtractCardFromDeck(Card card);
    
    Card* findCardInDeck(const Card& card);

    bool drawCardFromDeck(const Card& card);

    void displayDeck() const;

};

#endif