#pragma once
#include "Objet.hh"

class Missile:public Objet
{
public:
	Missile(std::string chemins, int vitesse_scrolling);
	void Avance();
};