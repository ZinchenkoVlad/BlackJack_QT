#ifndef GAME_H
#define GAME_H

#include <QPropertyAnimation>
#include <QDialog>

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Game *ui;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QPropertyAnimation *animation3;
    QPropertyAnimation *animation4;
    QPropertyAnimation *animation5;
    QPropertyAnimation *animation6;
    QPropertyAnimation *animation21;
    QPropertyAnimation *animation22;
    QPropertyAnimation *animation23;
    QPropertyAnimation *animation24;
    QPropertyAnimation *animation25;
    QPropertyAnimation *animation26;
};

#endif // GAME_H
