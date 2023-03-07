#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card
{
    bool isActive;
    bool cardBack;
    int cardNum;
    QString cardType;
    int numOfPoints;

public:
    Card(int cardNum, QString cardType, bool cardBack){
        this ->isActive = true;
        this ->cardBack = cardBack;

        this ->cardType = cardType;
        this ->cardNum = cardNum;
        this ->numOfPoints = giveNumOfPointsForCard(cardNum);
    }

    int getNumOfPointsInt(){
        return numOfPoints;
    }



private:
    int giveNumOfPointsForCard(int cardNum){
        int point = 0;

        switch (cardNum) {
        case 11: point = 10; break;
        case 12: point = 10; break;
        case 13: point = 10; break;

        default: point = cardNum; break;
        }

        if(cardNum == 14){
            // TODO
            point = 11;
        }

        return point;

    }
};

#endif // CARD_H
