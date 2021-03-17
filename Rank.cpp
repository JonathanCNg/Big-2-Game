//
// Created by jonng on 10/18/2020.
//

#include "Rank.h"

void Rank::setRank(rankEnum aRank, Suit::suitsEnum aSuit) {
    theRank = aRank;
    theSuitForColor = aSuit;
}
void Rank::setSFMLRank() {
    if(!rankFont.loadFromFile("../MilkyNice.ttf"))
        exit(10);
    setFont(rankFont);
    setString(convertIntToRankString(theRank));
    setFillColor(determineRankColor(theSuitForColor));
    setCharacterSize(25);
}

void Rank::setRankPositionCenter(sf::FloatRect backgroundBounds) {
    setOrigin(getGlobalBounds().width/2, getGlobalBounds().height/2);
    setPosition(backgroundBounds.left + backgroundBounds.width/2, backgroundBounds.top + backgroundBounds.height/2 - 6);
}

Rank::rankEnum Rank::getRankEnum() {
    return convertIntToRankEnum(theRank);
}
int Rank::getRankInt() {
    return theRank;
}
std::string Rank::getRankString() {
    return convertIntToRankString(theRank);
}

std::string Rank::convertIntToRankString(int aRank) {
    std::string ranksAsString[14] = {"INVALID", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    if (aRank > 0 && aRank < 14)
        return ranksAsString[aRank];
    else
        exit(10);
}

Rank::rankEnum Rank::convertIntToRankEnum(int aRank){
    switch(aRank)
    {
        case 1: return ACE;
        case 2: return TWO;
        case 3: return THREE;
        case 4: return FOUR;
        case 5: return FIVE;
        case 6: return SIX;
        case 7: return SEVEN;
        case 8: return EIGHT;
        case 9: return NINE;
        case 10: return TEN;
        case 11: return JACK;
        case 12: return QUEEN;
        case 13: return KING;
        default: exit(11);
    }
}

std::ostream& operator << (std::ostream& outs, Rank& aRank) {
    outs << aRank.getRankString();
    return outs;
}

sf::Color Rank::determineRankColor(int aSuit) {
    if(aSuit == Suit::HEARTS || aSuit == Suit::DIAMONDS)
        return {255,94,114};
    else if (aSuit == Suit::CLUBS || aSuit == Suit::SPADES)
        return {66,66,66};
    else
        exit(12);
}
