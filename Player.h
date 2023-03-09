#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    int amountOfPoints;
    int amountOfMoney;

    Player(int amountOfMoney = 100){
        this ->amountOfMoney = amountOfMoney;
        this ->amountOfPoints = 0;
    }

    int getAmountOfMoney(){
        return this ->amountOfMoney;
    }

    void getAmountOfMoney(int amountOfMoney){
        this ->amountOfMoney += amountOfMoney;
    }

    QString getAmountOfPoints(){

        return QString::number(this ->amountOfPoints);
    }

    void setAmountOfPoints(int amountOfPoints){
        this ->amountOfPoints += amountOfPoints;
    }

};







#endif // PLAYER_H
