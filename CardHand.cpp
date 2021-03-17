//
// Created by jonng on 11/30/2020.
//

#include "CardHand.h"

Card CardHand::takeCardAt(int cardIndex) {
    Card tempCard;
    tempCard = at(cardIndex);
    erase(cardIndex);
    return tempCard;
}
void CardHand::erase(int cardIndex) {
    CardHand tempCardHand = createCopy();
    clear();
    for(int i = 0; i < tempCardHand.size(); i++) {
        if (i != cardIndex)
            push_back(tempCardHand.at(i));
    }
}
void CardHand::sortByValue() {
    CardHand tempCardHand = createCopy();
    clear();
    for(int i = 1; i <= 13; i++) {
        for(int j = 0; j < tempCardHand.size(); j++)
        {
            if (tempCardHand.at(j).getBig2Value() == i) {
                push_back(tempCardHand.at(j));
            }
        }
    }
}
void CardHand::sortBySuit() {
    CardHand tempCardHand = createCopy();
    clear();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < tempCardHand.size(); j++)
        {
            if (tempCardHand.at(j).getSuitInt() == i)
                push_back(tempCardHand.at(j));
        }
    }
}

void CardHand::printAll(ostream& outs) {
    for (int i = 0; i < size(); i++) {
        outs << at(i) << std::endl;
    }
    outs << std::endl;
}
int CardHand::findTriples() {
    int isFound(false);
    //Record numbers
    int valuesOfEachSuit[4][14] = {0};
    for(int i = 0; i < size(); i++) {
        if (at(i).getIsReserved() != 5)
            valuesOfEachSuit[at(i).getSuitInt()][at(i).getBig2Value()]++;
    }
    //Reserve Cards
    for (int i = 1; i <= 13; i++) {
        if(valuesOfEachSuit[0][i] + valuesOfEachSuit[1][i] + valuesOfEachSuit[2][i] + valuesOfEachSuit[3][i] == 3) {
            isFound = i;
            for(int j = 0; j <= 3; j++) {
                if(valuesOfEachSuit[j][i])
                    accessCard(i,j)->setIsReserved(3);
            }
        }
    }
    return isFound;
}
int CardHand::findDoubles() {
    int isFound(false);
    int highestValue(0);
    int highestSuitOfThatValue(-1);
    //Record numbers
    int valuesOfEachSuit[4][14] = {0};
    for(int i = 0; i < size(); i++) {
        if (at(i).getIsReserved() != 3 && at(i).getIsReserved() != 5)
            valuesOfEachSuit[at(i).getSuitInt()][at(i).getBig2Value()]++;
    }
    //Reserve Cards
    for (int i = 1; i <= 13; i++) {
        if(valuesOfEachSuit[0][i] + valuesOfEachSuit[1][i] + valuesOfEachSuit[2][i] + valuesOfEachSuit[3][i] == 2) {
            highestValue = i;
            highestSuitOfThatValue = -1;
            for(int j = 0; j <= 3; j++) {
                if(valuesOfEachSuit[j][i]) {
                    accessCard(i,j)->setIsReserved(2);
                    highestSuitOfThatValue = j;
                }
            }
        }
    }
    isFound = Card::placeInOrderedDeck(highestValue,highestSuitOfThatValue);
    cout << "Double Value: " << isFound << endl;
    return isFound;
}
int CardHand::findBest5CardHand() {
    int temp(0);
    for (int i = 5; i >= 1; i--) {
        cout << i << " ";
        switch(i) {
            case 5: temp = findBestStraightFlush(); break;
            case 4: temp = findBest4OfAKind(); break;
            case 3: temp = findBestFullHouse(); break;
            case 2: temp = findBestFlush(); break;
            case 1: temp = findBestStraight(); break;
        }
        if (temp) {
            return temp;
        }
    }
    cout << "NONE :(\n";
    return temp;
}
int CardHand::findBestStraightFlush() {
    CardHand tempCardHand = createCopy();
    tempCardHand.sortByValue();
    tempCardHand.sortBySuit();

    //Find num of each suit
    int numOfEachSuit[4] = {0};
    for (int i = 0; i < tempCardHand.size(); i++) {
        numOfEachSuit[tempCardHand.at(i).getSuitInt()]++;
    }

    //Find values of suits seen 5 or more times
    int valuesOfEachSuit[4][14] = {0};
    for (int i = 0; i < 4; i++) {
        if(numOfEachSuit[i] >= 5) {
            for(int j = 0; j < tempCardHand.size(); j++) {
                if(at(j).getSuitInt() == i)
                    valuesOfEachSuit[i][at(j).getBig2Value()]++;
            }
        }
    }

//    //Print "valuesOfEachSuit"
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 14; j++) {
//            cout << valuesOfEachSuit[i][j] << " ";
//        }
//        cout << endl;
//    }

    //Find greatest straight flush
    int straightFlushPos(false); //0 if not found, 501-552 if found
    int straightFlushValue;
    int straightFlushSuit;
    for (int i = 3; i >= 0; i--) {
        if(numOfEachSuit[i] >= 5) {
            for(int j = 13; j >= 5; j--) {
                if(valuesOfEachSuit[i][j]) {
                    straightFlushPos = Card::placeInOrderedDeck(j,i) + 500;
                    straightFlushValue = j;
                    straightFlushSuit = i;
                    for(int k = 1; k <= 4; k++) {
                        if(!valuesOfEachSuit[i][j-k])
                            straightFlushPos = 0;
                    }
                    if (straightFlushPos)
                        break;
                }
            }
        }
        if (straightFlushPos)
            break;
    }

    //Reserve cards
//    cout << straightFlushValue << endl << straightFlushSuit << endl;
    if (straightFlushPos) {
        for(int i = 0; i < 5; i++) {
            accessCard(straightFlushValue-i,straightFlushSuit)->setIsReserved(5);
        }
    }
    return straightFlushPos;
}
int CardHand::findBest4OfAKind() {
    //Record values
    int valuesFound[14] = {0};
    for (int i = 0; i < size(); i++) {
        if (!at(i).getIsReserved())
            valuesFound[at(i).getBig2Value()]++;
    }
    //Look for quads, then change their reservation
    int quadValue(0);
    for (int i = 13; i >= 1; i--) {
        if (valuesFound[i] == 4) {
            for (int j = 0; j < 4; j++) {
                accessCard(i,j)->setIsReserved(5);
            }
            quadValue += 400 + i;
            break;
        }
    }
    if(quadValue) {
        findDoubles();
        CardHand tempCardHand = createCopy();
        tempCardHand.sortByValue();
        for (int i = 0; i < tempCardHand.size(); i++) {
            if(!tempCardHand.at(i).getIsReserved()) {
                accessCard(tempCardHand.at(i).getBig2Value(),tempCardHand.at(i).getSuitInt())->setIsReserved(5);
                break;
            }
        }
    }
    return quadValue;
}
int CardHand::findBestFullHouse() {
    int tripleValue(0);
    if(findTriples() && findDoubles()) {
        //Find values
        int valuesAndSuitsFound[4][14] = {0};
        for (int i = 0; i < size(); i++) {
            valuesAndSuitsFound[at(i).getSuitInt()][at(i).getBig2Value()]++;
        }
//        //Print "valuesOfEachSuit"
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j < 14; j++) {
//                cout << valuesAndSuitsFound[i][j] << " ";
//            }
//            cout << endl;
//        }
        //Reserve triple
        for (int i = 13; i >= 1; i--) {
            if(valuesAndSuitsFound[0][i] + valuesAndSuitsFound[1][i] + valuesAndSuitsFound[2][i] + valuesAndSuitsFound[3][i] == 3) {
                tripleValue = i + 300;
                for (int j = 3; j >= 0; j--) {
                    if(valuesAndSuitsFound[j][i]) {
                        accessCard(i,j)->setIsReserved(5);
                    }
                }
                break;
            }
        }
        //Reserve double
        for (int i = 1; i <= 13; i++) {
            if(valuesAndSuitsFound[0][i] + valuesAndSuitsFound[1][i] + valuesAndSuitsFound[2][i] + valuesAndSuitsFound[3][i] == 2) {
                for (int j = 0; j <= 3; j++) {
                    if(valuesAndSuitsFound[j][i]) {
                        accessCard(i,j)->setIsReserved(5);
                    }
                }
                break;
            }
        }
    }
    return tripleValue;
}
int CardHand::findBestFlush() {
    CardHand tempCardHand = createCopy();
    tempCardHand.sortByValue();
    tempCardHand.sortBySuit();

    //Find num of each suit
    int numOfEachSuit[4] = {0};
    for (int i = 0; i < tempCardHand.size(); i++) {
        numOfEachSuit[tempCardHand.at(i).getSuitInt()]++;
    }

    //Reserve the highest flush!
    int valueOfHighCard(0), numCardsReserved(0);
    for(int i = 3; i >= 0; i--) {
        if(numOfEachSuit[i] >= 5) {
            for(int j = tempCardHand.size()-1; j >= 0; j--) {
                if(numCardsReserved >= 5) {
                    break;
                }
                if(tempCardHand.at(j).getSuitInt() == i) {
                    accessCard(tempCardHand.at(j).getBig2Value(),i)->setIsReserved(5);
                    if(numCardsReserved == 0) {
                        valueOfHighCard = tempCardHand.at(j).getBig2Value() + 200;
                    }
                    numCardsReserved++;
                }
            }
        }
        if(numCardsReserved >= 5) {
            break;
        }
    }
    return valueOfHighCard;
}
int CardHand::findBestStraight() {
    CardHand tempCardHand = createCopy();
    tempCardHand.sortByValue();
    tempCardHand.sortBySuit();

    //Record numbers
    int valuesOfEachSuit[4][14] = {0};
    for(int j = 0; j < tempCardHand.size(); j++) {
        valuesOfEachSuit[at(j).getSuitInt()][at(j).getBig2Value()]++;
    }

    //Find highest card of straight
    int valueOfStraight(0);
    for(int i = 13; i >= 5; i--) {
        for(int j = 0; j < 5; j++) {
            if(valuesOfEachSuit[0][i-j] + valuesOfEachSuit[1][i-j] + valuesOfEachSuit[2][i-j] + valuesOfEachSuit[3][i-j] == 0)
                break;
            if(j == 4) { //Reserve the straight!
                valueOfStraight=i;
                for (int k = 0; k < 5; k++) {
                    for(int l = 3; l >= 0; l--) {
                        if(valuesOfEachSuit[l][valueOfStraight-k]) {
                            accessCard(valueOfStraight-k,l)->setIsReserved(5);
                            break;
                        }
                    }
                }
                return valueOfStraight + 100;
            }
        }
    }
    return 0;
}
ostream& operator << (ostream& outs, CardHand& aCardHand) {
    aCardHand.printAll(outs);
    return outs;
}
//void CardHand::operator = (CardHand& aCardHand) {
//    clear();
//    for (int i = 0; i < aCardHand.size(); i++) {
//        push_back(aCardHand.at(i));
//    }
//}
CardHand CardHand::createCopy() {
    CardHand tempCardHand;
    for (int i = 0; i < size(); i++) {
        tempCardHand.push_back(at(i));
    }
    return tempCardHand;
}
Card* CardHand::accessCard(int theValue, int theSuit) {
    for(int i = 0; i < size(); i++) {
        if (at(i).getBig2Value() == theValue && at(i).getSuitInt() == theSuit)
            return &at(i);
    }
    exit(39);
}
void CardHand::clearReservations() {
    for(int i = 0; i < size(); i++) {
        at(i).setIsReserved(0);
    }
}