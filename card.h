#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <list>

using namespace std;

class Card
{
    list<QString> listOfCardsOnDesk = {};
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

    bool checkForUniqueness(int cardNum, QString cardType){
        QString str = QString::number(cardNum) + cardType;

        //check list
        for (auto it = listOfCardsOnDesk.begin(); it != listOfCardsOnDesk.end(); ++it){
                if(*it == str){
                    return false;
                }
        }

        return true;
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
