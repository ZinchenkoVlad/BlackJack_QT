#include "game.h"
#include "ui_game.h"
#include "card.h"
#include <QRandomGenerator>
#include <tuple>
#include <list>


using namespace std;

list<QString> listOfCardsOnDesk = {};
bool firstTime = true;

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

        if (!firstTime){
            flag = checkForUniqueness(val, str);
        }
        else {  // fot first card
            firstTime = !firstTime;
            flag = false;
        }
    }while(!flag);

    listOfCardsOnDesk.push_back(QString::number(val) + str); // if is valid

    return {QString::number(val), str};
}

QString pathToImageCreator(){
    auto [x, y] = randomCardGenerator();

    QString s1{":/"};
    QString s2{"card1/"};
    QString s3{"Assets/"};
    QString s4{"png1/"};
    QString s5 = x;
    QString s6{"_of_"};
    QString s7 = y;
    QString s8{".png"};

    QString result;
    result.reserve(s1.length() + s2.length() + s3.length() + s4.length() + s5.length() + s6.length() + s7.length() + s8.length());
    result.append(s1);
    result.append(s2);
    result.append(s3);
    result.append(s4);
    result.append(s5);
    result.append(s6);
    result.append(s7);
    result.append(s8);

    return result;
}

void startAnimation(QPropertyAnimation* anim, int x, int y){
    anim->setDuration(2000);
    anim->setStartValue(QRect(680, 200, 100, 170));
    anim->setEndValue(QRect(x, y, 100, 170));
    anim->start();
}


Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    // Create backside card
    QPixmap pix(":/backSide/Assets/blue.png");
    ui -> imgBackCard -> setPixmap(pix.scaled(100, 170));

    // Get 2 startup cards for players
    QPixmap pix1(pathToImageCreator());
    ui -> imgPlayer1 -> setPixmap(pix1.scaled(100, 170));
    QPixmap pix2(pathToImageCreator());
    ui -> imgPlayer2 -> setPixmap(pix2.scaled(100, 170));

    // Get 2 startup cards for dealer
    QPixmap pix21(pathToImageCreator());
    ui -> imgDealer1 -> setPixmap(pix21.scaled(100, 170));
    QPixmap pix22(pathToImageCreator());
    ui -> imgDealer2 -> setPixmap(pix22.scaled(100, 170));

    animation1 = new QPropertyAnimation(ui->imgPlayer1, "geometry");
    animation2 = new QPropertyAnimation(ui->imgPlayer2, "geometry");
    animation3 = new QPropertyAnimation(ui->imgPlayer3, "geometry");
    animation4 = new QPropertyAnimation(ui->imgPlayer4, "geometry");
    animation5 = new QPropertyAnimation(ui->imgPlayer5, "geometry");
    animation6 = new QPropertyAnimation(ui->imgPlayer6, "geometry");
    animation21 = new QPropertyAnimation(ui->imgDealer1, "geometry");
    animation22 = new QPropertyAnimation(ui->imgDealer2, "geometry");
    animation23 = new QPropertyAnimation(ui->imgDealer3, "geometry");
    animation24 = new QPropertyAnimation(ui->imgDealer4, "geometry");
    animation25 = new QPropertyAnimation(ui->imgDealer5, "geometry");
    animation26 = new QPropertyAnimation(ui->imgDealer6, "geometry");

    startAnimation(animation1, 20, 380);
    startAnimation(animation21, 20, 20);
    startAnimation(animation2, 130, 380);
    startAnimation(animation22, 130, 20);



}

Game::~Game()
{
    delete ui;
}


// HIT BTN FOR PLAYER
int countOfPressHit = 1;
void Game::on_pushButton_clicked()
{

    // Draw pictures
    if(countOfPressHit == 1)
    {
        QPixmap pix3(pathToImageCreator());
        ui -> imgPlayer3 -> setPixmap(pix3.scaled(100, 170));
        startAnimation(animation3, 240, 380);
    }
    else if(countOfPressHit == 2)
    {
        QPixmap pix4(pathToImageCreator());
        ui -> imgPlayer4 -> setPixmap(pix4.scaled(100, 170));
        startAnimation(animation4, 350, 380);
    }
    else if(countOfPressHit == 3)
    {
        QPixmap pix5(pathToImageCreator());
        ui -> imgPlayer5 -> setPixmap(pix5.scaled(100, 170));
        startAnimation(animation5, 460, 380);
    }
    else if(countOfPressHit == 4)
    {
        QPixmap pix6(pathToImageCreator());
        ui -> imgPlayer6 -> setPixmap(pix6.scaled(100, 170));
        startAnimation(animation6, 570, 380);
    }

    countOfPressHit++;
    if(countOfPressHit > 4){
        ui->pushButton->setVisible(false);
    }
}

