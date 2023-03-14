#ifndef CARD_H
#define CARD_H

#include <QString>

class Card
{

public:
    Card(std::tuple <QString, QString> cardname, bool isBackSide = false){
        this ->cardType = std::get<1>(cardname);
        this ->cardNum = std::get<0>(cardname);
        this ->isBackSide = isBackSide;
        this ->pathToCardImg = pathToImageCreator(path2, isBackSide);

    }

    Card(std::tuple <QString, QString> cardname, QString path2, bool isBackSide = false){
        this ->cardType = std::get<1>(cardname);
        this ->cardNum = std::get<0>(cardname);
        this ->isBackSide = isBackSide;
        this ->path2 = path2;
        this ->pathToCardImg = pathToImageCreator(path2, isBackSide);
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
    QString path2 = "png1/";

    QString pathToCardImg;
    QString pathToBackCardImg;
    QString cardType;
    QString cardNum;


    int numOfCardPoints;
    bool isBackSide;
    int numOfBackCardPoints;


    QString pathToImageCreator(QString s4, bool isBackSide){ // s2, s4 for choosing diff image
        qInfo() << s4;
        QString result;
        if(isBackSide){
            result = ":/back/Assets/png3/green_of_backside.png";
            this->pathToBackCardImg = "://Assets/" + s4 + cardNum + "_of_" + cardType + ".png";
        }
        else{
//            result = "://Assets/" + s4 + cardNum + "_of_" + cardType + ".png";
            QString saveDirectory = QDir::currentPath() + "/Assets/" + s4 + "/";
            result = saveDirectory + cardNum + "_of_" + cardType + ".png";
        }

        return result;
    }




};

#endif // CARD_H
