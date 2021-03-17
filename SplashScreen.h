//
// Created by jonng on 12/9/2020.
//

#ifndef FINAL_PROJECT_SPLASHSCREEN_H
#define FINAL_PROJECT_SPLASHSCREEN_H
#include <SFML/Graphics.hpp>
#include "Button.h"
using namespace std;
using namespace sf;
class SplashScreen : public RectangleShape {
public:
    SplashScreen();
private:
    Texture* theImage;
};


#endif //FINAL_PROJECT_SPLASHSCREEN_H
