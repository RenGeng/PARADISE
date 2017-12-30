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
#define VITESSE_SCROLLING 5

 // Taille de la fenêtre : 800x480 pixels
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 800;
using namespace std;

int main()
{
	int i,cpt_objet=0;
	bool stop=false;
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
    Background Fond1("Image/background_SW.jpg",VITESSE_SCROLLING);
    Background Fond2("Image/background_SW.jpg",VITESSE_SCROLLING);
    Fond1.Apparition(window);    
    //Perso
    Player Perso("Image/ST1.png",1);

    deque<Objet> liste_objet;
    Objet Carre("Image/cratere.png",VITESSE_SCROLLING);
    // liste_objet.push_back(Carre);
    // liste_objet[0].Apparition(window);

    Perso.Apparition(window);
    Evenement event;


    // gestion temps apparition aléatoire
    srand (static_cast <unsigned> (time(0)));
    float borne_inf = 0.1;
    float borne_sup = 0.3;
    float DELAIS_APPARITION_OBSTACLE = (borne_inf + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup-borne_inf))))*10;

    // gestion du temps
    sf::Time temps_ecoule;
    float sec;
    sf::Clock clock;

    while(window.isOpen()){
    	if(stop==false){
	        cpt_objet+=1;
	        event.ActionPlayer(window,&Perso);
	        window.clear();
	        Fond1.Apparition(window);
	        Fond2.Apparition(window);
	        Fond1.Scrolling(&Fond2);

             // affichage du score
            text_a_afficher.setString("SCORE:"+to_string(score));
            window.draw(text_a_afficher);
            score++;
            if(clock.getElapsedTime().asSeconds()>DELAIS_APPARITION_OBSTACLE)
                {
                    liste_objet.push_back(Carre);
                    liste_objet[liste_objet.size()-1].RandomPos(&Perso);
                    clock.restart();
                    DELAIS_APPARITION_OBSTACLE = (borne_inf + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup-borne_inf))))*10;
                    if(liste_objet.size()>5) liste_objet.pop_front();
                }
            for (i = 0; i < liste_objet.size(); ++i)
            {
               liste_objet[i].Scrolling();
               liste_objet[i].Apparition(window);
             //gestion collision si on touche l'objet on le retire de la liste
             if(liste_objet[i].getPos_x()+liste_objet[i].getSize_x()/2==Perso.getPos_x()+Perso.getSize_x()/2 && (liste_objet[i].getPos_y()+liste_objet[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()*4/5 && liste_objet[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y()*4/5)){
                 stop=true;
             }
            
            }




	     //    if(cpt_objet==30){
	   		// 	liste_objet.push_back(Carre);
	   		// 	liste_objet[liste_objet.size()-1].RandomPos(&Perso);
	   		// 	cpt_objet=0;
	   		// }
	        // for (i = 0; i < liste_objet.size(); ++i)
	        // {
         //        if(clock.restart().asMilliseconds()<5)
         //        {
	        // 	  liste_objet[i].Scrolling();
	        // 	  liste_objet[i].Apparition(window);
         //        }
	        // 	//gestion collision si on touche l'objet on le retire de la liste
	        // 	if(liste_objet[i].getPos_x()+liste_objet[i].getSize_x()/2==Perso.getPos_x()+Perso.getSize_x()/2 && (liste_objet[i].getPos_y()+liste_objet[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()*4/5 && liste_objet[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y()*4/5)){
	        // 		liste_objet.erase(liste_objet.begin()+i);  
	        // 		stop=true;
	        // 	}
	        
	        // }

	        Perso.changement_cadre();
        	Perso.Apparition(window);
    	}
    	else if(stop==true){
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

    	// //Gestion des évènements
    	// int vitesse=3;
    	// float saut=100.0;
    	// int i;
    	// sleep(0.2);
    	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Perso.move(0,-vitesse);
    	// //Gestion des sauts
    	// else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)==true and sf::Keyboard::isKeyPressed(sf::Keyboard::Space)==true){
    	// 	for (i = 0; i < 10; ++i)
    	// 	{
    	// 		Perso.move(vitesse,-saut/10);
    	// 		// window.clear();
    	// 		// window.draw(background);
     //            Fond1.Apparition(window);
    	// 		Perso.Apparition(window);
    	// 		window.display();
    	// 	}	
    	// 	for (i = 0; i < 10; ++i)
    	// 	{
    	// 		Perso.move(vitesse,saut/10);
    	// 		//window.clear();
    	// 		// window.draw(background);
     //            Fond1.Apparition(window);
    	// 		Perso.Apparition(window);
    	// 		window.display();
    	// 	}
    	// }
    	// else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Perso.move(0,vitesse);
    	// else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)==true and sf::Keyboard::isKeyPressed(sf::Keyboard::Space)==false) Perso.move(vitesse,0);
    	// else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Perso.move(-vitesse,0);
    	// else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
    		
    	// 	for (i = 0; i < 10; ++i)
    	// 	{
    	// 		Perso.move(0,-saut/10);
    	// 		// window.clear();
    	// 		// window.draw(background);
     //            Fond1.Apparition(window);
    	// 		Perso.Apparition(window);
    	// 		window.display();
    	// 	}	
    	// 	for (i = 0; i < 10; ++i)
    	// 	{
    	// 		Perso.move(0,saut/10);
    	// 		// window.clear();
    	// 		// window.draw(background);
     //            Fond1.Apparition(window);
    	// 		Perso.Apparition(window);
    	// 		window.display();
    	// 	}
    	// }

     //    Fond1.Apparition(window);
    	// Perso.Apparition(window);
     //    Perso.Apparition(window);
    	// window.display();
    	// // window.clear();

        window.display();
    }

    return 0;
}