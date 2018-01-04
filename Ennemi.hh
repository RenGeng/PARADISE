#pragma once
#include "Objet.hh"

class Ennemi:public Objet
{
public:
	Ennemi(std::string chemins, int vitesse_scrolling);
	void Avance();
};
