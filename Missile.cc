#include "Missile.hh"

Missile::Missile(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling){
	_type = ETAT;
}

void Missile::Avance(){
	_image.move(0,-5);
}