//
// Created by jonng on 12/7/2020.
//

#ifndef FINAL_PROJECT_BUTTON_H
#define FINAL_PROJECT_BUTTON_H
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Button : public Drawable, public Transformable{
public:
    Button(string input, float x, float y, float width, float height);
    void setPosition(float x, float y);
    void draw (RenderTarget &window, RenderStates states) const override;
    FloatRect getGlobalBounds();
private:
    Font theFont;
    RectangleShape buttonBackground;
    Text theText;
};


#endif //FINAL_PROJECT_BUTTON_H
