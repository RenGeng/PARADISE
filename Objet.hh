#pragma once

#include "Decor.hh"
#include <vector>
#include <ctime>
#include <cstdlib>

class Objet: public Decor
{
	public:	
		Objet(std::string chemins,int vitesse_scrolling);
		void Apparition(sf::RenderWindow& window);
		void Scrolling();
		virtual void RandomPos();

	protected:
		std::vector<int> _tableau_pos; //contenant les coordonnées x de l'objet, gauche=50, milieu=200, droite=350
};
