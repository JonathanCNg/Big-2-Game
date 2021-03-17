//
// Created by jonng on 10/19/2020.
//

#ifndef POKER_ANALYSIS_V2_DECK_H
#define POKER_ANALYSIS_V2_DECK_H
#include "Card.h"

class Deck {
public:
    //Constructor creates basic ordered deck
    Deck();

    //Basic Functions
    void shuffle();
    void printDeck();
//    Card giveCard();
//    int getNumCardsLeft();
//    void takeCard();

    //Output Card of Deck
    Card getCardOfDeck(int deckIndex);
    std::string getRankOfCard(int deckIndex);
    std::string getSuitOfCard(int deckIndex);

    //Output Overload
    friend std::ostream& operator << (std::ostream& outs, Deck& aDeck);
private:
    void swap(Card& card1, Card& card2);
    Card theDeck[52];
//    int deckSize;
};


#endif //POKER_ANALYSIS_V2_DECK_H
