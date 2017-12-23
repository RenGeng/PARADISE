#include "Player.hh"

Player::Player(std::string chemins,int cptcadre):Decor(chemins){//,int top, int left, int largeur, int hauteur):Decor(chemins,top,left,largeur,hauteur){
	_cptcadre=cptcadre;
	_pos=1;
	_image.setPosition(400,240);
}


void Player::Apparition(sf::RenderWindow& window){
	_image.setTextureRect(sf::IntRect(60*_cptcadre,0,60,121));
	window.draw(_image);
}

void Player::changement_cadre(){
	if(_cptcadre==2) _cptcadre=0; //Si on doit bouger on change de cadre
	else _cptcadre+=1;
}

int Player::getPos(){
	return _pos;
}

void Player::setPos(int new_pos){
	_pos=new_pos;
}