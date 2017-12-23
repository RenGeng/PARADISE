#include "Background.hh"

Background::Background(std::string chemins):Decor(chemins){//,int top, int left, int largeur, int hauteur):Decor(chemins,top,left,largeur,hauteur){
	//_image.setPosition(0,300);
}


void Background::Apparition(sf::RenderWindow& window){	
	window.draw(_image);
}