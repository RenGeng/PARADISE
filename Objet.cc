#include "Objet.hh"


Objet::Objet(std::string chemins,int vitesse_scrolling):Decor(chemins,vitesse_scrolling){
}

void Objet::Apparition(sf::RenderWindow& window){
	window.draw(_image);
}

void Objet::Scrolling(){
	_image.move(0,_vitesse_scrolling);
}


void Objet::Random_x()
{
	int nb_alea=rand()%3;
	_image.setPosition(150*nb_alea+50,-150);
	this->setPos(nb_alea);
}


