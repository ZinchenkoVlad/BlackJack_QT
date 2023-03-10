#ifndef CARD_H
#define CARD_H


class Card
{
    QString path1 = "/";
    QString path2 = "png1/";

    QString pathToCardImg;
    QString pathToBackCardImg;
    QString cardType;
    QString cardNum;
    int numOfCardPoints;
    bool isBackSide;
    int numOfBackCardPoints;

public:
    Card(std::tuple <QString, QString> cardname, bool isBackSide = false){
        this ->cardType = std::get<1>(cardname);
        this ->cardNum = std::get<0>(cardname);
        this ->isBackSide = isBackSide;
        this ->pathToCardImg = pathToImageCreator(path1, path2, isBackSide);

    }
    ~Card(){
//        qInfo() << this->getPathToCardImg();
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
    QString pathToImageCreator(QString s2, QString s4, bool isBackSide){ // s2, s4 for choosing diff image
        QString result;
        if(isBackSide){
            result = ":/back/Assets/png3/green_of_backside.png";
            this->pathToBackCardImg = ":/" + s2 + "Assets/" + s4 + cardNum + "_of_" + cardType + ".png";
        }
        else{
            result = ":/" + s2 + "Assets/" + s4 + cardNum + "_of_" + cardType + ".png";
        }

        return result;
    }



};

#endif // CARD_H
