#include "gameover.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGuiApplication>
#include "playwindow.h"
#include "levelchoice.h"
GameOver::GameOver(bool winner,bool Dificulty, QWidget *parent)
    : QMainWindow{parent}
{

    this->setStyleSheet("background-color:#001C20");
    QWidget *mainWindow = new QWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWindow);
    QHBoxLayout *buttonLayout = new QHBoxLayout(mainWindow);

    QPushButton *replayButton = new QPushButton("play again");
    QPushButton *dificultieButton = new QPushButton("Difficulty page");

    replayButton->setFixedSize(124, 40);
    dificultieButton->setFixedSize(124, 40);

    QString buttonStyle = "QPushButton {"
                          "    background-color: black;"
                          "    color: white;"
                          "    border-radius: 15px;"
                          "    border: none;"
                          "}"

                          "QPushButton:hover {"
                          "    background-color: #cba135;"
                          "    color: white;"
                          "}"

                          "QPushButton:pressed {"
                          "    background-color: black;"
                          "    color: black;"
                          "}";

    replayButton->setStyleSheet(buttonStyle);
    dificultieButton->setStyleSheet(buttonStyle);

    QFrame *Image = new QFrame;


    QLabel *resultText = new QLabel(mainWindow);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(Image, 0, Qt::AlignCenter);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(resultText, 0, Qt::AlignCenter);

    if (winner) {
        Image->setStyleSheet("background-image:url(" +QGuiApplication::applicationDirPath()+ "/images/winner.png);");
        resultText->setText("You've Set your hands free ");


            Image->setFixedSize(338, 338);
    } else {
        Image->setStyleSheet("background-image:url(" + QGuiApplication::applicationDirPath() + "/images/loser.png);");
        resultText->setText("oh no, your hands are still trapped! ");
        Image->setFixedSize(280, 392);
     }

    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(replayButton);
    buttonLayout->addSpacing(60);
    buttonLayout->addWidget(dificultieButton);

    resultText->setStyleSheet("color:#cba135;font-size:30px;font-weight:bold;");

    connect(dificultieButton, &QPushButton::clicked, this, [this] {
        LevelChoice *level = new LevelChoice;
        setCentralWidget(level);
        this->update();
    });

    connect(replayButton, &QPushButton::clicked, this, [this,Dificulty] {
        QString image;
        if(Dificulty){
            image =  QGuiApplication::applicationDirPath()+"/images/back_easy.png";
        }else{
            image =  QGuiApplication::applicationDirPath()+"/images/back_hard.png";

        }

        PlayWindow *play = new PlayWindow(true,image);
        setCentralWidget(play);
        this->update();
    });

    setCentralWidget(mainWindow);



}
