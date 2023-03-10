#include <QApplication>
#include "gamewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget game;
    game.show();
    return a.exec();
}
