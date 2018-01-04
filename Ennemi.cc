#include "Ennemi.hh"

Ennemi::Ennemi(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling){
	_type = ETAT;
}

void Ennemi::Avance(){
	_image.move(0,1);
}