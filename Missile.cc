#include "Missile.hh"

Missile::Missile(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling){
}

void Missile::Avance(){
	_image.move(0,-5);
}

bool Missile::is_Collision(const Ennemi& r2d2,const Player& Perso) const
{
	if(r2d2.getPos_x()>getPos_x()-100 && r2d2.getPos_x()<getPos_x()+100 &&
	  (r2d2.getSize_y()*1/2+r2d2.getPos_y() > getPos_y() &&
	   r2d2.getPos_y()<getPos_y())) return true;

	return false;
}
