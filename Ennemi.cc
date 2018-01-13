#include "Ennemi.hh"

Ennemi::Ennemi(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling){
}

void Ennemi::Avance(){
	_image.move(0,1);
}


bool Ennemi::operator<=(const Player& Perso) const
{
	if(getPos_y()<=Perso.getPos_y()+Perso.getSize_y()) return true;

	return false;
}


bool Ennemi::operator>=(const Player& Perso) const
{
	if(getPos_y()+getSize_y()>=Perso.getPos_y()+Perso.getSize_y()) return true;

	return false;
}



bool Ennemi::operator==(const Player& Perso) const
{
	if(getPos()==Perso.getPos() && (*this>=Perso && *this<=Perso)) return true;

	return false;
}

bool Ennemi::operator==(const Obstacle& obstacle) const
{
	if(getPos()==obstacle.getPos() &&
	  (getSize_y()+getPos_y() > obstacle.getPos_y() &&
	   getPos_y()<obstacle.getPos_y())) return true;

	return false;
}

void Ennemi::Collision(Player& Perso)
{
	if(*this==Perso) Perso.set_Game_over(true,"Un ennemi !");
}


void Ennemi::Collision(Obstacle& obstacle)
{
	if(*this==obstacle)
	    {

	    	//S'il est tout à gauche il va à droite
	    	if(getPos()==0) {
	    		setPos(getPos_x()+150,getPos_y());
	    		setPos(1);
	    	}
	    	//S'il est au milieu il va à gauche ou à droite
	    	else if(getPos()==1)
	    	{  			
	    		if(rand()%2==0){
	    			setPos(getPos_x()-150,getPos_y());
	    			setPos(0);
	    		}
	    		else{
	    			setPos(getPos_x()+150,getPos_y());
	    			setPos(2);
	    		}
	    	}
	    	//S'il est à droite il va à gauche
	    	else if(getPos()==2){
	    		setPos(getPos_x()-150,getPos_y());
	    		setPos(1);
	    	}
	    }
}
