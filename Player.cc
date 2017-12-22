#include "Player.hh"

Player::Player(std::string chemins,int top, int left, int largeur, int hauteur):Decor(chemins,top,left,largeur,hauteur){
	_image.setPosition(0,300);
}