#pragma once
#include "Objet.hh"

class Bonus:public Objet
{
public:
	Bonus(std::string chemins, int vitesse_scrolling);
	int Random_x();
};
