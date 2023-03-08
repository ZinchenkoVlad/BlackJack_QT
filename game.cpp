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
    QPixmap pix(":/card3/Assets/png3/blue_of_backside.png");
    ui -> imgBackCard -> setPixmap(pix.scaled(100, 170));


    Game::animationStart();


// Four startup cards
    // Create startup card for players
    auto t3 = Game::randomCardGenerator();

    Card a1(get<0>(t3), get<1>(t3));
    t3 = Game::randomCardGenerator();
    Card a2(get<0>(t3), get<1>(t3));
    t3 = Game::randomCardGenerator();
    Card a21(get<0>(t3), get<1>(t3), true);
    t3 = Game::randomCardGenerator();
    Card a22(get<0>(t3), get<1>(t3));

    // Get 1-st startup card for player
    Game::getNewCardForPlayer(&a1, ui -> imgPlayer1);
    Game::startAnimation(animation1, 20, 380);  // animation for player card 1
    // Get 2-nd startup card for player
    Game::getNewCardForPlayer(&a2, ui -> imgPlayer2);
    Game::startAnimation(animation2, 130, 380); // animation for player card 2

    // Get 1-s startup card for dealer
    Game::getNewCardForPlayer(&a21, ui -> imgDealer1);
    Game::startAnimation(animation21, 20, 20);  // animation for dealer card 1
    // Get 2-nd startup card for dealer
    Game::getNewCardForPlayer(&a22, ui -> imgDealer2);
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
    auto t3 = Game::randomCardGenerator();

    // Draw cards for each click on HIT btn
    if(countOfPressHit == 1)
    {
        Card a3(get<0>(t3), get<1>(t3));
        Game::getNewCardForPlayer(&a3, ui -> imgPlayer3);
        Game::startAnimation(animation3, 240, 380);
    }
    else if(countOfPressHit == 2)
    {
        Card a4(get<0>(t3), get<1>(t3));
        Game::getNewCardForPlayer(&a4, ui -> imgPlayer4);
        Game::startAnimation(animation4, 350, 380);
    }
    else if(countOfPressHit == 3)
    {
        Card a5(get<0>(t3), get<1>(t3));
        Game::getNewCardForPlayer(&a5, ui -> imgPlayer5);
        Game::startAnimation(animation5, 460, 380);
    }
    else if(countOfPressHit == 4)
    {
        Card a6(get<0>(t3), get<1>(t3));
        Game::getNewCardForPlayer(&a6, ui -> imgPlayer6);
        Game::startAnimation(animation6, 570, 380);
    }

    countOfPressHit++;
    if(countOfPressHit > 4){
        ui->btnHit->setVisible(false);
    }
}

