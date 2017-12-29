#include "Objet.hh"
#include <cstdlib>

Objet::Objet(std::string chemins,int vitesse_scrolling):Decor(chemins,vitesse_scrolling){
}

void Objet::Apparition(sf::RenderWindow& window){
	window.draw(_image);
}

void Objet::Scrolling(){
	_image.move(0,_vitesse_scrolling);
}

void Objet::RandomPos(Player* perso){
	_image.setPosition(perso->getPos_x()-abs(perso->getSize_x()/2-_texture.getSize().x/2),0);
}