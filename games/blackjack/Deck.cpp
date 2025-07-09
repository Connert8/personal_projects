#include <iostream>
#include <vector>
#include "Deck.h"
#include <string>
using namespace std;



vector<Card> cards;

//Constructor
Deck::Deck() {}

//Method for initializing the deck based on how many cards are input
Deck::Deck(int size) {
    vector<Card> temp(size);
    cards = temp;

    int i = 0;
    //For suit range clubs to hearts and rank range ace to king, cards at the index = enum value
    for (Suit suit = CLUBS; suit <= HEARTS; suit = Suit(suit+1)) {
        for (Rank rank = ACE; rank <= KING; rank = Rank(rank+1)) {
            cards[i].suit = suit;
            cards[i].rank = rank;
            i++;
        }
    }
}

void Deck::populateDeck(int size) {
    cards.clear();
    vector<Card> temp(size);
    cards = temp;

    int i = 0;
    //For suit range clubs to hearts and rank range ace to king, cards at the index = enum value
    for (Suit suit = CLUBS; suit <= HEARTS; suit = Suit(suit+1)) {
        for (Rank rank = ACE; rank <= KING; rank = Rank(rank+1)) {
            cards[i].suit = suit;
            cards[i].rank = rank;
            i++;
        }
    }
}


void Deck::clearDeck() {
    cards.clear();
}

int Deck::countCardsInDeck() {
    int count = 0;
    for (size_t i = 0; i < cards.size(); i++) {
        count += 1;
    }
    return count;
}

bool Deck::checkForEmptyDeck() { // Currently trying to get this to make the game stop
    if (cards.size() <= 0) {
        cout << " - Shoe is empty - \n";
        return false;
    }
    return true;
}

void Deck::addCardToDeck(Card card) {
    cards.push_back(card);
}

void Deck::subtractCardFromDeck(Card card) {
    int i = 0;
    for (auto& d : cards) { // d is cards[i]
        if (d.getCardRank() == card.getCardRank() && d.getCardSuit() == card.getCardSuit()) {
            cards.erase(cards.begin() + i);
        }
        i += 1;

    }

}


Card* Deck::findCardInDeck(const Card& card) {
    for (size_t i = 0; i < cards.size(); i++) {
        if (cards[i].getCardRank() == card.getCardRank() && cards[i].getCardSuit() == card.getCardSuit()) {
            return &cards[i];
        }
    }
    return nullptr;

}


bool Deck::drawCardFromDeck(const Card& card) { //run until card in deck is drawn then subtract
    Card* find = nullptr;
    
    find = findCardInDeck(card);
        
    if (find != nullptr) {
        subtractCardFromDeck(card);
        return true;
    }

    return false;
}


void Deck::displayDeck() const {
    for (const auto& d : cards) {
        d.printCard();
    }


}
