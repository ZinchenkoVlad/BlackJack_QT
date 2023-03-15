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

    int getAmountOfMoney() const {
        return this ->amountOfMoney;
    }
    void setAmountOfMoney(int amountOfMoney){
        this ->amountOfMoney += amountOfMoney;
    }

    void setAmountOfBackPoints(int amountOfBackPoints){
        this ->amountOfBackPoints = amountOfBackPoints;
    }
    int getAmountOfBackPoints() const {
        return this ->amountOfBackPoints;
    }

    QString getPathToBackCardImg() const {
        return this ->pathToBackCardImg;
    }
    void setPathToBackCardImg(QString pathToBackCardImg){
        this ->pathToBackCardImg = pathToBackCardImg;
    }

    int getAmountOfPoints() const {
        return this ->amountOfPoints;
    }
    void setAmountOfPoints(int amountOfPoints){
        this ->amountOfPoints += amountOfPoints;
        if(!amountOfPoints){
            this ->amountOfPoints = amountOfPoints;
        }
    }

    int getPlayerBet() const {
        return this ->playerBet;
    }
    void setPlayerBet(int playerBet){
        this ->playerBet = playerBet;
    }

    bool checkLose(){
        return this->amountOfPoints > 21;
    }

};

#endif // PLAYER_H
