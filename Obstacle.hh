#pragma once
#include "Objet.hh"



class Obstacle:public Objet
{
public:
	Obstacle(std::string chemins, int vitesse_scrolling);
};