#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "Decor.hh"
#include "Player.hh"

 // Taille de la fenêtre : 800x480 pixels
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
using namespace std;

int main()
{
    //Création fenêtre 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Paperise Run");
    //Modifier position de la fenêtre
    window.setPosition(sf::Vector2i(200,200)); //A modifier selon les écrans
    window.setFramerateLimit(60);
     //Background
    Decor Fond("Image/background.png");
    Fond.Apparition(window);    
    //Perso
    Player Perso("Image/personnage.jpg",30,30,350,430);
    Perso.setDimension(0.25,0.25);
    Perso.Apparition(window);

    while(window.isOpen()){
        window.clear();
        Fond.Apparition(window);
        Perso.Apparition(window);
        window.display();
    	// sf::Event event;
    	// while(window.pollEvent(event)){
    	// 	//Si on clique sur fermer
    	// 	if(event.type == sf::Event::Closed) window.close();
    	// }

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
     //            Fond.Apparition(window);
    	// 		Perso.Apparition(window);
    	// 		window.display();
    	// 	}	
    	// 	for (i = 0; i < 10; ++i)
    	// 	{
    	// 		Perso.move(vitesse,saut/10);
    	// 		//window.clear();
    	// 		// window.draw(background);
     //            Fond.Apparition(window);
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
     //            Fond.Apparition(window);
    	// 		Perso.Apparition(window);
    	// 		window.display();
    	// 	}	
    	// 	for (i = 0; i < 10; ++i)
    	// 	{
    	// 		Perso.move(0,saut/10);
    	// 		// window.clear();
    	// 		// window.draw(background);
     //            Fond.Apparition(window);
    	// 		Perso.Apparition(window);
    	// 		window.display();
    	// 	}
    	// }

     //    Fond.Apparition(window);
    	// Perso.Apparition(window);
     //    Perso.Apparition(window);
    	// window.display();
    	// // window.clear();
    }

    return 0;
}