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
    int i,j,cpt_objet=0;
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
    Background Menu("Image/background_menu.png",0,0);
    Menu.Apparition(window);

    Background Fond1("Image/background_SW.jpg",VITESSE_SCROLLING,-800);
    Background Fond2("Image/background_SW.jpg",VITESSE_SCROLLING,-800);

    Fond1.Apparition(window);    
    //Perso
    Player Perso("Image/ST1.png",1);

    //Obstacle
    deque<Obstacle> liste_obstacle;
    Obstacle Carre("Image/cratere.png",VITESSE_SCROLLING);
    int x_random_obstacle;

    //Piece
    Piece piece("Image/Bitcoin.png",VITESSE_SCROLLING);
    int x_random_piece = piece.Random_x();
    vector<Piece> colonne_piece;
    for(i=0;i<5;i++) colonne_piece.push_back(piece);
    deque< vector<Piece> > liste_piece;

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
            event.Menu(window,&Menu);
            menu=false;
        }
        if(stop==false && menu==false){
            cpt_objet+=1;
            event.ActionPlayer(window,&Perso);
            window.clear();
            Fond1.Apparition(window);
            Fond2.Apparition(window);
            Fond1.Scrolling(&Fond2);

             // affichage du score
            text_a_afficher.setString("Score: "+to_string(score));
            window.draw(text_a_afficher);
            score++;

            //gestion des pièces
            if(clock_piece.getElapsedTime().asSeconds()>DELAIS_APPARITION_PIECE)
                {
                    x_random_piece = piece.Random_x();
                    for(i=0;i<liste_obstacle.size();i++)
                    {
                        for(j=0;j<colonne_piece.size();j++) 
                            {
                                colonne_piece[j].RandomPos(liste_obstacle[i],x_random_obstacle,x_random_piece);
                                colonne_piece[j].setPos(x_random_piece,-j*piece.getSize_y());
                            }
                    }
                    liste_piece.push_back(colonne_piece);
                    if(liste_piece.size()>5) liste_piece.pop_front();
                    //réinitialisation du clock_pièce
                    clock_piece.restart();
                    DELAIS_APPARITION_PIECE = (borne_inf_piece + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_piece-borne_inf_piece))))*10;
                }


            //gestion des obstacles
            if(clock_obstacle.getElapsedTime().asSeconds()>DELAIS_APPARITION_OBSTACLE)
                {
                    x_random_obstacle = Carre.Random_x();
                    for(i=0;i<liste_piece.size();i++)
                    {
                        for(j=0;j<liste_piece[i].size();j++) Carre.RandomPos(liste_piece[i][j],x_random_piece,x_random_obstacle);
                    }
                    liste_obstacle.push_back(Carre);
                    if(liste_obstacle.size()>10) liste_obstacle.pop_front();
                    //réinitialisation du clock_obstacle
                    clock_obstacle.restart();
                    DELAIS_APPARITION_OBSTACLE = (borne_inf_obstacle + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_obstacle-borne_inf_obstacle))))*10;
                }


            for(i=0;i<liste_piece.size();i++)
            {
                for(j=0;j<liste_piece[i].size();j++)
                {
                    liste_piece[i][j].Scrolling();
                    liste_piece[i][j].Apparition(window);
                }
            }

            for (i = 0; i < liste_obstacle.size(); ++i)
            {
               liste_obstacle[i].Scrolling();
               liste_obstacle[i].Apparition(window);
             //gestion collision si on touche l'objet on le retire de la liste
             if(liste_obstacle[i].getPos_x()==Perso.getPos_x() && (liste_obstacle[i].getPos_y()+liste_obstacle[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()*3/4 && liste_obstacle[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y()*3/4)){
                 stop=true;
             }
            
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
        cout<<"x_random_piece="<<x_random_piece<<endl;
        cout<<"x_random_obstacle="<<x_random_obstacle<<endl;
        window.display();
    }

    return 0;
}