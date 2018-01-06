#include "Ennemi.hh"

Ennemi::Ennemi(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling){
}

void Ennemi::Avance(){
	_image.move(0,1);
}

void Ennemi::Collision(Player& Perso,sf::RenderWindow& window)
{
	if(getPos_x()==Perso.getPos_x() && 
	    (getPos_y()+getSize_y()>=Perso.getPos_y()+Perso.getSize_y()
	    && getPos_y()<=Perso.getPos_y()+Perso.getSize_y())) Perso.set_Game_over(true);
}

void Ennemi::Collision(Obstacle& obstacle)
{
		    	if(getPos_x()==obstacle.getPos_x() &&
	    	 (getSize_y()+getPos_y() > obstacle.getPos_y() &&
	    	 	getPos_y()<obstacle.getPos_y()))
	    	{

	    		//S'il est tout à gauche il va à doire
	    		if(getPos_x()==50) setPos(getPos_x()+150,getPos_y());
	    		//S'il est au milieu il va à gauche ou à droite
	    		else if(getPos_x()==200){  			
	    			setPos(300*rand()%2+50,getPos_y());
	    		}
	    		//S'il est à gauche il va à droite
	    		else if(getPos_x()==350) setPos(getPos_x()-150,getPos_y());
	    	}
}
