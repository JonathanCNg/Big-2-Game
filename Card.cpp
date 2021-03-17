//
// Created by jonng on 10/18/2020.
//

#include "Card.h"

Card::Card() : Card(Rank::ACE, Suit::DIAMONDS, 0, 0){}
Card::Card(Rank::rankEnum aRank, Suit::suitsEnum aSuit) : Card(aRank, aSuit, 0, 0){}
Card::Card(Rank::rankEnum aRank, Suit::suitsEnum aSuit, int hPos, int vPos) : isRevealed(true), isSelected(false), isReserved(0){
    setRankAndSuit(aRank, aSuit);
    setCardPosition(hPos,vPos);
}
void Card::setRankAndSuit(Rank::rankEnum aRank, Suit::suitsEnum aSuit) {
    cardRank.setRank(aRank, aSuit);
    cardSuit.setSuit(aSuit);
}
void Card::createSFMLCard() {
    if (isRevealed) {
        cardRank.setSFMLRank();
        cardSuit.setSFMLSuit();
    }
}
std::string Card::getRankAndString() {
    return (getRankString() + " of " + getSuitString());
}
int Card::getRankInt() {
    return cardRank.getRankInt();
}
std::string Card::getRankString(){
    return cardRank.getRankString();
}
int Card::getSuitInt() {
    return cardSuit.getSuitInt();
}
std::string Card::getSuitString() {
    return cardSuit.getSuitString();
}
void Card::setCardPosition(int hPos, int vPos) {
    cardBackground.setPosition(hPos,vPos);
    cardRank.setRankPositionCenter(cardBackground.getGlobalBounds());
    cardSuit.setSuitPositions(cardBackground.getGlobalBounds());
    aFaceDownCard.setPosition(hPos,vPos);
}
sf::FloatRect Card::getGlobalBounds() {
    return cardBackground.getGlobalBounds();
}
void Card::move(float x, float y) {
    cardBackground.move(x,y);
    cardRank.move(x,y);
    cardSuit.move(x,y);
    aFaceDownCard.move(x,y);
}
std::ostream& operator << (std::ostream& outs, Card& aCard) {
    outs << aCard.cardRank << " of " << aCard.cardSuit;
    return outs;
}
void Card::operator = (Card& aCard) {
    cardRank.setRank(Rank::convertIntToRankEnum(aCard.getRankInt()), Suit::convertIntToSuitEnum(aCard.getSuitInt()));
    cardSuit.setSuit(Suit::convertIntToSuitEnum(aCard.getSuitInt()));
}
void Card::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    if (isRevealed) {
        window.draw(cardBackground);
        window.draw(cardRank);
        window.draw(cardSuit);
    }
    else {
        window.draw(aFaceDownCard);
    }
}
void Card::setIsRevealed(bool input) {
    isRevealed = input;
}
void Card::setIsSelected(bool input) {
    isSelected = input;
    if(isSelected) {
        cardBackground.setFillColor({sf::Color::Yellow});
    }
    else {
        cardBackground.setFillColor(sf::Color::White);
    }
}
bool Card::getIsRevealed() {
    return isRevealed;
}
bool Card::getIsSelected() {
    return isSelected;
}
void Card::setIsReserved(int input) {
    isReserved = input;
}
int Card::getIsReserved() {
    return isReserved;
}
int Card::placeInOrderedDeck(int theRank, int theSuit) {
    int position(0);
    position += (theRank-1)*4;
    position += theSuit+1;
    return position;
}
int Card::getBig2Value() {
    int value = getRankInt();
    if(value >= 1 && value <= 2) {
        value += 11;
    }
    else
        value -= 2;
    return value;
}
void Card::createLeft() {
//    cardBackground.makeLeft();
//    cardRank.makeLeft();
//    cardSuit.makeLeft();

//    cardRank.rotate(-90);
    createSFMLCard();
    cardBackground.setRotation(-90);
    aFaceDownCard.setRotation(-90);
}
void Card::createRight() {
//    cardBackground.makeRight();
//    cardRank.makeRight();
//    cardSuit.makeRight();

    createSFMLCard();
    cardBackground.setRotation(90);
    aFaceDownCard.setRotation(90);
}