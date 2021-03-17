//
// Created by jonng on 10/18/2020.
//

#ifndef POKER_ANALYSIS_V2_CARD_H
#define POKER_ANALYSIS_V2_CARD_H
#include "Rank.h"
#include "Suit.h"
#include "Background.h"
#include "FaceDownCard.h"

class Card : public sf::Drawable, public sf::Transformable{
public:
    //Constructors
    Card();
    Card(Rank::rankEnum aRank, Suit::suitsEnum aSuit);
    Card(Rank::rankEnum aRank, Suit::suitsEnum aSuit, int hPos, int vPos);

    //Setters
    void setRankAndSuit(Rank::rankEnum aRank, Suit::suitsEnum aSuit);
    void setIsRevealed(bool input);
    void setIsSelected(bool input);
    void setIsReserved(int input);

    //Getters
    std::string getRankAndString();
    int getRankInt();
    std::string getRankString();
    int getSuitInt();
    std::string getSuitString();
    bool getIsRevealed();
    bool getIsSelected();
    int getIsReserved();
    int getBig2Value();//3=1, 4=2, ... , A = 12, 2 = 13

    //SFML
    void createSFMLCard();
    sf::FloatRect getGlobalBounds();
    void move(float x, float y);
    void setCardPosition(int hPos, int vPos);
    void createLeft();
    void createRight();

    //Overload operators
    friend std::ostream& operator << (std::ostream& outs, Card& aCard);
    void operator = (Card& aCard);

    //bc it's drawable and transformable
    virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;

    //Additional functions
    static int placeInOrderedDeck(int theRank, int theSuit); //1-52
private:
    bool isRevealed;
    bool isSelected;
    int isReserved;
    //0 = not reserved
    //2 = reserved for pair
    //5 = reserved for 5-card hand
    Background cardBackground;
    FaceDownCard aFaceDownCard;
    Rank cardRank;
    Suit cardSuit;
};


#endif //POKER_ANALYSIS_V2_CARD_H
