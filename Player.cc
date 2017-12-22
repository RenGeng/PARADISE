#include "Player.hh"

Player::Player(std::string chemins):Decor(chemins){//,int top, int left, int largeur, int hauteur):Decor(chemins,top,left,largeur,hauteur){
	//_image.setPosition(0,300);
}

void Decor::Apparition(sf::RenderWindow& window){
	_image.setTextureRect(sf::IntRect(0,0,160,121));
	window.draw(_image);
}