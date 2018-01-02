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


void Objet::Random_x()
{
	srand(time(0));
	_image.setPosition(150*(rand()%3)+50,0);
	//return _tableau_pos[rand()%3];
}


void Objet::RandomPos(Objet& item, const int& random_x_item, const int& random_x)
{
	if(random_x_item == random_x)
	{
		switch (item._type)
		{
			case OBSTACLE:
			case ETAT:
				_image.setPosition(random_x,item.getPos_y()-item.getSize_y());
				break;
			case PIECE:
				_image.setPosition(random_x,item.getPos_y()-5*item.getSize_y());
				break;
		}
	}
	else _image.setPosition(random_x,-1);
}
