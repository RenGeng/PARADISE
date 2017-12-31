#include "Background.hh"

Background::Background(std::string chemins,int vitesse_scrolling,int pos_y):Decor(chemins,vitesse_scrolling){
	_image.setPosition(0,pos_y);
}


void Background::Apparition(sf::RenderWindow& window){	
	window.draw(_image);
}

void Background::Scrolling(Background* Fond2){
	//Fonction scrolling infinie 
	//On gère les deux même décors A et B qui se suivent

	//Si |A.y|>=hauteur_A/2 alors on bouge A et B.y=A.y-hauteur_A/2
	if(_image.getPosition().y>=-(int)_texture.getSize().y/2 && _image.getPosition().y<=(int)_texture.getSize().y/2){
		_image.move(0,_vitesse_scrolling);
		Fond2->setPos(0,_image.getPosition().y-(int)_texture.getSize().y);
	}

	//Si |B.y|>=hauteur_A/2 alors on bouge B et A.y=B.y-hauteur_A/2
	else if(Fond2->getPos_y()>=-(int)_texture.getSize().y/2 && Fond2->getPos_y()<=(int)_texture.getSize().y/2){
		Fond2->move(0,_vitesse_scrolling);
		_image.setPosition(0,Fond2->getPos_y()-(int)_texture.getSize().y);
	}
}