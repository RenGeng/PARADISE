#include "Player.hh"
#define VITESSE_COURSE 5 //Gère la vitesse de changement car les sleeps c'est galere
int vitesse_course=0;

Player::Player(std::string chemins,int cptcadre):Decor(chemins),_cptcadre(cptcadre),_saut(false),_cpt_saut(0),_cpt_piece(0),_etat_game_over(false){
	_image.setPosition(200,600);
	_pos=1;
}


void Player::Apparition(sf::RenderWindow& window){
	_image.setTextureRect(sf::IntRect(_texture.getSize().x*_cptcadre/2,0,_texture.getSize().x/2,_texture.getSize().y));
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

bool Player::getSaut() const{
	return _saut;
}

void Player::setSaut(bool etat){
	_saut=etat;
}

int Player::get_cpt_saut() const{
	return _cpt_saut;
}

void Player::set_cpt_saut(int cpt){
	_cpt_saut=cpt;
}

void Player::inc_piece()
{
	_cpt_piece++;
}

int Player::get_cpt_piece() const
{
	return _cpt_piece;
}

void Player::set_cpt_piece(int val)
{
	_cpt_piece=val;;
}

void Player::set_Game_over(bool etat,std::string message)
{
	_message_mort=message;
	_etat_game_over=etat;
}

bool Player::get_Game_over() const
{
	return _etat_game_over;
}

std::string Player::get_message_mort(){
	return _message_mort;
}
