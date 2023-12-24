#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H
#include <QWidget>
#include <card.h>
#include <QMainWindow>
#include <QFrame>
#include <QLabel>
class PlayWindow : public QMainWindow
{
    Q_OBJECT
public:
    PlayWindow(bool EasyLevel,QString image,QWidget *parent = nullptr);
    void SetUserCardPosition (  );
    void SetIACardPosition ( );
    void MakeAnimation(bool ForUser );
    void Get4Card();
    void User();
    void IA();
    void GameAmination(Card *card ,bool ForUser ,int index );
    void UserCardClickActivation(bool activation);
    void UpdateScore();
    void GameAminationIA(Card *card ,int index );
    void GameAminationUser(Card *card ,int index );
    void  InitCard();
    void  ShuffleCards();
    void SetMidllePosition();
    void RemoveCard(std::vector<Card*>& cardVector, int index);
    ~PlayWindow();


private :
    int WindowHeight;//la hauteur de l ecran du pc
    int WindowWidth ;//largeur
    QWidget *window ;//Objet QWidget de la fenetre
    QFrame *GameCard ;//distributeur des carte dans le jeu
    std::vector<QPoint> UserCardPoint;//cordonner des carte de l utilisateur
    std::vector<QPoint> IACardPoint;//cordonne des carte de L ia
    std::vector<Card*> ListOf40Card;//liste des 40 carte de l utilisateur
    std::vector<Card*> UserCard;//liste des carte de l'utilisateur
    std::vector<Card*> IACard;//liste des carte de l'ia
    QPoint UserCardPositionMiddle;//position des carte de l'utilisateur pour le centre
    QPoint IACardPositionMiddle;//position des carte de l'IA pour le centre
    QWidget  *GameArea ;//boite  blanche au milieu du jeux
    int UserPlayNumber =0;//le numero de la carte jouer par l'utilisateur
    int IAPlayNumber=0;//le numero de la carte jouer par l'IA
    bool IAPlay = false;//voir si l'IA a jouer

    QLabel *PlayerScore  ;//Label Qui affiche le score a l'ecran
    QLabel *IAScore ;//label qui affichele score de l IA a lecran
    int PlayerScoreNumber;//score de l'utilisateur
    int  IAScoreNumber ;//score de l 'IA
    std::vector<Card*> ListePlayingCard;//qui stock les cartes qui sont jouer
    bool EasyLevel;//variable de difficulter du jeu
    QString CardBack ; //image d'arriere plan pour les cartes



};

#endif // PLAYWINDOW_H
