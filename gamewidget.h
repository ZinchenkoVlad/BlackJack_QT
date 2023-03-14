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
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileDialog>
#include <QResource>

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

    QString path2 = "png1";
    ~GameWidget();

private:
    Ui::GameWidget *ui; // Declare the ui member variable

    bool firstTime = true;
    std::list<QString> listOfUsedCards = {};
    int countOfPressHit = 1;
    int playerStartupBet = 25;
    QStringList listCardFrontTypes;


    void startGame();
    void soundPlayer(QString path);
    void reset();
    void initAnimation();
    void makeBet();
    std::tuple <QString, QString> randomCardGenerator();
    void drawCard(Player* player, Card* temp, QLabel* labelCard, QLabel* labelScore, QPropertyAnimation* anim, int x, int y);
    void timer(int time);
    void dealerMove();
    void gameOver(QString text);
    void checkListCardFrontTypes();


private slots:
    void on_btnStand_clicked();
    void on_btnHit_clicked();

    void on_btnAddNewSkins_clicked();
    void on_btnChangeSkins_clicked();

private:
    QPropertyAnimation* animation1 ;
    QPropertyAnimation* animation2 ;
    QPropertyAnimation* animation3 ;
    QPropertyAnimation* animation4 ;
    QPropertyAnimation* animation5 ;
    QPropertyAnimation* animation6 ;
    QPropertyAnimation* animation21;
    QPropertyAnimation* animation22;
    QPropertyAnimation* animation23;
    QPropertyAnimation* animation24;
    QPropertyAnimation* animation25;
    QPropertyAnimation* animation26;

    QMediaPlayer* backgroundMusic;
    QAudioOutput* audioOutput1;
    QMediaPlayer* music;
    QAudioOutput* audioOutput;
};


#endif // GAMEWIDGET_H
