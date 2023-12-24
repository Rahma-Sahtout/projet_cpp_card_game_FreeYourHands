#include "mainwindow.h"
#include<QWidget>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QPoint>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QCoreApplication>
 #include "levelchoice.h"
#include "rules.h"
#include <QAudioOutput>
#include <QGuiApplication>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
     window = new QWidget(this);
    //initialisation de la musique d'arriere plan
     QString filePath = QCoreApplication::applicationDirPath() + "/song/bg_song.mp3";
     musicPlayer.setSource(QUrl::fromLocalFile(filePath));
     musicPlayer.setAudioOutput(new QAudioOutput);

     //signal pour detecter si la musique touche a sa fin

     musicPlayer.play();

    QScreen *Screen = QGuiApplication::primaryScreen();
    QRect ScreenBox = Screen->geometry();
    WindowHeight = ScreenBox.height();
    WindowWidth = ScreenBox.width();
    window->setStyleSheet("background-color:#001C20");
    QVBoxLayout *container = new QVBoxLayout(window);
    QFrame *bg_image = new QFrame (window);//image arriere plan
     QLabel *GameName = new QLabel(window);
    GameName->setText("Free Your Hands");
    GameName->setFixedSize(240,30);
    GameName->setStyleSheet(
        "font-weight :bold; font-size:30px;color:#cba135;background-color:transparent");

    bg_image->setStyleSheet("background-image :url("+QGuiApplication::applicationDirPath()+"/images/back_bg.png"+");");
    bg_image ->setFixedSize(481,518);
    QPushButton *PlayButton = new QPushButton("Play");
 container->addWidget(GameName,0,Qt::AlignCenter);
    container->addSpacing(20);



     container->addWidget(bg_image,1, Qt::AlignCenter);
    container->addSpacing(20);
    QPushButton *RegleJeu = new QPushButton("Rules");
     RegleJeu->setFixedSize(200,50);

     RegleJeu->setStyleSheet("QPushButton {"
                         "background-color: black; /* Couleur d'arrière-plan */"
                         "color: white; /* Couleur du texte */"
                         " border: none; /* Pas de bordure */"
                         "padding: 10px 20px; /* Espacement intérieur */"
                         "text-align: center; /* Alignement du texte */"
                         "border-radius: 15px; /* Bords arrondis */"
                         "font-size: 16px; /* Taille de la police */"
                         "}"

                         "QPushButton:hover {"
                         "background-color: #cba135; /* Couleur d'arrière-plan lors du survol */"
                         "color: black; /* Couleur du texte lors du survol */"
                         "}"
                         ");");
     container->addWidget(RegleJeu,0,Qt::AlignCenter);
     container->addSpacing(20);
    container->addWidget(PlayButton,0,Qt::AlignCenter);

    //boutton play
    PlayButton->setStyleSheet("QPushButton {"
                              "background-color: black; /* Couleur d'arrière-plan */"
                              "color: white; /* Couleur du texte */"
                              " border: none; /* Pas de bordure */"
                              "padding: 10px 20px; /* Espacement intérieur */"
                              "text-align: center; /* Alignement du texte */"
                              "border-radius: 15px; /* Bords arrondis */"
                              "font-size: 16px; /* Taille de la police */"
                              "}"

                              "QPushButton:hover {"
                              "background-color: #cba135; /* Couleur d'arrière-plan lors du survol */"
                              "color: black; /* Couleur du texte lors du survol */"
                              "}"
                              ");");
    PlayButton->setFixedSize(200,50);


    connect(PlayButton ,&QPushButton::clicked,this,[this]{
        MainWindow::buttonClick();
    });
    connect(RegleJeu ,&QPushButton::clicked,this,[this]{
        Rules *page = new Rules;
        page->showMaximized();
            this->close();
    });






    setCentralWidget(window);



}

void MainWindow :: buttonClick(){
    LevelChoice * pageSuivante = new LevelChoice();
    setCentralWidget(pageSuivante);
    this->update();
}


