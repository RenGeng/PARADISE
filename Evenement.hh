#pragma once
#include <SFML/Graphics.hpp>
#include "Decor.hh"
#include "Player.hh"
#include "Background.hh"
// Evenement qui gère les décors

class Evenement
{
public:
	Evenement(){};
	void ActionPlayer(sf::RenderWindow &window,Player* item);
	
};