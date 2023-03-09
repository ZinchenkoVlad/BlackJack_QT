#ifndef CARD_H
#define CARD_H


class Card
{
    QString path1 = "card1/";
    QString path2 = "png1/";
    QString pathToCardImg;
    QString cardType;
    QString cardNum;
    int numOfCardPoints;
    bool isBackSide;

public:
    Card(QString cardNum, QString cardType, bool isBackSide = false){
        this ->cardType = cardType;
        this ->cardNum = cardNum;
        this ->isBackSide = isBackSide;
        this ->pathToCardImg = pathToImageCreator(path1, path2, isBackSide, "black");

    }

    QString getPathToCardImg(){
        return pathToCardImg;
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

        default: point = cardNum; break;
        }

        if(cardNum == (int)14){
            if(playerPoints > 10){
                point = 1;
            }
            else {
                point = 11;
            }
        }

        return point;

    }

private:
    QString pathToImageCreator(QString s2, QString s4, bool isBackSide, QString x1 = "green"){ // s2, s4 for choosing diff image
        QString result;
        if(isBackSide){
            result = ":/card3/Assets/png3/" + x1 + "_of_backside.png";
        }
        else{
            result = ":/" + s2 + "Assets/" + s4 + cardNum + "_of_" + cardType + ".png";
        }

        return result;
    }



};

#endif // CARD_H
