#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <deque>
#include <vector>
#include <ctime>
#include "Decor.hh"
#include "Player.hh"
#include "Background.hh"
#include "Evenement.hh"
#include "Objet.hh"
#include "Bonus.hh"
#include "Obstacle.hh"
#include "Piece.hh"

 // Taille de la fenêtre : 800x480 pixels
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 800;
using namespace std;

int main()
{
    int VITESSE_SCROLLING = 5;
    int pos_piece_y;
    int i,j;
    bool stop=false,menu=true;
    // Pour afficher le score
    sf::Font font;
    if (!font.loadFromFile("CaviarDreams.ttf"))
    {
        cout<<"ERREUR CHARGEMENT POLICE"<<endl;
    }
    unsigned long long score=0;
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

    Background Fond1("Image/background_SW.jpg",VITESSE_SCROLLING,-800);
    Background Fond2("Image/background_SW.jpg",VITESSE_SCROLLING,-800);

    Fond1.Apparition(window);    
    //Perso
    Player Perso("Image/ST1.png",1);

    //Obstacle
    deque<Obstacle> liste_obstacle;
    Obstacle Trou("Image/cratere.png",VITESSE_SCROLLING);
    int x_random_obstacle;

    //Piece
    deque<Piece> liste_piece;
    Piece piece("Image/Bitcoin.png",VITESSE_SCROLLING);

    // int x_random_piece = piece.Random_x();
    // vector<Piece> colonne_piece;
    // for(i=0;i<5;i++) colonne_piece.push_back(piece);
    // deque< vector<Piece> > liste_piece;

    Perso.Apparition(window);
    Evenement event;


    // gestion temps apparition aléatoire obstacle
    srand (static_cast <unsigned> (time(0)));
    float borne_inf_obstacle = 0.05;
    float borne_sup_obstacle = 0.1;
    float DELAIS_APPARITION_OBSTACLE = (borne_inf_obstacle + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_obstacle-borne_inf_obstacle))))*10;

    // gestion temps apparition aléatoire pièce
    float borne_inf_piece = 0.2;
    float borne_sup_piece = 0.6;
    float DELAIS_APPARITION_PIECE = (borne_inf_piece + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_piece-borne_inf_piece))))*10;


    // gestion du temps
    sf::Clock clock_obstacle;
    sf::Clock clock_piece;

    while(window.isOpen())
    {
        if(menu==true)
        {
            event.Menu(window,Menu1,Menu2,Menu3,Menu4,Menu5);
            menu=false;
        }
        if(stop==false && menu==false){
            event.ActionPlayer(window,&Perso);
            window.clear();
            Fond1.Apparition(window);
            Fond2.Apparition(window);
            Fond1.Scrolling(&Fond2);

             // affichage du score
            text_a_afficher.setString("Score: "+to_string(score));
            window.draw(text_a_afficher);
            score++;

            //-----------Gestion des obstacles-----------//

            //Si la clock est supérieur au délai d'apparation on ajoute l'obstacle à la liste 
            if(clock_obstacle.getElapsedTime().asSeconds()>DELAIS_APPARITION_OBSTACLE){

            	//Affectation aléatoire de la position du trou
            	Trou.Random_x();
            	liste_obstacle.push_back(Trou);

            	//Réinitialisation du clock_obstacle
                clock_obstacle.restart();
                DELAIS_APPARITION_OBSTACLE = (borne_inf_obstacle + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_obstacle-borne_inf_obstacle))))*10;
            }

            //On parcourt les obstacles pour les afficher
            for (i = 0; i < liste_obstacle.size(); ++i)
            {
               liste_obstacle[i].Scrolling();
               liste_obstacle[i].Apparition(window);

             	//Gestion collision si on touche l'objet on arrete
             	if(liste_obstacle[i].getPos_x()==Perso.getPos_x() && 
             		(liste_obstacle[i].getPos_y()+liste_obstacle[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()*3/4 
             			&& liste_obstacle[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y()*3/4)) stop=true;
             	//S'il sort de l'écran on le retire de la liste
             	else if(liste_obstacle[i].getPos_y()>800) liste_obstacle.erase(liste_obstacle.begin()+i);             	            
            }

            //-----------Gestion des pieces-----------//
            if(clock_piece.getElapsedTime().asSeconds()>DELAIS_APPARITION_PIECE){

            	//Affectation aléatoire de la position des pieces en x
            	piece.Random_x();

            	//Affectation aléatoire du nombre de piece entre 3 et 6
            	srand(time(0));
            	//Position de la premiere piece
            	pos_piece_y=0;
            	for(i=0;i<rand()%5+3;i++){
            		//On modifie la coordonnée y de chaque piece pour les avoir les unes à la suite des autres
            		piece.setPos(piece.getPos_x(),pos_piece_y);
            		pos_piece_y-=50;
            		liste_piece.push_back(piece);           

            		//réinitialisation du clock_pièce
                	clock_piece.restart();
            	    DELAIS_APPARITION_PIECE = (borne_inf_piece + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_piece-borne_inf_piece))))*10;
            	}
            }
            //On parcourt les pieces pour les afficher
            for (i = 0; i < liste_piece.size(); ++i)
            {
               liste_piece[i].Scrolling();
               liste_piece[i].Apparition(window);

             	//Gestion collision si on touche l'objet on retire la piece de la liste
             	if((liste_piece[i].getPos_x()==Perso.getPos_x() && 
             		((liste_piece[i].getPos_y()+liste_piece[i].getSize_y()>=Perso.getPos_y()
             			&& liste_piece[i].getPos_y()<=Perso.getPos_y()) || (liste_piece[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y() && 
             			liste_piece[i].getPos_y()+liste_piece[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()))) || liste_piece[i].getPos_y()>800) 
             		liste_piece.erase(liste_piece.begin()+i);              	           	            
            }

            Perso.changement_cadre();
            Perso.Apparition(window);
        }
        else if(stop==true && menu==false){
            Fond1.Apparition(window);
            Fond2.Apparition(window);
            Perso.Apparition(window);               
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) stop=false;
       
        sf::Event event;
        while(window.pollEvent(event)){
            //Si on clique sur fermer
            if(event.type == sf::Event::Closed) window.close();
        }
        //cout<<liste_obstacle.size()<<endl;
        // cout<<"x_random_obstacle="<<x_random_obstacle<<endl;
        window.display();
    }

    return 0;
}