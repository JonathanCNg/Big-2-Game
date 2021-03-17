//
// Created by jonng on 10/18/2020.
//

#ifndef POKER_ANALYSIS_V2_SUIT_H
#define POKER_ANALYSIS_V2_SUIT_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Suit : public sf::Drawable, public sf::Transformable{
public:
    enum suitsEnum {
        DIAMONDS, CLUBS, HEARTS, SPADES
    };

    //Setters
    void setSuit(suitsEnum aSuit);
    void setSuitPositions(sf::FloatRect bounds);

    //Getters
    suitsEnum getSuitEnum();
    int getSuitInt();
    std::string getSuitString();

    //SFML
    void setSFMLSuit();
    void move(float x, float y);

    //Converters
    static std::string convertIntToSuitString(int aSuit);
    static suitsEnum convertIntToSuitEnum(int aSuit);

    //Overload Output
    friend std::ostream& operator << (std::ostream& outs, Suit& aSuit);

    //bc its drawable and transformable
    virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;

    void updateSuit();
private:
    void setImage(int aSuit);
    sf::RectangleShape leftTopSuit;
    sf::RectangleShape bottomRightSuit;
    sf::Texture* suitImage;
    int theSuit;
};


#endif //POKER_ANALYSIS_V2_SUIT_H
