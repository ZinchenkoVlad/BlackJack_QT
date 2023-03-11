#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    int amountOfPoints;
    int amountOfBackPoints;
    int amountOfMoney;
    int playerBet;

    QString pathToBackCardImg;

    Player(int amountOfMoney = 100){
        this ->amountOfMoney = amountOfMoney;
        this ->amountOfPoints = 0;
    }

    int getAmountOfMoney(){
        return this ->amountOfMoney;
    }
    void setAmountOfMoney(int amountOfMoney){
        this ->amountOfMoney += amountOfMoney;
    }

    void setAmountOfBackPoints(int amountOfBackPoints){
        this ->amountOfBackPoints = amountOfBackPoints;
    }
    int getAmountOfBackPoints(){
        return this ->amountOfBackPoints;
    }

    QString getPathToBackCardImg(){
         return this ->pathToBackCardImg;
    }
    void setPathToBackCardImg(QString pathToBackCardImg){
        this ->pathToBackCardImg = pathToBackCardImg;
    }

    QString getAmountOfPoints(){

        return QString::number(this ->amountOfPoints);
    }
    void setAmountOfPoints(int amountOfPoints){
        this ->amountOfPoints += amountOfPoints;
        if(!amountOfPoints){
            this ->amountOfPoints = amountOfPoints;
        }
    }

    int getPlayerBet(){
         return this ->playerBet;
    }
    void setPlayerBet(int playerBet){
        this ->playerBet = playerBet;
    }

    bool checkLoose(){
        if(this->amountOfPoints > 21){
            return true;
        }
        else
            return false;
    }

};

#endif // PLAYER_H
