//
// Created by jonng on 11/30/2020.
//

#ifndef FINAL_PROJECT_FACEDOWNCARD_H
#define FINAL_PROJECT_FACEDOWNCARD_H
#include <SFML/Graphics.hpp>

class FaceDownCard : public sf::RectangleShape {
public:
    FaceDownCard();
private:
    sf::Texture* cardBack;
};


#endif //FINAL_PROJECT_FACEDOWNCARD_H
