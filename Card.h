#ifndef CARD_H
#define CARD_H

#include <QString>

class Card
{

public:

    Card(std::tuple <QString, QString> cardname, QString globalPathCard, bool isBackSide = false){
        this ->cardType = std::get<1>(cardname);
        this ->cardNum = std::get<0>(cardname);
        this ->isBackSide = isBackSide;
        this ->globalPathCard = globalPathCard;
        this ->pathToCardImg = pathToImageCreator(globalPathCard, isBackSide);
    }

    Card(std::tuple <QString, QString> cardname, QString globalPathCard, QString globalPathBackCard, bool isBackSide = false){
        this ->cardType = std::get<1>(cardname);
        this ->cardNum = std::get<0>(cardname);
        this ->isBackSide = isBackSide;
        this ->globalPathCard = globalPathCard;
        this ->globalPathBackCard = globalPathBackCard;
        this ->pathToCardImg = pathToImageCreator(globalPathCard, isBackSide, globalPathBackCard);
    }


    QString getPathToCardImg(){
        return pathToCardImg;
    }

    QString getPathToBackCardImg(){
        return pathToBackCardImg;
    }

    bool getIsBackSide(){
        return this->isBackSide;
    }

    void setIsBackSide(bool isBackSide){
        this->isBackSide = isBackSide;
    }

    int giveNumOfPointsForCard(int playerPoints){
        int point = 0;
        int cardNum = this->cardNum.toInt();

        switch (cardNum) {
        case 11: point = 10; break;
        case 12: point = 10; break;
        case 13: point = 10; break;
        case 14: point = 11; break;

        default: point = cardNum; break;
        }

        if(point == 14 && playerPoints > 10){
            point = 1;
        }

        return point;
    }


private:
    QString globalPathCard = "png1/";
    QString globalPathBackCard = "back/";

    QString pathToCardImg;
    QString pathToBackCardImg;
    QString cardType;
    QString cardNum;

    int numOfCardPoints;
    bool isBackSide;
    int numOfBackCardPoints;


    QString pathToImageCreator(QString path, bool isBackSide, QString path2 = ""){

        QString result;
        QString saveDirectory = QDir::currentPath() + "/Assets/" + path + "/";
        QString saveDirectory1 = QDir::currentPath() + "/Assets/" + path2;

        if(isBackSide){
            this->pathToBackCardImg = saveDirectory + cardNum + "_of_" + cardType + ".png";
            result = saveDirectory1;
            qInfo() <<"/nInside card/t"<< result;
        }
        else{
            saveDirectory = QDir::currentPath() + "/Assets/" + path + "/";
            result = saveDirectory + cardNum + "_of_" + cardType + ".png";
        }
        return result;
    }

};

#endif // CARD_H
