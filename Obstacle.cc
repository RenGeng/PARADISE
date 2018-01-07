#include "Obstacle.hh"

Obstacle::Obstacle(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling){
}


bool Obstacle::operator<=(const Player& Perso) const
{
	if(getPos_y()<=Perso.getPos_y()+Perso.getSize_y()*3/4) return true;

	return false;
}

bool Obstacle::operator>=(const Player& Perso) const
{
	if(getPos_y()+getSize_y()>=Perso.getPos_y()+Perso.getSize_y()*3/4) return true;

	return false;
}

bool Obstacle::operator==(const Player& Perso) const
{
	if(getPos_x()==Perso.getPos_x() && 
	  (*this>=Perso && *this<=Perso) && Perso.getSaut()==false) return true;

	return false;
}



void Obstacle::Collision(Player& Perso)
{
	if(*this==Perso) Perso.set_Game_over(true);
}