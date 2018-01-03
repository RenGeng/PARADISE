#include "Player.hh"
#define VITESSE_COURSE 5 //Gère la vitesse de changement car les sleeps c'est galere
int vitesse_course=0;

Player::Player(std::string chemins,int cptcadre):Decor(chemins){
	_cptcadre=cptcadre;
	_pos=1;
	_saut=false;
	_cpt_saut=0;
	_image.setPosition(200,500);
}


void Player::Apparition(sf::RenderWindow& window){
	_image.setTextureRect(sf::IntRect(56*_cptcadre,0,56,110));
	window.draw(_image);
}

void Player::changement_cadre(){
	vitesse_course+=1;
	if(_cptcadre==1 && vitesse_course==VITESSE_COURSE){
		_cptcadre=0; //Si on doit bouger on change de cadre
		vitesse_course=0;
	}
	else if(vitesse_course==VITESSE_COURSE){
		_cptcadre+=1;
		vitesse_course=0;
	}
}

int Player::getPos(){
	return _pos;
}

void Player::setPos(int new_pos){
	_pos=new_pos;
}

bool Player::getSaut(){
	return _saut;
}

void Player::setSaut(bool etat){
	_saut=etat;
}

int Player::get_cpt_saut(){
	return _cpt_saut;
}

void Player::set_cpt_saut(int cpt){
	_cpt_saut=cpt;
}