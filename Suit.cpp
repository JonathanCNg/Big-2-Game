//
// Created by jonng on 10/18/2020.
//

#include "Suit.h"

void Suit::setSuit(suitsEnum aSuit) {
    theSuit = aSuit;
}
void Suit::setSFMLSuit() {
    setImage(getSuitEnum());
    bottomRightSuit.setRotation(180);
}
void Suit::move(float x, float y) {
    leftTopSuit.move(x,y);
    bottomRightSuit.move(x,y);
}
void Suit::setSuitPositions(sf::FloatRect bounds) {
    leftTopSuit.setPosition(bounds.left + 3, bounds.top + 3);
    bottomRightSuit.setPosition(bounds.left + bounds.width - 3, bounds.top + bounds.height - 3);
}
Suit::suitsEnum Suit::getSuitEnum() {
    return convertIntToSuitEnum(theSuit);
}
int Suit::getSuitInt() {
    return theSuit;
}
std::string Suit::getSuitString() {
    return convertIntToSuitString(theSuit);
}
std::string Suit::convertIntToSuitString(int aSuit) {
    std::string suitsAsString[4] = {"DIAMONDS", "CLUBS", "HEARTS", "SPADES"};
    if (aSuit >= 0 && aSuit < 4)
        return suitsAsString[aSuit];
    else
        exit(20);
}
Suit::suitsEnum Suit::convertIntToSuitEnum(int aSuit) {
    switch(aSuit)
    {
        case 0: return DIAMONDS;
        case 1: return CLUBS;
        case 2: return HEARTS;
        case 3: return SPADES;
        default: exit(21);
    }
}
std::ostream& operator << (std::ostream& outs, Suit& aSuit) {
    outs << aSuit.getSuitString();
    return outs;
}
void Suit::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    window.draw(leftTopSuit);
    window.draw(bottomRightSuit);
}
void Suit::setImage(int aSuit) {
    std::string suitString;
    switch(aSuit) {
        case DIAMONDS:
            suitString = "../diamonds.png";
            break;
        case CLUBS:
            suitString = "../clubs.png";
            break;
        case HEARTS:
            suitString = "../hearts.png";
            break;
        case SPADES:
            suitString = "../spades.png";
            break;
    }
    suitImage = new sf::Texture;
    if (!suitImage->loadFromFile(suitString))
        exit(22);
    leftTopSuit.setTexture(suitImage);
    bottomRightSuit.setTexture(suitImage);
    leftTopSuit.setSize({17.f, 17.f});
    bottomRightSuit.setSize({17.f, 17.f});
//    leftTopSuit.setScale(0.5f, 0.5f);
//    bottomRightSuit.setScale(0.5f, 0.5f);
}
void Suit::updateSuit() {
    setImage(theSuit);
}