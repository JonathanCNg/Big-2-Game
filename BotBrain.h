//
// Created by jonng on 12/9/2020.
//

#ifndef FINAL_PROJECT_BOTBRAIN_H
#define FINAL_PROJECT_BOTBRAIN_H
#include "Deck.h"
#include "CardHand.h"
#include "Button.h"
#include "SplashScreen.h"
#include "Light.h"

class BotBrain {
public:
    static void beepBoop(CardHand &playerHand, CardHand &gameHand, Window &gameWindow, int &numOfCardsToPlace, int &valueOfLastCard, int &whoPlayedLast, int &whoTurnIsIt);
};


#endif //FINAL_PROJECT_BOTBRAIN_H
