#include "levelchoice.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QGuiApplication>
#include "playwindow.h"
#include "mainwindow.h"

LevelChoice::LevelChoice(QWidget *parent) : QMainWindow(parent) {
    QWidget *window = new QWidget(this);
    window->setStyleSheet("background-color:#001C20");

    QVBoxLayout *BoxHard = new QVBoxLayout;
    QVBoxLayout *BoxEasy = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout(window);

    QPushButton *EasyButton = new QPushButton("Facile", window);
    QPushButton *HardButton = new QPushButton("Difficile", window);
    QPushButton *BackButton = new QPushButton( window);

    QFrame *EasyImage = new QFrame(window);
    QFrame *HardImage = new QFrame(window);

    EasyImage->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/back_easy.png);");
     HardImage->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/back_hard.png);");
    EasyImage->setFixedSize(105, 150);
    HardImage->setFixedSize(105, 150);

    EasyButton->setFixedSize(105, 40);
    HardButton->setFixedSize(105, 40);

    EasyButton->setStyleSheet(
        "QPushButton {"
        "background-color: black;"
        "color: white;"
        "border: none;"
        "padding: 10px 20px;"
        "text-align: center;"
        "border-radius: 15px;"
        "font-size: 16px;"
        "}"

        "QPushButton:hover {"
        "background-color: #cba135;"
        "color: black;"
        "}"
        );

    HardButton->setStyleSheet(
        "QPushButton {"
        "background-color: black;"
        "color: white;"
        "border: none;"
        "padding: 10px 20px;"
        "text-align: center;"
        "border-radius: 15px;"
        "font-size: 16px;"
        "}"

        "QPushButton:hover {"
        "background-color: #cba135;"
        "color: black;"
        "}"
        );
    BackButton->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/fleche.png);outline:none;border:none");
    BackButton->setFixedSize(32,32);
    BackButton->move(20,20);

    container->setAlignment(Qt::AlignCenter);
    container->addLayout(BoxEasy);
    container->addSpacing(150);
    container->addLayout(BoxHard);

    BoxEasy->setAlignment(Qt::AlignHCenter);
    BoxHard->setAlignment(Qt::AlignHCenter);

    BoxEasy->addWidget(EasyImage);
    BoxEasy->addSpacing(20);
    BoxEasy->addWidget(EasyButton);

    BoxHard->addWidget(HardImage);
    BoxHard->addSpacing(20);
    BoxHard->addWidget(HardButton);

    connect(HardButton,&QPushButton::clicked,this,[this]{
        QString image = QGuiApplication::applicationDirPath()+"/images/back_hard.png";
        PlayWindow *page = new PlayWindow(false,image);
        setCentralWidget(page);
        this->update();
    });

        connect(EasyButton,&QPushButton::clicked,this,[this]{
        QString image = QGuiApplication::applicationDirPath()+"/images/back_easy.png";
        PlayWindow *page = new PlayWindow(true,image);
            setCentralWidget(page);
            this->update();
        });
    connect(BackButton,&QPushButton::clicked,this,[this]{
        MainWindow *page = new MainWindow;
            page->showMaximized();
        this->close();
    });


    setCentralWidget(window);
}
