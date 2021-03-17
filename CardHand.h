//
// Created by jonng on 11/30/2020.
//

#ifndef FINAL_PROJECT_CARDHAND_H
#define FINAL_PROJECT_CARDHAND_H
#include <vector>
#include "Card.h"
using namespace std;

class CardHand : public std::vector<Card>{
public:
    Card takeCardAt(int cardIndex);
    void sortByValue();
    void sortBySuit();
    int findTriples(); //returns value of triple
    int findDoubles(); //returns highest card of double
    //0 = none
    //1+ = num of pairs found
    int findBest5CardHand();
    //0 = none
    //101-152 = strongest value in straight
    //201-213 = strongest value in flush
    //301-313 = strongest value in full house
    //401-413 = quad value in four of a kind
    //501-552 = strongest value in straight flush
    friend ostream& operator << (ostream& outs, CardHand& aCardHand);
//    void operator = (CardHand& aCardHand);
    CardHand createCopy();
    Card* accessCard(int theRank, int theSuit);
    void clearReservations();
private:
    void printAll(ostream& outs);
    void erase(int cardIndex);
    int findBestStraightFlush();
    int findBest4OfAKind();
    int findBestFullHouse();
    int findBestFlush();
    int findBestStraight();

};


#endif //FINAL_PROJECT_CARDHAND_H
