#include "Objet.hh"


Objet::Objet(std::string chemins,int vitesse_scrolling):Decor(chemins,vitesse_scrolling){
	_tableau_pos.push_back(50);
	_tableau_pos.push_back(200);
	_tableau_pos.push_back(350);
}

void Objet::Apparition(sf::RenderWindow& window){
	window.draw(_image);
}

void Objet::Scrolling(){
	_image.move(0,_vitesse_scrolling);
}

void Objet::RandomPos(){
	srand(time(0));
	_image.setPosition(_tableau_pos[rand()%4],0);
}

