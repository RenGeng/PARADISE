#include "Objet.hh"

Objet::Objet(std::string chemins,int vitesse_scrolling):Decor(chemins,vitesse_scrolling){
	_image.setPosition(100,100);
}

void Objet::Apparition(sf::RenderWindow& window){
	window.draw(_image);
}

void Objet::Scrolling(){
	_image.move(0,_vitesse_scrolling);
}

