//
// Created by jonng on 12/9/2020.
//

#include "Light.h"

Light::Light() {
    setFillColor(Color::Yellow);
    setSize({10.f,10.f});
    setPosition(5,5);
    setOrigin(getGlobalBounds().width/2,getGlobalBounds().height/2);
}