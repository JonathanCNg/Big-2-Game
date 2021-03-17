//
// Created by jonng on 11/30/2020.
//

#include "FaceDownCard.h"

FaceDownCard::FaceDownCard() {
    cardBack = new sf::Texture;
    if (!cardBack->loadFromFile("../cardBackBlue.png"))
        exit(114);
    setTexture(cardBack);
    setSize({50.f, 75});
}