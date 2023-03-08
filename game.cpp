#include "game.h"
#include "ui_game.h"
#include "card.h"


using namespace std;


Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    // Create backside card
    QPixmap pix(":/backSide/Assets/blue.png");
    ui -> imgBackCard -> setPixmap(pix.scaled(100, 170));


    Game::animationStart();




// Four startup cards
    // Get 1-st startup card for players
    QPixmap pix1(Game::pathToImageCreator(path1, path2));
    ui -> imgPlayer1 -> setPixmap(pix1.scaled(100, 170));
    Game::startAnimation(animation1, 20, 380);  // animation for player card 1
    // Get 2-nd startup card for players
    QPixmap pix2(Game::pathToImageCreator(path1, path2));
    ui -> imgPlayer2 -> setPixmap(pix2.scaled(100, 170));
    Game::startAnimation(animation2, 130, 380); // animation for player card 2

    // Get 1-s startup card for dealer
    QPixmap pix21(Game::pathToImageCreator(path1, path2));
    ui -> imgDealer1 -> setPixmap(pix21.scaled(100, 170));
    Game::startAnimation(animation21, 20, 20);  // animation for dealer card 1
    // Get 2-nd startup card for dealer
    QPixmap pix22(Game::pathToImageCreator(path1, path2));
    ui -> imgDealer2 -> setPixmap(pix22.scaled(100, 170));
    Game::startAnimation(animation22, 130, 20); // animation for dealer card 2





}
Game::~Game()
{
    delete ui;
}


// HIT BTN FOR PLAYER
int countOfPressHit = 1;
void Game::on_btnHit_clicked()
{

    // Draw cards for each click on HIT btn
    if(countOfPressHit == 1)
    {
        QPixmap pix3(Game::pathToImageCreator("card1/", "png1/"));
        ui -> imgPlayer3 -> setPixmap(pix3.scaled(100, 170));
        Game::startAnimation(animation3, 240, 380);
    }
    else if(countOfPressHit == 2)
    {
        QPixmap pix4(Game::pathToImageCreator("card1/", "png1/"));
        ui -> imgPlayer4 -> setPixmap(pix4.scaled(100, 170));
        Game::startAnimation(animation4, 350, 380);
    }
    else if(countOfPressHit == 3)
    {
        QPixmap pix5(Game::pathToImageCreator("card1/", "png1/"));
        ui -> imgPlayer5 -> setPixmap(pix5.scaled(100, 170));
        Game::startAnimation(animation5, 460, 380);
    }
    else if(countOfPressHit == 4)
    {
        QPixmap pix6(Game::pathToImageCreator("card1/", "png1/"));
        ui -> imgPlayer6 -> setPixmap(pix6.scaled(100, 170));
        Game::startAnimation(animation6, 570, 380);
    }

    countOfPressHit++;
    if(countOfPressHit > 4){
        ui->btnHit->setVisible(false);
    }
}

