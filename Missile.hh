#pragma once
#include "Ennemi.hh"
#include "Player.hh"

class Missile:public Objet
{
public:
	Missile(std::string chemins, int vitesse_scrolling);
	void Avance();
	bool is_Collision(const Ennemi&,const Player&) const;
};