#include "gamewidget.h"
#include "ui_gamewidget.h" // Include the generated header file for the UI

Player user(1000);
Player dealer;

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::GameWidget), score(0)
{
    ui->setupUi(this); // Load the UI from the .ui file

    // Start game
    startGame();
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::startGame()
{
    // Reset score and enable button
    reset();

    initAnimation();

    Card a1(randomCardGenerator());
    Card a2(randomCardGenerator());
    Card a21(randomCardGenerator(), true);
    dealer.setPathToBackCardImg(a21.getPathToBackCardImg());
    Card a22(randomCardGenerator());

    drawCard(&user, &a1, ui->labelPlayer1, ui->labelPlayerScore, animation1, 20, 380);
    drawCard(&user, &a2, ui->labelPlayer2, ui->labelPlayerScore, animation2, 130, 380);
    drawCard(&dealer, &a21, ui->labelDealer1, ui->labelDealerScore, animation21, 20, 20);
    drawCard(&dealer, &a22, ui->labelDealer2, ui->labelDealerScore, animation22, 130, 20);

    // hit btn is next
}

void GameWidget::reset(){
    countOfPressHit = 1;
    ui->labelPlayer1->clear();
    ui->labelPlayer2->clear();
    ui->labelPlayer3->clear();
    ui->labelPlayer4->clear();
    ui->labelPlayer5->clear();
    ui->labelPlayer6->clear();
    ui->labelDealer1->clear();
    ui->labelDealer2->clear();
    ui->labelDealer3->clear();
    ui->labelDealer4->clear();
    ui->labelDealer5->clear();
    ui->labelDealer6->clear();

    user.setAmountOfPoints(0);
    dealer.setAmountOfPoints(0);

    ui->labelDealerScore->setText(user.getAmountOfPoints());
    ui->labelPlayerScore->setText(user.getAmountOfPoints());

    ui->btnHit->setEnabled(true);
    ui->btnStand->setEnabled(true);

}

void GameWidget::gameOver(QString text){

    QMessageBox msgBox;
    QPushButton *connectButton = msgBox.addButton(tr("Play again"), QMessageBox::ActionRole);
    QPushButton *exitButton = msgBox.addButton(tr("Exit"), QMessageBox::ActionRole);
    msgBox.setWindowTitle("Result:");
    msgBox.setText(text);
    msgBox.setInformativeText("Try again :)");
    msgBox.exec();

    if (msgBox.clickedButton() == connectButton) {
        startGame();
    }
    else if (msgBox.clickedButton() == exitButton) {
        QCoreApplication::quit();
    }
}

void GameWidget::initAnimation(){
    animation1  = new QPropertyAnimation(ui->labelPlayer1, "geometry");
    animation2  = new QPropertyAnimation(ui->labelPlayer2, "geometry");
    animation3  = new QPropertyAnimation(ui->labelPlayer3, "geometry");
    animation4  = new QPropertyAnimation(ui->labelPlayer4, "geometry");
    animation5  = new QPropertyAnimation(ui->labelPlayer5, "geometry");
    animation6  = new QPropertyAnimation(ui->labelPlayer6, "geometry");
    animation21 = new QPropertyAnimation(ui->labelDealer1, "geometry");
    animation22 = new QPropertyAnimation(ui->labelDealer2, "geometry");
    animation23 = new QPropertyAnimation(ui->labelDealer3, "geometry");
    animation24 = new QPropertyAnimation(ui->labelDealer4, "geometry");
    animation25 = new QPropertyAnimation(ui->labelDealer5, "geometry");
    animation26 = new QPropertyAnimation(ui->labelDealer6, "geometry");
}

void GameWidget::drawCard(Player* player, Card* temp, QLabel* labelCard, QLabel* labelScore, QPropertyAnimation* anim, int x, int y){
    QPixmap pix(temp->getPathToCardImg());
    labelCard -> setPixmap(pix.scaled(100, 170));

    anim->setDuration(1000);
    anim->setStartValue(QRect(680, 200, 100, 170));
    anim->setEndValue(QRect(x, y, 100, 170));
    anim->start();

    // change score
    if (temp->getIsBackSide()){
        player->setAmountOfPoints(0);
        player->setAmountOfBackPoints(temp->giveNumOfPointsForCard(player->getAmountOfPoints().toInt()));

    }
    else{
        player->setAmountOfPoints(temp->giveNumOfPointsForCard(player->getAmountOfPoints().toInt()));
    }
    labelScore->setText(player->getAmountOfPoints());
}

std::tuple <QString, QString> GameWidget::randomCardGenerator(){
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
            flagExitFromLoop = checkCardForUniqueness(cardNum + cardType);
        }

    }while(!flagExitFromLoop);

    listOfUsedCards.push_back(cardNum + cardType);

    return {cardNum, cardType};
}

bool GameWidget::checkCardForUniqueness(QString card){
        //check list
        for (auto it = listOfUsedCards.begin(); it != listOfUsedCards.end(); ++it){
            if(*it == card){
                return false;
            }
        }
        return true;
    }

void GameWidget::dealerMove(){
    QPixmap pix(dealer.getPathToBackCardImg());
    ui->labelDealer1 -> setPixmap(pix.scaled(100, 170));

    dealer.setAmountOfPoints(dealer.getAmountOfBackPoints());
    ui->labelDealerScore->setText(dealer.getAmountOfPoints());

    int playerScore = user.getAmountOfPoints().toInt();
    int dealerScore = dealer.getAmountOfPoints().toInt();

    int iterations = 1;

    while(dealerScore < playerScore){
        if(iterations == 1){
            Card a23(randomCardGenerator());
            drawCard(&dealer, &a23, ui->labelDealer3, ui->labelDealerScore, animation23, 240, 20);
        }
        else if(iterations == 2){
            Card a24(randomCardGenerator());
            drawCard(&dealer, &a24, ui->labelDealer4, ui->labelDealerScore, animation24, 350, 20);
        }
        else if(iterations == 3){
            Card a25(randomCardGenerator());
            drawCard(&dealer, &a25, ui->labelDealer5, ui->labelDealerScore, animation25, 460, 20);
        }
        else if(iterations == 4){
            Card a26(randomCardGenerator());
            drawCard(&dealer, &a26, ui->labelDealer6, ui->labelDealerScore, animation26, 570, 20);
        }
        else break;
        iterations++;
        dealerScore = dealer.getAmountOfPoints().toInt();
    }
    if (dealerScore > playerScore && dealerScore > 21){
        gameOver("You WIN");
    }
    else if (dealerScore > playerScore && dealerScore <= 21){
        gameOver("You Loose");
    }
    else if (dealerScore == playerScore){
        gameOver("Draw");
    }
}



// Buttons
void GameWidget::on_btnStand_clicked()
{
    ui->btnHit->setEnabled(false);
    ui->btnStand->setEnabled(false);

    dealerMove();
}

void GameWidget::on_btnHit_clicked()
{
    // Draw cards for each click on HIT btn
    if(countOfPressHit == 1)
    {
        Card a3(randomCardGenerator());
        drawCard(&user, &a3, ui->labelPlayer3, ui->labelPlayerScore, animation3, 240, 380);
    }
    else if(countOfPressHit == 2)
    {
        Card a4(randomCardGenerator());
        drawCard(&user, &a4, ui->labelPlayer4, ui->labelPlayerScore, animation4, 350, 380);
    }
    else if(countOfPressHit == 3)
    {
        Card a5(randomCardGenerator());
        drawCard(&user, &a5, ui->labelPlayer5, ui->labelPlayerScore, animation5, 460, 380);
    }
    else if(countOfPressHit == 4)
    {
        Card a6(randomCardGenerator());
        drawCard(&user, &a6, ui->labelPlayer6, ui->labelPlayerScore, animation6, 570, 380);
    }

    countOfPressHit++;
    if(countOfPressHit > 4){
        ui->btnHit->setVisible(false);
    }
    if (user.checkLoose()){
        gameOver("You Loose");
    }
}

