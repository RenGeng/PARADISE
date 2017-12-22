#pragma once

#include "Decor.hh"

class Player: public Decor
{
public:
	Player(std::string chemins);//,int top, int left, int largeur, int hauteur);
	void Apparition(sf::RenderWindow& window);
	
};