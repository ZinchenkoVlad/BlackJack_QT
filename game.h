#ifndef GAME_H
#define GAME_H

#include <QPropertyAnimation>
#include <QDialog>
#include "ui_game.h"
#include "card.h"
#include <list>
#include <QRandomGenerator>

using namespace std;


namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

    bool firstTime = true;
    list<QString> listOfCardsOnDesk = {};


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


    tuple <QString, QString> randomCardGenerator(){
        QString str;
        int val, x;
        bool flag; // for uniqueness do while

        do{
            val = QRandomGenerator::global()->bounded(2, 15); // generate a random number between 2 and 14 (inclusive)
            x = QRandomGenerator::global()->bounded(1, 5);
            switch (x) {
                case 1:
                    str = "clubs";
                    break;
                case 2:
                    str = "diamonds";
                    break;
                case 3:
                    str = "hearts";
                    break;
                case 4:
                    str = "spades";
                    break;
            }

            if (firstTime){
                firstTime = false;
                flag = false;
            }
            else {  // for first card
                flag = checkForUniqueness(val, str);
            }
        }while(!flag);

        listOfCardsOnDesk.push_back(QString::number(val) + str);

        return {QString::number(val), str};
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
