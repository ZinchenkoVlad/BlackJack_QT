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
        pathToCardImg = pathToImageCreator(globalPathCard, isBackSide);
    }

    Card(std::tuple <QString, QString> cardname, QString globalPathCard, QString globalPathBackCard, bool isBackSide = false){
        this ->cardType = std::get<1>(cardname);
        this ->cardNum = std::get<0>(cardname);
        this ->isBackSide = isBackSide;
        this ->globalPathCard = globalPathCard;
        pathToCardImg = pathToImageCreator(globalPathCard, isBackSide, globalPathBackCard);
    }


    QString getPathToCardImg() const {
        return pathToCardImg;
    }

    QString getPathToBackCardImg() const {
        return pathToBackCardImg;
    }

    bool getIsBackSide() const {
        return this->isBackSide;
    }

    void setIsBackSide(bool isBackSide){
        this->isBackSide = isBackSide;
    }

    int giveNumOfPointsForCard(int playerPoints) const {
        int point = 0;
        int cardNum = this->cardNum.toInt();

        switch (cardNum) {
        case 11: point = 10; break;
        case 12: point = 10; break;
        case 13: point = 10; break;
        case 14: point = 11; break;

        default: point = cardNum; break;
        }

        if(point == 11 && playerPoints > 10){
            point = 1;
        }

        return point;
    }


private:
    QString globalPathCard = "png1/";

    QString pathToCardImg;
    QString pathToBackCardImg;
    QString cardType;
    QString cardNum;

    int numOfCardPoints;
    bool isBackSide;
    int numOfBackCardPoints;


    QString pathToImageCreator(const QString& path, bool isBackSide, const QString& backPath = "")
    {
        QString assetsDirectory = QDir::currentPath() + "/Assets/";

        if (isBackSide) {
            pathToBackCardImg = assetsDirectory + path + "/" + cardNum + "_of_" + cardType + ".png";
            return assetsDirectory + backPath;
        } else {
            return assetsDirectory + path + "/" + cardNum + "_of_" + cardType + ".png";
        }
    }

};

#endif // CARD_H
