//
// Created by jonng on 10/19/2020.
//

#include "Deck.h"

Deck::Deck() {
    for (int currentRank = 1; currentRank < 14; currentRank++) {
        for (int currentSuit = 0; currentSuit < 4; currentSuit++)
        {
            theDeck[((currentRank-1) * 4) + currentSuit].setRankAndSuit(Rank::convertIntToRankEnum(currentRank), Suit::convertIntToSuitEnum(currentSuit));
        }
    }
}
void Deck::shuffle() {
    for (int swapsDone = 0; swapsDone < 100; swapsDone++)
    {
        swap(theDeck[rand()%52], theDeck[rand()%52]);
    }
}
void Deck::printDeck() {
    for (int deckIndex = 0; deckIndex < 52; deckIndex++)
    {
        std::cout << std::setw(2) << deckIndex + 1 << ": " << std::setw(2) << theDeck[deckIndex].getRankString() << " of " << theDeck[deckIndex].getSuitString() << std::endl;
    }
}
//Card Deck::giveCard() {
//
//}
//int Deck::getNumCardsLeft() {
//
//}
//void Deck::takeCard() {
//
//}
Card Deck::getCardOfDeck(int deckIndex) {
    return theDeck[deckIndex];
}
std::string Deck::getRankOfCard(int deckIndex) {
    return theDeck[deckIndex].getRankString();
}
std::string Deck::getSuitOfCard(int deckIndex) {
    return theDeck[deckIndex].getSuitString();
}
std::ostream& operator << (std::ostream& outs, Deck& aDeck) {
    for (int deckIndex = 0; deckIndex < 52; deckIndex++)
    {
        outs << std::setw(2) << deckIndex + 1 << ": " << std::setw(2) << aDeck.theDeck[deckIndex].getRankString() << " of " << aDeck.theDeck[deckIndex].getSuitString() << std::endl;
    }
    return outs;
}
void Deck::swap(Card& card1, Card& card2) {
    Card temp = card1;
    card1 = card2;
    card2 = temp;
}