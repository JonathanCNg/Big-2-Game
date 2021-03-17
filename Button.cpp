//
// Created by jonng on 12/7/2020.
//

#include "Button.h"

Button::Button(string input, float x, float y, float width, float height) {
    buttonBackground.setFillColor(sf::Color::White);
    buttonBackground.setSize({width,height});
    setPosition(x,y);
    if(!theFont.loadFromFile("../MilkyNice.ttf"))
        exit(10);
    theText.setFont(theFont);
    theText.setString(input);
    theText.setFillColor(Color::Black);
    theText.setCharacterSize(25);
    theText.setOrigin(theText.getGlobalBounds().width/2, theText.getGlobalBounds().height/2);
    theText.setPosition(buttonBackground.getGlobalBounds().left + buttonBackground.getGlobalBounds().width/2, buttonBackground.getGlobalBounds().top + buttonBackground.getGlobalBounds().height/2-5);
}

void Button::setPosition(float x, float y) {
    buttonBackground.setPosition(x,y);
    theText.setPosition(buttonBackground.getGlobalBounds().left + buttonBackground.getGlobalBounds().width/2, buttonBackground.getGlobalBounds().top + buttonBackground.getGlobalBounds().height/2);
}
void Button::draw (RenderTarget &window, RenderStates states) const {
    window.draw(buttonBackground);
    window.draw(theText);
}
FloatRect Button::getGlobalBounds() {
    return buttonBackground.getGlobalBounds();
}