#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>


int main()
{
    //Création fenêtre 
    sf::RenderWindow window(sf::VideoMode(800,600),"Paperise Run");
    //Modifier position de la fenêtre
    window.setPosition(sf::Vector2i(200,200)); //A modifier selon les écrans
    window.setFramerateLimit(60);
    sf::CircleShape cercle;
    cercle.setFillColor(sf::Color(100,250,50));
    cercle.setRadius(50);
    cercle.setPosition(100,100);

    while(window.isOpen()){
    	sf::Event event;
    	while(window.pollEvent(event)){
    		//Si on clique sur fermer
    		if(event.type == sf::Event::Closed) window.close();
    	}
    	window.draw(cercle);
    	window.display();
    	window.clear();
    }

    return 0;
}