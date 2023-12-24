#ifndef CARD_H
#define CARD_H

#include <QPushButton>

class Card : public QPushButton
{
    Q_OBJECT
public:
     Card(QWidget *parent = nullptr);
    /*proprieter dune carte */
    int CardNumber ;
    QString CardImage;
    QString CardBackImage= "/images/back.png";






};

#endif // CARD_H
