#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <list>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QInputDialog>

#include "Player.h"
#include "Card.h"


namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);

    ~GameWidget();

private:
    Ui::GameWidget *ui; // Declare the ui member variable

    bool firstTime = true;
    std::list<QString> listOfUsedCards = {};
    int countOfPressHit = 1;

    void startGame();
    void reset();
    void initAnimation();
    void makeBet();
    std::tuple <QString, QString> randomCardGenerator();
    bool checkCardForUniqueness(QString card);
    void drawCard(Player* player, Card* temp, QLabel* labelCard, QLabel* labelScore, QPropertyAnimation* anim, int x, int y);
    void dealerMove();
    void gameOver(QString text);

private slots:
    void on_btnStand_clicked();
    void on_btnHit_clicked();

private:
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


#endif // GAMEWIDGET_H
