#pragma once

#include "Decor.hh"

class Background: public Decor
{
public:
	Background(std::string chemins);//,int top, int left, int largeur, int hauteur);

	void Apparition(sf::RenderWindow& window);
	
};