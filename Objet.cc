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
	srand(time(0));
	_image.setPosition(150*(rand()%3)+50,-150);
}
