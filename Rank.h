//
// Created by jonng on 10/18/2020.
//

#ifndef POKER_ANALYSIS_V2_RANK_H
#define POKER_ANALYSIS_V2_RANK_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <ctime>
#include "Suit.h"

class Rank : public sf::Text {
public:
    enum rankEnum {
        INVALID, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
    };

    //Setters
    void setRank(rankEnum aRank, Suit::suitsEnum aSuit);
    void setSFMLRank();
    void setRankPositionCenter(sf::FloatRect backgroundBounds);

    //Getters
    rankEnum getRankEnum();
    int getRankInt();
    std::string getRankString();

    //Converters
    static std::string convertIntToRankString(int aRank);
    static rankEnum convertIntToRankEnum(int aRank);\

    //Overload Output
    friend std::ostream& operator << (std::ostream& outs, Rank& aRank);
private:
    sf::Color determineRankColor(int aSuit);
    sf::Font rankFont;
    int theRank;
    int theSuitForColor;
};


#endif //POKER_ANALYSIS_V2_RANK_H
