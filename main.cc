#include "Evenement.hh"




using namespace std;

 float VITESSE_SCROLLING;

// gestion temps apparition aléatoire obstacle
 float borne_inf_obstacle;
 float borne_sup_obstacle;
 float DELAIS_APPARITION_OBSTACLE;

// gestion temps apparition aléatoire pièce
 float borne_inf_piece;
 float borne_sup_piece;
 float DELAIS_APPARITION_PIECE;
// gestion temps apparition aléatoire r2d2
 float borne_inf_r2d2;
 float borne_sup_r2d2;
 float DELAIS_APPARITION_R2D2;
// gestion temps apparition aléatoire missile
 float DELAIS_MISSILE;

// à effacer plus tard
 bool stop;

 vector<Piece> liste_piece;
 vector<Obstacle> liste_obstacle;
 vector<Missile> liste_missile;
 vector<Ennemi> liste_ennemi;

// Pour afficher le score
unsigned long long score;

int main()
{

    srand(time(0));
 // Initialisation des variables globales
  VITESSE_SCROLLING = 3.0;

// gestion temps apparition aléatoire obstacle
  borne_inf_obstacle = 0.05;
  borne_sup_obstacle = SCREEN_HEIGHT/(VITESSE_SCROLLING*60.0*10.0)-borne_inf_obstacle;
  DELAIS_APPARITION_OBSTACLE = (borne_inf_obstacle + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_obstacle-borne_inf_obstacle))))*10;

// gestion temps apparition aléatoire pièce
  borne_inf_piece = 0.2;
  borne_sup_piece = borne_sup_obstacle+0.2;
  DELAIS_APPARITION_PIECE = (borne_inf_piece + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_piece-borne_inf_piece))))*10;

// gestion temps apparition aléatoire r2d2
  borne_inf_r2d2 = 0.05;
  borne_sup_r2d2 = SCREEN_HEIGHT/(VITESSE_SCROLLING*60.0*10.0)-borne_inf_r2d2;
  DELAIS_APPARITION_R2D2 = (borne_inf_r2d2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_r2d2-borne_inf_r2d2))))*10;

// gestion temps apparition missile
  DELAIS_MISSILE = 0.5;
// Pour afficher le score
score=0;

	//Chargement des sons
	sf::Music Menu_son;
	if (!Menu_son.openFromFile("Son/menu.wav")) return -1; // erreur
	sf::Music missile_son;
	if (!missile_son.openFromFile("Son/missile.wav")) return -1; // erreur
	sf::Music mort_son;
	if (!mort_son.openFromFile("Son/mort.wav")) return -1; // erreur
	sf::Music R2D2_son;
	if (!R2D2_son.openFromFile("Son/R2D2.wav")) return -1; // erreur
	sf::Music piece_son;
	if (!piece_son.openFromFile("Son/piece.wav")) return -1; // erreur

    int i;
    sf::Font font;
    if (!font.loadFromFile("CaviarDreams.ttf"))
    {
        cout<<"ERREUR CHARGEMENT POLICE"<<endl;
    }
    sf::Text text_a_afficher;
    text_a_afficher.setFont(font);
    text_a_afficher.setCharacterSize(30);
    text_a_afficher.setStyle(sf::Text::Bold);
    text_a_afficher.setColor(sf::Color::Black);
    text_a_afficher.setPosition(0,0);

    //Création fenêtre 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Paperise Run");
    //Modifier position de la fenêtre
    window.setPosition(sf::Vector2i(200,200)); //A modifier selon les écrans
    window.setFramerateLimit(60);
    //Background
    Background Menu1("Image/background_menu1.png",0,0);
    Background Menu2("Image/background_menu2.png",0,0);
    Background Menu3("Image/background_menu3.png",0,0);
    Background Menu4("Image/background_menu4.png",0,0);
    Background Menu5("Image/background_menu5.png",0,0);

    // Conteneur pour la gestion de la vitesse
    vector<Decor*> liste_vitesse_scrolling;


    //Fond à scrolling infinie
    Background Fond1("Image/background_SW.jpg",VITESSE_SCROLLING,-800);
    liste_vitesse_scrolling.push_back(&Fond1);
    Background Fond2("Image/background_SW.jpg",VITESSE_SCROLLING,-800);
    liste_vitesse_scrolling.push_back(&Fond2);

    //Obstacle
    Obstacle Trou("Image/cratere.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&Trou);
    Obstacle Vaisseau_ecrase("Image/vaisseau_ecrase.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&Vaisseau_ecrase);

    //Piece
    Piece piece("Image/Bitcoin.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&piece);

    //Ennemi
    Ennemi R2d2("Image/r2d2.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&R2d2);

    //Missile
    Missile missile_rouge("Image/missile.png",0);

    //Perso
    Player Perso("Image/ST1.png",1);

    Evenement event;


    // gestion du temps
    sf::Clock clock_obstacle;
    sf::Clock clock_piece;
    sf::Clock clock_r2d2;
    sf::Clock clock_missile;

    Menu_son.play();
    event.Menu(window,Menu1,Menu2,Menu3,Menu4,Menu5);
    Menu_son.stop();

    while(window.isOpen())
    {       
        if(stop==false){
            event.ActionPlayer(window,&Perso);
            window.clear();
            Fond1.Apparition(window);
            Fond2.Apparition(window);
            Fond1.Scrolling(&Fond2);

            event.gestion_vitesse(liste_vitesse_scrolling);

            // affichage du score
            text_a_afficher.setString("Score: "+to_string(score));
            window.draw(text_a_afficher);
            score++;

            // gestion des objets 
            event.gestion_objet(clock_obstacle,Trou,Vaisseau_ecrase,window,Perso);
            event.gestion_objet(clock_r2d2,R2d2,window,Perso,R2D2_son,mort_son);
            event.gestion_objet(clock_missile,missile_rouge,window,Perso,missile_son);
            event.gestion_objet(clock_piece,piece,window,Perso,piece_son);
            

            Perso.changement_cadre();
            Perso.Apparition(window);
        }
        else if(stop==true){
            Fond1.Apparition(window);
            Fond2.Apparition(window);
            Perso.Apparition(window);               
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) stop=false;
       
        sf::Event event;
        while(window.pollEvent(event)){
            //Si on clique sur fermer
            if(event.type == sf::Event::Closed) window.close();
        }
        window.display();
    }

    return 0;
}