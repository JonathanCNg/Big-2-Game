//
// Created by jonng on 12/9/2020.
//

#include "SplashScreen.h"

SplashScreen::SplashScreen() {
    theImage = new sf::Texture;
    if (!theImage->loadFromFile("../SplashScreen.png"))
        exit(22);
    setTexture(theImage);
    setSize({960.f, 960.f});
    setPosition(0,0);
}