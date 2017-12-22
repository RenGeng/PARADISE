#pragma once
#include <SFML/Graphics.hpp>
#include "Decor.hh"
// Evenement qui gère les décors

class Evenement
{
public:
	Evenement(){};
	void Action(sf::RenderWindow &window,Decor* item);
	
};