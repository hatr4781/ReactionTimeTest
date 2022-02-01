/**
 * @file main.cpp
 * @author Ha Tran
 */

#include "reactiontimetest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReactionTimeTest w;
    w.show();
    return a.exec();
}
