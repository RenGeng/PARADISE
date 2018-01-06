#include "Obstacle.hh"

Obstacle::Obstacle(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling){
}

void Obstacle::Collision(Player& Perso, sf::RenderWindow& window)
{
		    if(getPos_x()==Perso.getPos_x() && 
	        (getPos_y()+getSize_y()>=Perso.getPos_y()+Perso.getSize_y()*3/4 
	            && getPos_y()<=Perso.getPos_y()+Perso.getSize_y()*3/4) && Perso.getSaut()==false) Perso.set_Game_over(true);
}