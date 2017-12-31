#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <deque>
#include <ctime>
#include "Decor.hh"
#include "Player.hh"
#include "Background.hh"
#include "Evenement.hh"
#include "Objet.hh"
#include "Bonus.hh"
#include "Obstacle.hh"

#define VITESSE_SCROLLING 10

 // Taille de la fenêtre : 800x480 pixels
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 800;
using namespace std;

int main()
{
    int i,cpt_objet=0;
    bool stop=false,menu=true;
    // Pour afficher le score
    sf::Font font;
    if (!font.loadFromFile("CaviarDreams.ttf"))
    {
        cout<<"ERREUR CHARGEMENT POLICE"<<endl;
    }
    long long score=0;
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

    deque<Obstacle> liste_obstacle;
    Obstacle Carre("Image/cratere.png",VITESSE_SCROLLING);
    std::vector<Bonus> liste_piece;
    Bonus piece("Image/Bitcoin.png",VITESSE_SCROLLING);
    int x_random_piece = piece.Random_x();
    for(i=0;i<5;i++) liste_piece.push_back(piece);

    Perso.Apparition(window);
    Evenement event;


    // gestion temps apparition aléatoire
    srand (static_cast <unsigned> (time(0)));
    float borne_inf = 0.05;
    float borne_sup = 0.1;
    float DELAIS_APPARITION_OBSTACLE = (borne_inf + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup-borne_inf))))*10;

    // gestion du temps
    sf::Time temps_ecoule;
    float sec;
    sf::Clock clock;

    while(window.isOpen()){
        if(menu==true){
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
            if(clock.getElapsedTime().asSeconds()>DELAIS_APPARITION_OBSTACLE)
                {
                    Carre.RandomPos();
                    x_random_piece = piece.Random_x();
                    for(i=0;i<5;i++) liste_piece[i].setPos(x_random_piece,i*-50);
                    liste_obstacle.push_back(Carre);
                    clock.restart();
                    DELAIS_APPARITION_OBSTACLE = (borne_inf + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup-borne_inf))))*10;
                    if(liste_obstacle.size()>5) liste_obstacle.pop_front();
                }
            for (i = 0; i < liste_obstacle.size(); ++i)
            {
               liste_obstacle[i].Scrolling();
               liste_obstacle[i].Apparition(window);
             //gestion collision si on touche l'objet on le retire de la liste
             if(liste_obstacle[i].getPos_x()==Perso.getPos_x() && (liste_obstacle[i].getPos_y()+liste_obstacle[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()*4/5 && liste_obstacle[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y()*4/5)){
                 stop=true;
             }
            
            }

            for(i=0;i<5;i++)
            {
                liste_piece[i].Scrolling();
                liste_piece[i].Apparition(window);
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
        window.display();
    }

    return 0;
}