#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <vector>
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

    vector<Objet> liste_objet;
    // Objet Carre("Image/carre.png",VITESSE_SCROLLING);
    // liste_objet.push_back(Carre);
    // liste_objet[0].Apparition(window);

    Perso.Apparition(window);
    Evenement event;


    while(window.isOpen()){
        cpt_objet+=1;
        event.ActionPlayer(window,&Perso);
        window.clear();
        Fond1.Apparition(window);
        Fond2.Apparition(window);
        Fond1.Scrolling(&Fond2);
        Perso.changement_cadre();
        Perso.Apparition(window);
        if(cpt_objet==VITESSE_SCROLLING*10){
        	Objet Carre("Image/cratere.png",VITESSE_SCROLLING);
   			liste_objet.push_back(Carre);
   			cpt_objet=0;
   		}
        for (i = 0; i < liste_objet.size(); ++i)
        {
        	liste_objet[i].Scrolling();
        	liste_objet[i].Apparition(window);
        	//gestion collision si on touche l'objet on le retire de la liste
        	if(liste_objet[i].getPos_x()==Perso.getPos_x() && (liste_objet[i].getPos_y()>=Perso.getPos_y() && liste_objet[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y())) liste_objet.erase(liste_objet.begin()+i);  
        
        }

       
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