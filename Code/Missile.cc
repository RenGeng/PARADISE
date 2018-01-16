#include "Missile.hh"

Missile::Missile(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling){
}

void Missile::Avance(){
	_image.move(0,-5);
}

bool Missile::is_Collision(const Ennemi& ennemi,const Player& Perso) const
{
	if(ennemi.getPos()==getPos() &&
	  (ennemi.getSize_y()*1/2+ennemi.getPos_y() > getPos_y() &&
	   ennemi.getPos_y()<getPos_y())) return true;

	return false;
}
