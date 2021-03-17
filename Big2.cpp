//
// Created by jonng on 11/23/2020.
//

#include "Big2.h"

void Big2::run() {

    //Window Stuff
    sf::RenderWindow myWindow({960,960,32}, "Big 2!");
    myWindow.setFramerateLimit(165);

    //Declare splashscreen
    SplashScreen theSplash;
    bool startPressed(false);

    //Declare dot
    Light aDot;

    //Distribute cards
    Deck theDeck;
    theDeck.shuffle();
    CardHand demoCardHand;
    CardHand *playerCards = new CardHand[4];
    CardHand *gameHands = new CardHand[4];
    for(int i = 0; i < 52; i+=4) {
        for(int j = 0; j < 4; j++) {
            playerCards[j].push_back(theDeck.getCardOfDeck(i+j));
        }
    }

    //See who has the 3 of Diamonds
    int whoStarts(-1);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 13; j++) {
            if(playerCards[i].at(j).getSuitInt() == 0 && playerCards[i].at(j).getBig2Value() == 1) {
                whoStarts = i;
                break;
            }
        }
        if(whoStarts != -1) {
            break;
        }
    }

    //Declare buttons
    Button playButton("PLAY",95.f,myWindow.getSize().y-145.f,100,50);
    Button passButton("PASS", myWindow.getSize().x-95-100,myWindow.getSize().y-145,100,50);
    Button sortByValueBut("R", 10, myWindow.getSize().y - 10 - 50, 50, 50);
    Button sortBySuitBut("S",myWindow.getSize().x-10-50,myWindow.getSize().y-10-50,50,50);
    Button startButton("START", myWindow.getSize().x/2-125/2,myWindow.getSize().y/2-70/2,125,70);
    Button youWon("YOU WON :)",myWindow.getSize().x/2-200/2,myWindow.getSize().y/2-70/2,200,70);
    Button youLost("YOU LOST :(", myWindow.getSize().x/2-200/2,myWindow.getSize().y/2-70/2,200,70);


    //Declare variables
    int numOfCardsToPlace(0);
    int valueOfLastCard(0);
    int whoPlayedLast(-1);
    int whoTurnIsIt(whoStarts);
    bool gameOver(false);

    //Flip all the bots' cards over
    for (int botNum = 1; botNum < 4; botNum++) {
        for (int i = 0; i < 13; i++) {
            playerCards[botNum].at(i).setIsRevealed(false);
        }
    }

    //Window is now actionable!
    while(myWindow.isOpen())
    {

        sf::Event myEvent;
        while(myWindow.pollEvent(myEvent))
        {
            //Closes window when appropriate
            if(myEvent.type == sf::Event::Closed)
                myWindow.close();

            //Start Button Logic
            if(!startPressed) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2f mpos = (sf::Vector2f) sf::Mouse::getPosition(myWindow);

                    if(startButton.getGlobalBounds().contains(mpos))
                    {
                        startPressed = true;
                    }
                }
            }

            //Check if anybody won
            for (int i = 0; i < 4; i++) {
                if (playerCards[i].size() == 0) {
                    gameOver = true;
                }
            }
            //Resets window
            myWindow.clear({53,101,77});

            //Only runs when start button has been pressed
            if(startPressed && !gameOver) {

                switch(whoTurnIsIt) {
                    case 0:
                        aDot.setPosition(myWindow.getSize().x/2, myWindow.getSize().y-100);

                        //Will know if you played last
                        if(whoPlayedLast == 0) {
                            valueOfLastCard = 0;
                            numOfCardsToPlace = 0;
                        }
                        //Clear ur gameHand
                        gameHands[0].clear();

                        //Real player code selecting cards
                        for(int cardIndex = 0; cardIndex < playerCards[0].size(); cardIndex++) {

//                            //Draw cards
//                            playerCards[0].at(cardIndex).setCardPosition((myWindow.getSize().y-(playerCards[0].size()*60-10))/2+60*cardIndex,myWindow.getSize().y-85.f);
//                            myWindow.draw(playerCards[0].at(cardIndex));

                            //If mouse is clicked on cards
                            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                sf::Vector2f mpos = (sf::Vector2f) sf::Mouse::getPosition(myWindow);

                                if(playerCards[0].at(cardIndex).getGlobalBounds().contains(mpos))
                                {
                                    if(playerCards[0].at(cardIndex).getIsSelected())
                                        playerCards[0].at(cardIndex).setIsSelected(false);
                                    else
                                        playerCards[0].at(cardIndex).setIsSelected(true);
                                }
                            }
                        }

                        //If mouse is clicked on buttons
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            sf::Vector2f mpos = (sf::Vector2f) sf::Mouse::getPosition(myWindow);

                            //Sort by Value Button
                            if(sortByValueBut.getGlobalBounds().contains(mpos))
                            {
                                playerCards[0].sortByValue();
                            }

                            //Sort by Suit Button
                            if(sortBySuitBut.getGlobalBounds().contains(mpos))
                            {
                                playerCards[0].sortBySuit();
                            }

                            //Play Button
                            if(playButton.getGlobalBounds().contains(mpos))
                            {
                                bool isValid(false);
                                for(int cardIndex = playerCards[0].size()-1; cardIndex >= 0; cardIndex--) {
                                    if(playerCards[0].at(cardIndex).getIsSelected()) {
                                        gameHands[0].push_back(playerCards[0].takeCardAt(cardIndex));
                                    }
                                }

                                //Determine if hand is valid
                                //You start, any card size will do!
                                if(gameHands[0].empty());
                                else if(numOfCardsToPlace == 0 || whoPlayedLast == 0 || whoPlayedLast == -1) {

                                    if(gameHands[0].size() == 1) {
                                        isValid = true;
                                        valueOfLastCard = Card::placeInOrderedDeck(gameHands[0].at(0).getBig2Value(), gameHands[0].at(0).getSuitInt());
                                    }
                                    else if(gameHands[0].size() == 2) {
                                        if (gameHands[0].findDoubles()) {
                                            isValid = true;
                                            valueOfLastCard = gameHands[0].findDoubles();
                                        }
                                    }
                                    else if(gameHands[0].size() == 3) {
                                        if (gameHands[0].findTriples()) {
                                            isValid = true;
                                            valueOfLastCard = gameHands[0].findTriples();
                                        }
                                    }
                                    else if(gameHands[0].size() == 5) {
                                        if (gameHands[0].findBest5CardHand()) {
                                            isValid = true;
                                            gameHands[0].clearReservations();
                                            valueOfLastCard = gameHands[0].findBest5CardHand();
                                        }
                                    }
                                }
                                //You're playing somebody else's game
                                else {
                                    if (numOfCardsToPlace == 1) {
                                        if (Card::placeInOrderedDeck(gameHands[0].at(0).getBig2Value(), gameHands[0].at(0).getSuitInt())  > valueOfLastCard) {
                                            valueOfLastCard = Card::placeInOrderedDeck(gameHands[0].at(0).getBig2Value(), gameHands[0].at(0).getSuitInt());
                                            isValid = true;
                                        }
                                    } else if (numOfCardsToPlace == 2) {
                                        if (gameHands[0].findDoubles() > valueOfLastCard) {
                                            valueOfLastCard = gameHands[0].findDoubles();
                                            isValid = true;
                                        }
                                    } else if (numOfCardsToPlace == 3) {
                                        if (gameHands[0].findTriples() > valueOfLastCard) {
                                            valueOfLastCard = gameHands[0].findTriples();
                                            isValid = true;
                                        }
                                    } else if (numOfCardsToPlace == 5) {
                                        if (gameHands[0].findBest5CardHand() > valueOfLastCard) {
                                            valueOfLastCard = gameHands[0].findBest5CardHand();
                                            isValid = true;
                                        }
                                    }
                                }
                                if(isValid) {
                                    numOfCardsToPlace = gameHands[0].size();
                                    whoPlayedLast = 0;
                                    whoTurnIsIt = 1;
                                }
                                else { //You fucked up, count ur cards again lol
                                    for(int cardIndex = gameHands[0].size()-1; cardIndex >= 0; cardIndex--) {
                                        playerCards[0].push_back(gameHands[0].takeCardAt(cardIndex));
                                    }
                                }
                            }

                            //Pass button
                            if(passButton.getGlobalBounds().contains(mpos))
                            {
                                whoTurnIsIt = 1;
                            }
                        }
                        for(int cardIndex = 0; cardIndex < playerCards[0].size(); cardIndex++) {
                            playerCards[0].at(cardIndex).createSFMLCard();
                        }
                        for(int cardIndex = 0; cardIndex < gameHands[0].size(); cardIndex++) {
                            gameHands[0].at(cardIndex).createSFMLCard();
                        }
                        break;
                    case 1:
                        aDot.setPosition(100, myWindow.getSize().y/2);
                        BotBrain::beepBoop(playerCards[whoTurnIsIt], gameHands[whoTurnIsIt],myWindow, numOfCardsToPlace,valueOfLastCard, whoPlayedLast, whoTurnIsIt);
                        break;
                    case 2:
                        aDot.setPosition(myWindow.getSize().x/2, 100);
                        BotBrain::beepBoop(playerCards[whoTurnIsIt], gameHands[whoTurnIsIt],myWindow, numOfCardsToPlace,valueOfLastCard, whoPlayedLast, whoTurnIsIt);
                        break;
                    case 3:
                        aDot.setPosition(myWindow.getSize().x-100, myWindow.getSize().y/2);
                        BotBrain::beepBoop(playerCards[whoTurnIsIt], gameHands[whoTurnIsIt],myWindow, numOfCardsToPlace,valueOfLastCard, whoPlayedLast, whoTurnIsIt);
                        break;
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //Keep cards updated
                for(int cardIndex = 0; cardIndex < playerCards[0].size(); cardIndex++) {
                    playerCards[0].at(cardIndex).createSFMLCard();
                }
                for(int cardIndex = 0; cardIndex < gameHands[0].size(); cardIndex++) {
                    gameHands[0].at(cardIndex).createSFMLCard();
                }
                for(int cardIndex = 0; cardIndex < playerCards[1].size(); cardIndex++) {
                    playerCards[1].at(cardIndex).createLeft();
                }
                for(int cardIndex = 0; cardIndex < gameHands[1].size(); cardIndex++) {
                    gameHands[1].at(cardIndex).createLeft();
                }
                for(int cardIndex = 0; cardIndex < playerCards[2].size(); cardIndex++) {
                    playerCards[2].at(cardIndex).createSFMLCard();
                }
                for(int cardIndex = 0; cardIndex < gameHands[2].size(); cardIndex++) {
                    gameHands[2].at(cardIndex).createSFMLCard();
                }
                for(int cardIndex = 0; cardIndex < playerCards[3].size(); cardIndex++) {
                    playerCards[3].at(cardIndex).createRight();
                }
                for(int cardIndex = 0; cardIndex < gameHands[3].size(); cardIndex++) {
                    gameHands[3].at(cardIndex).createRight();
                }
            }

            //Waits for mouse activity to end (avoids multi-clicks)
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                cout << "Value: " << valueOfLastCard << "\n";
                cout << "NumCards: " << numOfCardsToPlace << "\n";
            }
            while(sf::Mouse::isButtonPressed(sf::Mouse::Right));

            //Draw all cardHands
            for(int cardIndex = 0; cardIndex < playerCards[0].size(); cardIndex++) {
                playerCards[0].at(cardIndex).setCardPosition((myWindow.getSize().y - (playerCards[0].size() * 60 - 10)) / 2 + 60 * cardIndex,myWindow.getSize().y - 85.f);
                myWindow.draw(playerCards[0].at(cardIndex));
            }
            for(int cardIndex = 0; cardIndex < gameHands[0].size(); cardIndex++) {
                gameHands[0].at(cardIndex).setCardPosition((myWindow.getSize().y-(gameHands[0].size()*60-10))/2+60*cardIndex,myWindow.getSize().y-85.f-200);
                myWindow.draw(gameHands[0].at(cardIndex));
            }
            for(int cardIndex = 0; cardIndex < playerCards[1].size(); cardIndex++) {
                playerCards[1].at(cardIndex).setCardPosition(10,myWindow.getSize().y-((myWindow.getSize().y-(playerCards[1].size()*60-10))/2)-60*cardIndex);
                myWindow.draw(playerCards[1].at(cardIndex));
            }
            for(int cardIndex = 0; cardIndex < gameHands[1].size(); cardIndex++) {
                gameHands[1].at(cardIndex).setCardPosition(10+200,myWindow.getSize().y-((myWindow.getSize().y-(gameHands[1].size()*60-10))/2)-60*cardIndex);
                myWindow.draw(gameHands[1].at(cardIndex));
            }
            for(int cardIndex = 0; cardIndex < playerCards[2].size(); cardIndex++) {
                playerCards[2].at(cardIndex).setCardPosition((myWindow.getSize().y-(playerCards[2].size()*60-10))/2+60*cardIndex,10);
                myWindow.draw(playerCards[2].at(cardIndex));
            }
            for(int cardIndex = 0; cardIndex < gameHands[2].size(); cardIndex++) {
                gameHands[2].at(cardIndex).setCardPosition((myWindow.getSize().y-(gameHands[2].size()*60-10))/2+60*cardIndex,10+200);
                myWindow.draw(gameHands[2].at(cardIndex));
            }
            for(int cardIndex = 0; cardIndex < playerCards[3].size(); cardIndex++) {
                playerCards[3].at(cardIndex).setCardPosition(myWindow.getSize().x-10,(myWindow.getSize().y-(playerCards[3].size()*60-10))/2+60*cardIndex);
                myWindow.draw(playerCards[3].at(cardIndex));
            }
            for(int cardIndex = 0; cardIndex < gameHands[3].size(); cardIndex++) {
                gameHands[3].at(cardIndex).setCardPosition(myWindow.getSize().x-10-200,(myWindow.getSize().y-(gameHands[3].size()*60-10))/2+60*cardIndex);
                myWindow.draw(gameHands[3].at(cardIndex));
            }

            //Draw buttons
            myWindow.draw(playButton);
            myWindow.draw(passButton);
            myWindow.draw(sortByValueBut);
            myWindow.draw(sortBySuitBut);
            myWindow.draw(aDot);
            if(gameOver) {
                if(playerCards[0].size() == 0) {
                    myWindow.draw(youWon);
                }
                else {
                    myWindow.draw(youLost);
                }
                myWindow.display();
            }
            while(gameOver) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    myWindow.close();
                    exit(0);
                }
            }

            //Splash Screen
            if(!startPressed) {
                myWindow.draw(theSplash);
                myWindow.draw(startButton);
            }

            //Display
            myWindow.display();
        }
    }
}


