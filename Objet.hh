#pragma once

#include "Decor.hh"
#include <vector>
#include <ctime>
#include <cstdlib>


enum type_objet{OBSTACLE,PIECE,ETAT}; // ETAT permet d'identifier les buff/debuff

class Objet: public Decor
{
	public:	
		Objet(std::string chemins,int vitesse_scrolling);
		void Apparition(sf::RenderWindow& window);
		void Scrolling();
		int Random_x();
		virtual void RandomPos(Objet& item, const int& random_x_item, const int& random_x);

	protected:
		std::vector<int> _tableau_pos; //contenant les coordonnées x de l'objet, gauche=50, milieu=200, droite=350
		type_objet _type;
};
