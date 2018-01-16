#include "Evenement.hh"

float VITESSE_SCROLLING;

// gestion temps apparition aléatoire obstacle
float borne_inf_obstacle;
float borne_sup_obstacle;
float DELAIS_APPARITION_OBSTACLE;

// gestion temps apparition aléatoire pièce
float borne_inf_piece;
float borne_sup_piece;
float DELAIS_APPARITION_PIECE;
// gestion temps apparition aléatoire ennemi1
float borne_inf_ennemi1;
float borne_sup_ennemi1;
float DELAIS_APPARITION_ennemi1;
// gestion temps apparition aléatoire missile
float DELAIS_MISSILE;

std::vector<Piece> liste_piece;
std::vector<Obstacle> liste_obstacle;
std::vector<Missile> liste_missile;
std::vector<Ennemi> liste_ennemi;

bool yoda_play; //Savoir si on a deja joué le son de yoda

// Pour afficher le score
unsigned long long score;


//Background Menu
Background Menu1("../Image/background_menu1.png",0,0);
Background Menu2("../Image/background_menu2.png",0,0);
Background Menu3("../Image/background_menu3.png",0,0);
Background Menu4("../Image/background_menu4.png",0,0);
Background Menu5("../Image/background_menu5.png",0,0);

//Background commande
Background Commande1("../Image/commande1.png",0,0);
Background Commande2("../Image/commande2.png",0,0);
Background Commande3("../Image/commande3.png",0,0);
Background Commande4("../Image/commande4.png",0,0);
Background Commande5("../Image/commande5.png",0,0);

//Background fin du jeu
Background Game_over("../Image/game_over.png");

//Background des fonds avec scrolling infini
Background Fond1("../Image/background_SW.png",VITESSE_SCROLLING,-800);
Background Fond2("../Image/background_SW.png",VITESSE_SCROLLING,-800);


//Obstacle
Obstacle obstacle1("../Image/cratere.png",VITESSE_SCROLLING);
Obstacle obstacle2("../Image/monstre_sable.png",VITESSE_SCROLLING);
Obstacle Vaisseau_fuite("../Image/vaisseau_fuite.png",VITESSE_SCROLLING);

//Piece
Piece piece("../Image/Bitcoin.png",VITESSE_SCROLLING);

//Ennemi
Ennemi ennemi1("../Image/r2d2.png",VITESSE_SCROLLING);
Ennemi ennemi2("../Image/c3po.png",VITESSE_SCROLLING);

//Missile
Missile missile_rouge("../Image/missile.png",0);

//Perso
Player Perso("../Image/ST1.png",1);



    // gestion du temps
    sf::Clock clock_obstacle;
    sf::Clock clock_piece;
    sf::Clock clock_ennemi;
    sf::Clock clock_missile;