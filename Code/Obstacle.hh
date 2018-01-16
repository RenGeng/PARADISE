#pragma once
#include "Objet.hh"



class Obstacle:public Objet
{
public:
	Obstacle(std::string chemins, int vitesse_scrolling);
	bool operator<=(const Player&) const;
	bool operator>=(const Player&) const;
	bool operator==(const Player&) const;
	void Collision(Player&);
};