#pragma once

#include "Decor.hh"

class Background: public Decor
{
public:
	Background(std::string chemins,int vitesse_scrolling);

	void Apparition(sf::RenderWindow& window);
	void Scrolling(Background* Fond2);
};