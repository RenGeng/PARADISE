#pragma once
#include "Player.hh"
#include "Obstacle.hh"


class Ennemi:public Objet
{
public:
	Ennemi(std::string chemins, int vitesse_scrolling);
	void Avance();
	bool operator<=(const Player&) const;
	bool operator>=(const Player&) const;
	bool operator==(const Player&) const;
	bool operator==(const Obstacle&) const;
	void Collision(Player&);
	void Collision(Obstacle&);
};
