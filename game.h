#ifndef GAME_H
#define GAME_H

#include <QPropertyAnimation>
#include <QDialog>
#include "ui_game.h"
#include "card.h"
#include <list>
#include <QRandomGenerator>
#include "Player.h"

using namespace std;


namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

    bool firstTime = true;
    list<QString> listOfUsedCards = {};


public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

private slots:
    void on_btnHit_clicked();

    void startAnimation(QPropertyAnimation* anim, int x, int y){
        anim->setDuration(1000);
        anim->setStartValue(QRect(680, 200, 100, 170));
        anim->setEndValue(QRect(x, y, 100, 170));
        anim->start();
    }

    void getNewCardForPlayer(Card* temp, QLabel* button){
        QPixmap pix3(temp->getPathToCardImg());
        button -> setPixmap(pix3.scaled(100, 170));
    }

    void changePointsForPlayer(Player* player, Card* temp, QLabel* label){
        player->setAmountOfPoints(temp->giveNumOfPointsForCard(player->getAmountOfPoints().toInt()));
        label->setText(player->getAmountOfPoints());
    }

    void animationStart(){
        animation1  = new QPropertyAnimation(ui->imgPlayer1, "geometry");
        animation2  = new QPropertyAnimation(ui->imgPlayer2, "geometry");
        animation3  = new QPropertyAnimation(ui->imgPlayer3, "geometry");
        animation4  = new QPropertyAnimation(ui->imgPlayer4, "geometry");
        animation5  = new QPropertyAnimation(ui->imgPlayer5, "geometry");
        animation6  = new QPropertyAnimation(ui->imgPlayer6, "geometry");
        animation21 = new QPropertyAnimation(ui->imgDealer1, "geometry");
        animation22 = new QPropertyAnimation(ui->imgDealer2, "geometry");
        animation23 = new QPropertyAnimation(ui->imgDealer3, "geometry");
        animation24 = new QPropertyAnimation(ui->imgDealer4, "geometry");
        animation25 = new QPropertyAnimation(ui->imgDealer5, "geometry");
        animation26 = new QPropertyAnimation(ui->imgDealer6, "geometry");
    }




    bool checkForUniqueness(QString card){

        //check list
        for (auto it = listOfUsedCards.begin(); it != listOfUsedCards.end(); ++it){
            if(*it == card){
                return false;
            }
        }

        return true;
    }


    tuple <QString, QString> randomCardGenerator(){
        QString cardType;
        QString cardNum;
        bool flagExitFromLoop = true; // for uniqueness do while

        do{
            cardNum = QString::number(QRandomGenerator::global()->bounded(2, 15)); // generate a random number between 2 and 14 (inclusive)

            switch (QRandomGenerator::global()->bounded(1, 5)) {
                case 1: cardType = "clubs"; break;
                case 2: cardType = "diamonds"; break;
                case 3: cardType = "hearts"; break;
                case 4: cardType = "spades"; break;
            }

            if (firstTime){// for first card
                firstTime = false;
                flagExitFromLoop = false;
            }
            else {
                flagExitFromLoop = checkForUniqueness(cardNum + cardType);
            }

        }while(!flagExitFromLoop);

        listOfUsedCards.push_back(cardNum + cardType);

        return {cardNum, cardType};
    }


private:
    Ui::Game *ui;

    QPropertyAnimation *animation1 ;
    QPropertyAnimation *animation2 ;
    QPropertyAnimation *animation3 ;
    QPropertyAnimation *animation4 ;
    QPropertyAnimation *animation5 ;
    QPropertyAnimation *animation6 ;
    QPropertyAnimation *animation21;
    QPropertyAnimation *animation22;
    QPropertyAnimation *animation23;
    QPropertyAnimation *animation24;
    QPropertyAnimation *animation25;
    QPropertyAnimation *animation26;
};

#endif // GAME_H
