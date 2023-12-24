#include "rules.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include "mainwindow.h"
#include <QGuiApplication>

Rules::Rules(QWidget *parent)
    : QMainWindow{parent}
{
    QWidget *mainWindow = new QWidget(this);
    this->setStyleSheet("background-color:#001C20");
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWindow);

    QLabel *titleLabel = new QLabel("Free Your Hands");
    titleLabel->setStyleSheet("color:#cba135;font-family:bold;font-size:20px");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    mainLayout->addSpacing(20);

    // Utilisez QTextEdit pour afficher le texte des règles
    QTextEdit *contentTextEdit = new QTextEdit;
    contentTextEdit->setStyleSheet("color:#cba135;font-size:18px; background-color: #001C20;otline:none;border:none");
    contentTextEdit->setReadOnly(true);
    contentTextEdit->setText("Il était une fois dans le pays magique de Libérez Vos Mains, un jeu mystique qui transportait les joueurs dans un voyage enchanteur de transformation. Imaginez être piégé à l'intérieur d'un œuf, attendant avec impatience de se libérer et de devenir un papillon magnifique !\n\n"
                                            "Dans ce jeu, chaque joueur, l'utilisateur et l'IA, commençait avec 4 cartes. Le but était de jouer une carte sur la table, et celui avec le nombre le plus élevé sur sa carte remportait le tour.\n\n"
                                            "Pour la difficulté facile, l'IA et l'utilisateur commençaient avec le même nombre de points. Remporter un tour accordait un point.\n"
                                            "Cependant, pour le mode difficile, lorsque l'IA sortait victorieuse d'un tour, elle s'élevait plus haut, gagnant 2 points, tandis que l'utilisateur n'en gagnait qu'1.\n\n"
                                            "Alors que les joueurs se préparaient à embarquer dans leur aventure métamorphique, ils mélangeaient leurs paquets, permettant à la magie de s'infiltrer dans chaque carte. Le paquet était ensuite divisé en deux parties égales, avec 20 cartes pour chaque joueur.\n\n"
                                            "Avec de l'anticipation dans l'air, les joueurs tiraient leur première carte, la révélant au monde. La carte, comme un papillon émergeant de sa chrysalide, voltigeait sur la table, face visible pour tous. Le joueur avec la carte de rang le plus élevé ressentait une montée d'excitation en revendiquant la victoire, collectant les deux cartes comme symbole de leur triomphe.\n\n"
                                            "Mais méfiez-vous, car même dans ce royaume mystique, il existait la possibilité d'une égalité. Lorsque deux cartes de rang égal se rencontraient, un sentiment d'équilibre s'installait parmi les joueurs, et aucune carte n'était remportée. C'était un moment de suspense, où le destin jouait sa main mystérieuse.\n"
                                            "Le jeu continuait, tour après tour, avec les joueurs luttant pour la suprématie. Chaque carte jouée était un pas de plus vers la victoire, un pas de plus vers devenir le papillon ultime. La bataille faisait rage jusqu'à ce qu'un joueur émergeât en tant que véritable champion, ayant rassemblé toutes les cartes en sa possession.\n"
                                            "Et ainsi, le conte de Libérez Vos Mains prit fin, le joueur victorieux se prélassant dans la gloire de son voyage métamorphique. Le jeu avait apporté joie, excitation et une touche de magie à tous ceux qui osaient jouer.\n"
                                            "Maintenant, mon ami, êtes-vous prêt à vous lancer dans votre propre aventure dans le monde de Libérez Vos Mains ? Laissez les cartes vous guider alors que vous déployez vos ailes et embrassez la transformation qui vous attend !");

    // Ajustez la hauteur minimale pour assurer la visibilité du texte
    contentTextEdit->setMinimumHeight(600);
    contentTextEdit->setMinimumWidth(800);

    // Ajoutez QTextEdit au layout
    mainLayout->addWidget(contentTextEdit, 0, Qt::AlignCenter);


    QPushButton *backButton = new QPushButton(mainWindow);
    backButton->setFixedSize(32, 32);
    backButton->move(40, 40);
    backButton->setStyleSheet("background-image:url(" + QGuiApplication::applicationDirPath() + "/images/fleche.png);outline:none;border:none");

    connect(backButton, &QPushButton::clicked, this, [this] {
        MainWindow *levelWindow = new MainWindow;
        levelWindow->showMaximized();
        this->close();
    });

    setCentralWidget(mainWindow);
}
