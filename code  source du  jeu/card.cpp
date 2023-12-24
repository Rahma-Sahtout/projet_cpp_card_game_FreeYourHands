#include "card.h"
#include <QGuiApplication>
#include<algorithm>
#include <random>


Card::Card(QWidget *parent)
    : QPushButton{parent}
{
   CardBackImage = QCoreApplication::applicationDirPath() + QString("/images/back.png");
}

