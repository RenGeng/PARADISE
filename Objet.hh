#pragma once

#include "Decor.hh"
#include "Player.hh"

class Objet: public Decor
{
	public:	
		Objet(std::string chemins,int vitesse_scrolling);
		void Apparition(sf::RenderWindow& window);
		void Scrolling();
		void RandomPos(Player* perso);

};
