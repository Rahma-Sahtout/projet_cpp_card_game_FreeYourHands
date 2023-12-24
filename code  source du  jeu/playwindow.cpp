#include "playwindow.h"
#include <QGuiApplication>
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QScreen>
#include <QRect>
#include<card.h>
#include <QLabel>
#include <QPoint>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <gameover.h>
PlayWindow::PlayWindow(bool EasyLevel ,QString image, QWidget *parent)
    : QMainWindow{parent}
{

    window = new QWidget(this);
    CardBack = image;

    window->setStyleSheet("background-color:#001C20");
    QScreen *Screen = QGuiApplication::primaryScreen();
    QRect ScreenBox = Screen->geometry();
    WindowHeight = ScreenBox.height();
    WindowWidth = ScreenBox.width();
     GameArea = new QWidget ;
    QHBoxLayout *GameBox = new QHBoxLayout(window);
    window->setFixedSize(WindowWidth,WindowHeight-70);
    QWidget *IAIcon = new QWidget(window);
    QWidget *PlayerIcon = new QWidget(window);
    IAIcon->setFixedSize(70,70);
    PlayerIcon->setFixedSize(64,70);
    IAIcon->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/IA.png); ");
    PlayerIcon->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/player1.png);");

     PlayerScore = new QLabel(window);
     IAScore = new QLabel(window);
    QLabel *PlayerName = new QLabel(window);
    QLabel *IAName = new QLabel(window);
    PlayerName->setText("User");
    IAName->setText("IA");
    PlayerName->setStyleSheet("color:#cba135;font-weight:bold; font-size:20px");
    IAName->setStyleSheet("color:#cba135;font-weight:bold; font-size:20px");
    PlayerScore->setStyleSheet("color:#cba135;font-weight:bold; font-size:20px");
    IAScore->setStyleSheet("color:#cba135;font-weight:bold; font-size:20px");

    this->EasyLevel = EasyLevel;
    PlayerScore->setText("0");
    IAScore->setText("0");
    // Positionnement des icônes en haut et en bas de la fenêtre
    QPoint IAIconPosition = QPoint((WindowWidth - IAIcon->width()) / 2,10);
    QPoint PlayerIconPosition = QPoint((WindowWidth - PlayerIcon->width()) / 2, WindowHeight - PlayerIcon->height()-70);
    IAIcon->move(IAIconPosition); // Centre en haut
    PlayerIcon->move(PlayerIconPosition);
    IAName->move(IAIconPosition.x() + IAIcon->width() + 20, IAIconPosition.y() + IAIcon->height() / 2 - IAName->height() / 2);
    IAScore->move(IAIconPosition.x() - 20 - 20, IAIconPosition.y() + IAIcon->height() / 2 - IAScore->height() / 2);

    // Positionnement des labels PlayerName et PlayerScore par rapport à PlayerIcon
    PlayerName->move(PlayerIconPosition.x() + PlayerIcon->width() + 20, PlayerIconPosition.y() + PlayerIcon->height() / 2 - PlayerName->height() / 2);
    PlayerScore->move(PlayerIconPosition.x() - 20 - 20, PlayerIconPosition.y() + PlayerIcon->height() / 2 - PlayerScore->height() / 2);




    //obtenier les coordonne des carte pour L'utilisateur et l'ia

    SetUserCardPosition ();
    SetIACardPosition ();





     GameCard = new QFrame(window) ;
    GameCard->setFixedSize(90,135);

     GameCard->setStyleSheet("background-image:url("+CardBack+");");
     GameArea->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/gamearea.png);");
    GameBox->setAlignment(Qt::AlignCenter);
    GameArea->setFixedSize(600,307);
    GameBox->addWidget(GameArea,1,Qt::AlignCenter);
    GameCard->move(40,(WindowHeight- 135 )/2 -30);
    IAIcon->raise();
    PlayerIcon->raise();





    //initialisation des 40 carte du jeux
    InitCard();
    Get4Card();
    //initialisation des score
      PlayerScoreNumber = 0  ;
      IAScoreNumber= 0 ;
      //Logique pour caculer les coordonner des Carte sur  la table de jeu
      SetMidllePosition();
     setCentralWidget(window);


}
void PlayWindow::Get4Card(){
     //animation des carte pour l'utilisateur
    MakeAnimation(true);

     //animation des carte pour l'Ia
    MakeAnimation(false);

    //initialiser le clik de l'utilisateur sur les carte
    User();


}
void PlayWindow ::SetMidllePosition(){
    QWidget *widget = new QWidget;
    QPropertyAnimation *animation = new QPropertyAnimation(widget,"pos");
    animation->setEndValue(QPoint(0,0));
    animation->setDuration(100);
    animation->start();
    connect(animation,&QPropertyAnimation::finished,this,[this]{
        //formule pour caluler et centre les Widgets sur le milieu de la table de jeu

        QPoint position = GameArea->mapToGlobal(QPoint(0, 0));
        int xCenter = position.x() + (GameArea->width() - 90 * 2) / 2 -60 ;
        int spacing = 200;
        int yCenter = position.y() + (GameArea->height() - 135) / 2;

        // Positionnement des widgets enfants
        UserCardPositionMiddle = QPoint(xCenter, yCenter);
        IACardPositionMiddle = QPoint(xCenter + spacing, yCenter);


    });
}
void PlayWindow::User(){
    /*fonction qui sert a connecter les clicks de l'utilisateur*/
    int size = UserCard.size();
    for(int i = 0;i<size;i++){
        connect(UserCard[i],&QPushButton::clicked,this,[this,i]{
            //code a executer lors du click sur une carte
            //desactiver le click de l'utilisateur car il vient de jouer
            UserCardClickActivation(false);
            GameAmination(UserCard[i],true ,i );

        });
    }
}
void PlayWindow::IA(){

    /* Fonction qui dirige les actions de l'IA.
     *  C'est une fonction simple qui prend aléatoirement l'une de ses cartes
     *  disponibles pour jouer. */

    int minValue = 0;  // Valeur minimale
    int maxValue = IACard.size()-1;  // Valeur maximale
    qDebug()<<"ce que Ia IaCard taille elet "<<IACard.size();


    int randomValue = QRandomGenerator::global()->bounded(minValue, maxValue + 1);
    qDebug()<<"nombre aleatoire "<<randomValue;
    //animer la carte jouer par l'ia
    GameAmination(IACard[randomValue],false ,randomValue);


}
void PlayWindow::GameAmination(Card *card ,bool ForUser,int index ){

    /* Fonction principale du jeu. Elle contrôle les
     *  animations des cartes de l'utilisateur et de l'IA.
     *  Elle donne également les tours de jeu de l'utilisateur et de l'IA. */


    //rendre les cartes visible pour les cartes cache de l'IA
    card->setStyleSheet("background-image:url("+card->CardImage+");");



    QPoint position = ForUser ? UserCardPositionMiddle : IACardPositionMiddle;
    QPropertyAnimation *animation = new QPropertyAnimation(card ,"pos");
    animation->setEndValue(position);
    card->raise();
    animation->setDuration(1300);
    animation->start();
    //deteriminer les numero des  cartes jouer par l'utilisateur et l'IA

    if(ForUser){
        UserPlayNumber = card->CardNumber;
        //indique que l'ia n'a pas encore jouer

         IAPlay = false;
    }else{
        IAPlayNumber = card->CardNumber;
        //indique que l'ia viens jouer
         IAPlay = true;


    }

    connect(animation,&QPropertyAnimation::finished,this,[this,card,index,ForUser]{
        //ajouter la carte a la liste des cartes jouer pour la liberation de la memoire
        ListePlayingCard.push_back(card);
        if(ForUser){
         }else{
            //tour de l'ia blocker les carte de l'utilisateur
            UserCardClickActivation(true);
            //suprimer les cartes de la liste des cartes de L'IA
            RemoveCard(IACard,index);



        }
        if(IACard.empty()){
            //vider les cartes de l'utilisateur pour aceillir de nouvelle carte

            UserCard.clear();
            //l'ia a jouer sa dernier carte lancement de 4 nouvelle cartes
            Get4Card();

        }


        if(IAPlay){
            //l'ia vient de jouer comparaison des carte et attributiion des score


            if(UserPlayNumber > IAPlayNumber){
                qDebug()<<"user gagne ";
                PlayerScoreNumber++;



            }else if(UserPlayNumber < IAPlayNumber) {
                qDebug()<<"ia gagne ";

                if(EasyLevel){
                    //niveau facile +1 point
                   IAScoreNumber++;
                }else{
                    //niveau difficile +2 point
                    IAScoreNumber++;
                    IAScoreNumber++;
                }



            }else{
                qDebug()<<"mathch null";
            }
            //mise a jour des scores a l'ecran de la fenetre de jeu
            UpdateScore();



            qDebug()<<"user score "<<PlayerScoreNumber;
            qDebug()<<"ia score "<<IAScoreNumber;

        }else {
            //ia n'a pas encore jouer
            //dire a l'Ia de jouer
          IA();

        }


    });


}
void PlayWindow::RemoveCard(std::vector<Card*>& cardVector, int index) {
    int taille = cardVector.size();
    /*fonction pour supprimer une carte de la liste des carte pour l'ia ou l'utilisateur*/

    if (index >= 0 && index < taille) {
        //suprimer la carte
        cardVector.erase(cardVector.begin() + index);


    } else {
        // index est invalide (en dehors des limites du vecteur)
        qDebug() << "L'index spécifié n'est pas valide.";
    }
}

void PlayWindow::UpdateScore(){
    /*fonction pour mettre a jour les scores sur la fenetre de jeu*/
    PlayerScore->setText(QString::number(PlayerScoreNumber));
    IAScore->setText(QString::number(IAScoreNumber));


}


void PlayWindow ::UserCardClickActivation(bool activation){
    //desativer le click de l'utilisateur pour eviter qu'il joue quand c'est pas sont tour
    int size = UserCard.size();
    for(int i = 0 ;i<size;i++){
        UserCard[i]->setEnabled(activation);
    }

}
void PlayWindow::MakeAnimation(bool ForUser ){
    /*fontion qui prend la liste des 40 carte enleve 4 carte  pour la distribuer a l'ia ou a l utilisateur */
     int size = ListOf40Card.size();
    qDebug()<<"la taille de ListOf40Card "<<size;
    if(size == 0 ){
        //la liste est vide le jeu est terminer

        if(PlayerScoreNumber >  IAScoreNumber){
            //jouer a gagner la partie
            //chargement de la page de fin du jeu
            GameOver *page = new GameOver(true,EasyLevel);
            setCentralWidget(page);
            this->update();
        }else{
            GameOver *page = new GameOver(false,EasyLevel);
            setCentralWidget(page);
            this->update();
        }
    }else{

        if(ForUser){
            /*animation de 4 carte */
            QPropertyAnimation *animation1 = new QPropertyAnimation(ListOf40Card[size-1],"pos");
            animation1->setDuration(1200);
            animation1->setStartValue(GameCard->pos());
            animation1->setEndValue(UserCardPoint[0]);
            animation1->start();
            QPropertyAnimation *animation2 = new QPropertyAnimation(ListOf40Card[size-2],"pos");
            animation2->setDuration(1200);
            animation2->setStartValue(GameCard->pos());
            animation2->setEndValue(UserCardPoint[1]);
            animation2->start();
            QPropertyAnimation *animation3 = new QPropertyAnimation(ListOf40Card[size-3],"pos");
            animation3->setDuration(1200);
            animation3->setStartValue(GameCard->pos());
            animation3->setEndValue(UserCardPoint[2]);
            animation3->start();
            QPropertyAnimation *animation4 = new QPropertyAnimation(ListOf40Card[size-4],"pos");
            animation4->setDuration(1200);
            animation4->setStartValue(GameCard->pos());
            animation4->setEndValue(UserCardPoint[3]);
            animation4->start();
            //on ajoute les carte au carte de l'utilisateur (4 carte)
            UserCard.push_back(ListOf40Card[size-1]);
            UserCard.push_back(ListOf40Card[size-2]);
            UserCard.push_back(ListOf40Card[size-3]);
            UserCard.push_back(ListOf40Card[size-4]);
            //connection des cartes des carte pour activer le click
            User();


        }else{
            //cacher les carte de l'IA durant la distribution des carte
            ListOf40Card[size-1]->setStyleSheet("background-image:url("+CardBack+");");
            ListOf40Card[size-2]->setStyleSheet("background-image:url("+CardBack+");");
            ListOf40Card[size-3]->setStyleSheet("background-image:url("+CardBack+");");
            ListOf40Card[size-4]->setStyleSheet("background-image:url("+CardBack+");");
            QPropertyAnimation *animation1 = new QPropertyAnimation(ListOf40Card[size-1],"pos");
            animation1->setDuration(1200);
            animation1->setStartValue(GameCard->pos());
            animation1->setEndValue(IACardPoint[0]);
            animation1->start();
            QPropertyAnimation *animation2 = new QPropertyAnimation(ListOf40Card[size-2],"pos");
            animation2->setDuration(1200);
            animation2->setStartValue(GameCard->pos());
            animation2->setEndValue(IACardPoint[1]);
            animation2->start();
            QPropertyAnimation *animation3 = new QPropertyAnimation(ListOf40Card[size-3],"pos");
            animation3->setDuration(1200);
            animation3->setStartValue(GameCard->pos());
            animation3->setEndValue(IACardPoint[2]);
            animation3->start();
            QPropertyAnimation *animation4 = new QPropertyAnimation(ListOf40Card[size-4],"pos");
            animation4->setDuration(1200);
            animation4->setStartValue(GameCard->pos());
            animation4->setEndValue(IACardPoint[3]);
            animation4->start();
            IACard.push_back(ListOf40Card[size-1]);
            IACard.push_back(ListOf40Card[size-2]);
            IACard.push_back(ListOf40Card[size-3]);
            IACard.push_back(ListOf40Card[size-4]);

        }
        //suppression des elements jouer
        ListOf40Card.pop_back();
        ListOf40Card.pop_back();
        ListOf40Card.pop_back();
        ListOf40Card.pop_back();
        qDebug()<<"taille de la liste"<<ListOf40Card.size();

    }



}

void PlayWindow ::SetUserCardPosition ( ){
    /*fontion qui utilise les coordonne de l'ecran pour calculer les position des carte de l'utilisateur pour faire les animations */

          const int cardSpacing = 10;
         //calcule du point de depart pour centre la liste des 4 carte par une formule de centrage des element
         int startValue = (WindowWidth - (4 * 90 + 4 * cardSpacing)) / 2;

         int i = 0;

          while ( i < 4) {
             //ajout dans la liste des 4 point
                 QPoint cardPositionTop(startValue + i * (90 + cardSpacing), WindowHeight -130 -135);
                 UserCardPoint.push_back(cardPositionTop);
             i++;
         }
          qDebug()<<"user point " <<UserCardPoint;



}

void PlayWindow ::SetIACardPosition (){

          /*fontion qui utilise les coordonne de l'ecran pour calculer les positions des cartes de l'ia pour faire les animation */
      int cardSpacing = 10;
           //calcule du point de depart pour centre la liste des 4 carte par une formule de centrage des element
         //position de depart pour centre les carte
         int startValue = (WindowWidth - (4 * 90 + 4 * cardSpacing)) / 2;

         int i = 0;

         while ( i < 4) {


             //ajout des 4 poisitions pour les cartes
             QPoint cardPositionBottom(startValue + i * (90 + cardSpacing),80 );  //Qpoint contenant les cordonne des different position pour
             IACardPoint.push_back(cardPositionBottom);
             qDebug()<<"liste des point de IACardPoint;"<<IACardPoint;

             i++;


         }

 qDebug()<<" iA carte " <<IACardPoint;
}
void PlayWindow::ShuffleCards() {
 /*fontion pour melanger les cartes */
 std::random_device rd;
 std::default_random_engine rng(rd());

 std::shuffle(ListOf40Card.begin(), ListOf40Card.end(), rng);


}
void PlayWindow::InitCard() {
 /*fonction pour initialiser la liste des 40 cartes */
 std::vector<int> cardNumbers = {1, 2, 3, 4, 5, 6, 7, 10, 11, 12};

 int index = 0;
 int i = 1 ;



 while (i <= 40) {
             if((i- 1) %10 == 0){
            /*condition lors que qu'on atteint 10 carte pour remettre le index a 0*/
                 index = 0;


             }
             int cardNumber = cardNumbers[index];

             Card* newCard = new Card(window);
             newCard->setFixedSize(90,135);//taille d'une carte
             newCard->move(-200,-200);//faire disparaitre les carte de l'ecran
             newCard->CardNumber = cardNumber;//QCoreApplication::applicationDirPath() chemin vers l'executable .exe
             newCard->CardImage = QCoreApplication::applicationDirPath() + QString("/images/%1.png").arg(i);//chemain absolue pour les carte

             newCard->setStyleSheet("background-image:url("+newCard->CardImage+");");//definition de l'image d arrier plan des carte

             ListOf40Card.push_back(newCard);//on ajoute a la liste des 40 carte


             index++;
             i++;
 }

//melanger les carte de la liste
 ShuffleCards();
 }
PlayWindow ::~PlayWindow(){
    //destructeur liberation de la memoire alouer

    while (ListePlayingCard.size() != 0) {

        int taille = ListePlayingCard.size();
        //selectionner le dernier element
        Card *temp = ListePlayingCard[taille-1];
        qDebug()<<"liberation memoire";
        ListePlayingCard.pop_back();
        delete temp;


    }
}
