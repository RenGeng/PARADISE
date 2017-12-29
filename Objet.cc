#include "Objet.hh"
#include <cstdlib>

Objet::Objet(std::string chemins,int vitesse_scrolling):Decor(chemins,vitesse_scrolling){
	_image.setPosition(100*(rand()%3+1),0);
}

void Objet::Apparition(sf::RenderWindow& window){
	window.draw(_image);
}

void Objet::Scrolling(){
	_image.move(0,_vitesse_scrolling);
}

