#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main()
{
    //Création fenêtre 
    sf::RenderWindow window(sf::VideoMode(800,600),"Paperise Run");
    //Modifier position de la fenêtre
    window.setPosition(sf::Vector2i(200,200)); //A modifier selon les écrans
    window.setFramerateLimit(60);
    //Background
    sf::Texture perso;
	sf::Sprite cercle;
	if(!perso.loadFromFile("personnage.jpg",sf::IntRect(30,30,350,430)))
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
    	int vitesse=10;
    	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) cercle.move(0,-vitesse);
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) cercle.move(0,vitesse);
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) cercle.move(vitesse,0);
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) cercle.move(-vitesse,0);
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) window.clear();
    	else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
    		window.clear();
    		window.draw(cercle);
    		cercle.setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
    	} 
    	window.draw(cercle);
    	window.display();
    	window.clear();
    }

    return 0;
}