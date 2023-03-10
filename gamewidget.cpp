#include "gamewidget.h"
#include "ui_gamewidget.h" // Include the generated header file for the UI

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::GameWidget), score(0)
{
    ui->setupUi(this); // Load the UI from the .ui file

    // Connect button signal to slot
    connect(ui->playAgainButton, &QPushButton::clicked, this, &GameWidget::handlePlayAgain);

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
    //reset();

    Player user(1000);
    Player dealer;

    initAnimation();

    Card a1(randomCardGenerator());
    Card a2(randomCardGenerator());
    Card a21(randomCardGenerator(), true);
    Card a22(randomCardGenerator());

    drawCard(&user, &a1, ui->labelPlayer1, ui->labelPlayerScore, animation1, 20, 380);
    drawCard(&user, &a2, ui->labelPlayer2, ui->labelPlayerScore, animation2, 130, 380);
    drawCard(&user, &a21, ui->labelDealer1, ui->labelDealerScore, animation21, 20, 20);
    drawCard(&user, &a22, ui->labelDealer2, ui->labelDealerScore, animation22, 130, 20);



    // TODO: Implement game logic here
    // ...


    // Game is over, enable button and show score
//    gameOver("Win");
}


void GameWidget::endGame()
{
    // Disable game elements and show play again button
    ui->playAgainButton->setEnabled(true);

    // Update score label

    ui->scoreLabel->setText(QString("Score: %1").arg(score));
}

void GameWidget::handlePlayAgain()
{
    // Start a new game
    startGame();
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
    if (temp->getIsBackSide())  player->setAmountOfPoints(0);
    else    player->setAmountOfPoints(temp->giveNumOfPointsForCard(player->getAmountOfPoints().toInt()));
    labelScore->setText(player->getAmountOfPoints());
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



// Buttons
void GameWidget::on_scoreBtn_clicked()
{
    score += score;
    ui->scoreLabel->setText(QString::number(score));

}
void GameWidget::on_endBtn_clicked()
{
    gameOver("Win");
    //endGame();
}


