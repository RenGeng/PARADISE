#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

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
	sf::Texture backgroundTexture;
	sf::Sprite background;
	 if (!backgroundTexture.loadFromFile("Image/background.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image de background." << endl;
	}
	else
		background.setTexture(backgroundTexture);

	window.draw(background);
    //Perso
    sf::Texture perso;
	sf::Sprite cercle;
	if(!perso.loadFromFile("Image/personnage.jpg",sf::IntRect(30,30,350,430)))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image de background." << endl;
	}
	else{
		perso.setSmooth(true);
		cercle.setTexture(perso);
	}
	cercle.setScale(0.25,0.25);
	window.draw(cercle);

    // sf::CircleShape cercle;
    // cercle.setFillColor(sf::Color(100,250,50));
    // cercle.setRadius(50);
    // cercle.setPosition(100,100);
    window.clear();
    window.draw(cercle);

    while(window.isOpen()){

    	sf::Event event;
    	while(window.pollEvent(event)){
    		//Si on clique sur fermer
    		if(event.type == sf::Event::Closed) window.close();
    	}

    	//Gestion des évènements
    	int vitesse=3;
    	float saut=100.0;
    	int i;
    	sleep(0.2);
    	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) cercle.move(0,-vitesse);
    	//Gestion des sauts
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)==true and sf::Keyboard::isKeyPressed(sf::Keyboard::Space)==true){
    		for (i = 0; i < 10; ++i)
    		{
    			cercle.move(vitesse,-saut/10);
    			window.clear();
    			window.draw(background);
    			window.draw(cercle);
    			window.display();
    		}	
    		for (i = 0; i < 10; ++i)
    		{
    			cercle.move(vitesse,saut/10);
    			window.clear();
    			window.draw(background);
    			window.draw(cercle);
    			window.display();
    		}
    	}
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) cercle.move(0,vitesse);
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)==true and sf::Keyboard::isKeyPressed(sf::Keyboard::Space)==false) cercle.move(vitesse,0);
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) cercle.move(-vitesse,0);
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
    		
    		for (i = 0; i < 10; ++i)
    		{
    			cercle.move(0,-saut/10);
    			window.clear();
    			window.draw(background);
    			window.draw(cercle);
    			window.display();
    		}	
    		for (i = 0; i < 10; ++i)
    		{
    			cercle.move(0,saut/10);
    			window.clear();
    			window.draw(background);
    			window.draw(cercle);
    			window.display();
    		}
    	}
    	else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
    		window.clear();
    		window.draw(cercle);
    		cercle.setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
    	} 

    	if(cercle.getPosition().x>SCREEN_WIDTH) cercle.setPosition(0,cercle.getPosition().y);
    	else if(cercle.getPosition().x<0) cercle.setPosition(SCREEN_WIDTH,cercle.getPosition().y);

    	
    	window.draw(background);
    	window.draw(cercle);
    	window.display();
    	window.clear();
    }

    return 0;
}