#include "mainwindow.h"
#include <QApplication>
#include <QMediaPlayer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QMediaPlayer player;

    // Charger le fichier audio
    QString filePath = "C:/Users/ENVY/Desktop/free  your hands/song/bg_song.mp3";
    player.setSource(filePath);

    // Jouer la musique
    player.play();
    w.showMaximized();
    return a.exec();
}
