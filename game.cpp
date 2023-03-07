#include "game.h"
#include "ui_game.h"
#include "card.h"
#include <ctime>

using namespace std;

int randomNumGenerator(){
    srand(time(0));
    return rand() % 13+2;    // generate a random number between 2 and 14 (inclusive)
}

QString imageCreator(QString num, QString type){
    QString s1{":/"};
    QString s2{"card1/"};
    QString s3{"Assets/"};
    QString s4{"png1/"};
    QString s5 = num;
    QString s6{"_of_"};
    QString s7 = type;
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


Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    // Get 2 startup cards for player
    int val = randomNumGenerator();
    QPixmap pix1(imageCreator(QString::number(val), "clubs"));
    ui -> imgPlayer1 -> setPixmap(pix1.scaled(100, 170));
    QPixmap pix2(imageCreator(QString::number(val), "clubs"));
    ui -> imgPlayer2 -> setPixmap(pix2.scaled(100, 170));




}

Game::~Game()
{
    delete ui;
}


// HIT BTN
int countOfPressHit = 1;
void Game::on_pushButton_clicked()
{


    int val = randomNumGenerator();

    Card b(val, false);


    ui->labelPlayer->setText(QString(b.getNumOfPointsQString()));



    // Draw pictures
    if(countOfPressHit == 1)
    {
        QPixmap pix3(imageCreator(QString::number(val), "diamonds"));
        ui -> imgPlayer3 -> setPixmap(pix3.scaled(100, 170));
    }
    else if(countOfPressHit == 2)
    {
        QPixmap pix4(imageCreator(QString::number(val), "clubs"));
        ui -> imgPlayer4 -> setPixmap(pix4.scaled(100, 170));
    }
    else if(countOfPressHit == 3)
    {
        QPixmap pix5(imageCreator(QString::number(val), "clubs"));
        ui -> imgPlayer5 -> setPixmap(pix5.scaled(100, 170));
    }
    else if(countOfPressHit == 4)
    {
        QPixmap pix6(imageCreator(QString::number(val), "clubs"));
        ui -> imgPlayer6 -> setPixmap(pix6.scaled(100, 170));
    }

    countOfPressHit++;
}

