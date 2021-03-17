//
// Created by jonng on 12/9/2020.
//

#include "BotBrain.h"

void BotBrain::beepBoop(CardHand &playerHand, CardHand &gameHand, Window &gameWindow, int &numOfCardsToPlace, int &valueOfLastCard, int &whoPlayedLast, int &whoTurnIsIt) {
    playerHand.sortBySuit();
    playerHand.sortByValue();
    playerHand.clearReservations();
    gameHand.clear();

    //If starting, just place 1 card down lol
    if(whoPlayedLast == whoTurnIsIt || whoPlayedLast == -1) {
        numOfCardsToPlace = 0;
        valueOfLastCard = 0;
        valueOfLastCard = Card::placeInOrderedDeck(playerHand.at(0).getBig2Value(), playerHand.at(0).getSuitInt());
        gameHand.push_back(playerHand.takeCardAt(0));
        whoPlayedLast = whoTurnIsIt;
        numOfCardsToPlace = 1;
    }
    //If replying, play smallest single, largest double, largest triple, or largest 5 card
    else {
        if(numOfCardsToPlace == 1) {
            for(int i = 0; i < playerHand.size(); i++) {
                if (Card::placeInOrderedDeck(playerHand.at(i).getBig2Value(),playerHand.at(i).getSuitInt()) >= valueOfLastCard) {
                    valueOfLastCard = Card::placeInOrderedDeck(playerHand.at(i).getBig2Value(),playerHand.at(i).getSuitInt());
                    whoPlayedLast = whoTurnIsIt;
                    gameHand.push_back(playerHand.takeCardAt(i));
                    break;
                }
            }
        }
        else if(numOfCardsToPlace == 2) {
            if (playerHand.findDoubles() > valueOfLastCard) {
                int counter(0);
                for (int i = playerHand.size()-1; i >= 0; i--) {
                    if (playerHand.at(i).getIsReserved() == 2) {
                        counter++;
                        if (counter == 1) {
                            valueOfLastCard = playerHand.findDoubles();
                            whoPlayedLast = whoTurnIsIt;
                        }
                        gameHand.push_back(playerHand.takeCardAt(i));
                        if (counter >= 2) {
                            break;
                        }
                    }
                }
            }
        }
        else if (numOfCardsToPlace == 3) {
            if (playerHand.findTriples() > valueOfLastCard) {
                int counter(0);
                for (int i = playerHand.size()-1; i >= 0; i--) {
                    if (playerHand.at(i).getIsReserved() == 3) {
                        counter++;
                        if (counter == 1) {
                            valueOfLastCard = playerHand.findTriples();
                            whoPlayedLast = whoTurnIsIt;
                        }
                        gameHand.push_back(playerHand.takeCardAt(i));
                        if (counter >= 3) {
                            break;
                        }
                    }
                }
            }
        }
        else if (numOfCardsToPlace == 5) {
            if (playerHand.findBest5CardHand() > valueOfLastCard) {
                int counter(0);
                for (int i = playerHand.size()-1; i >= 0; i--) {
                    if (playerHand.at(i).getIsReserved() == 5) {
                        counter++;
                        if (counter == 1) {
                            playerHand.clearReservations();
                            valueOfLastCard = playerHand.findBest5CardHand();
                            whoPlayedLast = whoTurnIsIt;
                        }
                        gameHand.push_back(playerHand.takeCardAt(i));
                        if (counter >= 5) {
                            break;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < gameHand.size(); i++) {
        gameHand.at(i).setIsRevealed(true);
    }
    switch(whoTurnIsIt) {
        case 0:
            for(int cardIndex = 0; cardIndex < playerHand.size(); cardIndex++) {
                playerHand.at(cardIndex).createSFMLCard();
            }
            for(int cardIndex = 0; cardIndex < gameHand.size(); cardIndex++) {
                gameHand.at(cardIndex).createSFMLCard();
            }
            break;
        case 1:
            for(int cardIndex = 0; cardIndex < playerHand.size(); cardIndex++) {
                playerHand.at(cardIndex).createLeft();
            }
            for(int cardIndex = 0; cardIndex < gameHand.size(); cardIndex++) {
                gameHand.at(cardIndex).createLeft();
            }
            break;
        case 2:
            for(int cardIndex = 0; cardIndex < playerHand.size(); cardIndex++) {
                playerHand.at(cardIndex).createSFMLCard();
            }
            for(int cardIndex = 0; cardIndex < gameHand.size(); cardIndex++) {
                gameHand.at(cardIndex).createSFMLCard();
            }
            break;
        case 3:
            for(int cardIndex = 0; cardIndex < playerHand.size(); cardIndex++) {
                playerHand.at(cardIndex).createRight();
            }
            for(int cardIndex = 0; cardIndex < gameHand.size(); cardIndex++) {
                gameHand.at(cardIndex).createRight();
            }
            break;
    }

    if(whoTurnIsIt == 3) {
        whoTurnIsIt = 0;
    }
    else {
        whoTurnIsIt++;
    }
}