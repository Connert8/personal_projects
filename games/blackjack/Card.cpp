#include "Card.h"
#include <string>
#include <iostream>
using namespace std;


Rank rank;
Suit suit;


//Constructors
Card::Card() : suit(SPADES), rank(ACE) {}
Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

//Getters
Rank Card::getCardRank() const { return rank; }
Suit Card::getCardSuit() const { return suit; }

//Setters
void Card::setCardRank(Rank r) { rank = r; }
void Card::setCardSuit(Suit s) { suit = s; }


Card Card::drawCard() {
    Rank rank;
    Suit suit;
    int s, r;
    r = rand() % 13 + 1;
    s = rand() % 5;
    //cout << r << " " << s << endl;

    switch (r) {
        case 1:
            rank = ACE;
            break;
        case 2:
            rank = TWO;
            break;
        case 3:
            rank = THREE;
            break;
        case 4:
            rank = FOUR;
            break;
        case 5:
            rank = FIVE;
            break;
        case 6:
            rank = SIX;
            break;
        case 7:
            rank = SEVEN;
            break;
        case 8:
            rank = EIGHT;
            break;
        case 9:
            rank = NINE;
            break;
        case 10:
            rank = TEN;
            break;
        case 11:
            rank = JACK;
            break;
        case 12:
            rank = QUEEN;
            break;
        case 13:
            rank = KING;
            break;
    };

    switch(s) {
        case 1:
            suit = CLUBS;
            break;
        case 2:
            suit = SPADES;
            break;
        case 3:
            suit = DIAMONDS;
            break;
        case 4:
            suit = HEARTS;
            break;
    };

    Card card(suit, rank);

    return card;


}



//Prints the card using enum value
void Card::printCard() const {
    switch(Card::suit) {
        case SPADES:
            cout << "Spades\n";
            break;
        case DIAMONDS:
            cout << "Diamonds\n";
            break;
        case HEARTS:
            cout << "Hearts\n";
            break;
        case CLUBS:
            cout << "Clubs\n";
            break;
        default:
            cout << "-Error in printing Suit-";
            return;

    };


    switch(Card::rank) {
        case ACE:
            cout << "Ace\n";
            break;
        case TWO:
            cout << "Two\n";
            break;
        case THREE:
            cout << "Three\n";
            break;
        case FOUR:
            cout << "Four\n";
            break;
        case FIVE:
            cout << "Five\n";
            break;
        case SIX:
            cout << "Six\n";
            break;
        case SEVEN:
            cout << "Seven\n";
            break;
        case EIGHT:
            cout << "Eight\n";
            break;
        case NINE:
            cout << "Nine\n";
            break;
        case TEN:
            cout << "Ten\n";
            break;
        case JACK:
            cout << "Jack\n";
            break;
        case QUEEN:
            cout << "Queen\n";
            break;
        case KING:
            cout << "King\n";
            break;
        default:
            cout << "-Error in printing Rank-";
            return;


    };
    
}

string Card::printRank() const {
    switch(Card::rank) {
        case ACE:
            return "Ace";
            break;
        case TWO:
            return "Two";
            break;
        case THREE:
            return "Three";
            break;
        case FOUR:
            return "Four";
            break;
        case FIVE:
            return "Five";
            break;
        case SIX:
            return "Six";
            break;
        case SEVEN:
            return "Seven";
            break;
        case EIGHT:
            return "Eight";
            break;
        case NINE:
            return "Nine";
            break;
        case TEN:
            return "Ten";
            break;
        case JACK:
            return "Jack";
            break;
        case QUEEN:
            return "Queen";
            break;
        case KING:
            return "King";
            break;
        default:
            return "-Error in printing Rank-";


    };


}

string Card::printSuit() const {
    switch(Card::suit) {
        case SPADES:
            return "Spades";
            break;
        case DIAMONDS:
            return "Diamonds";
            break;
        case HEARTS:
            return "Hearts";
            break;
        case CLUBS:
            return "Clubs";
            break;
        default:
            return "-Error in printing Suit-";

    };


}
