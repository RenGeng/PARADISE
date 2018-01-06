#pragma once
#include "Player.hh"
#include "Obstacle.hh"


class Ennemi:public Objet
{
public:
	Ennemi(std::string chemins, int vitesse_scrolling);
	void Avance();
	void Collision(Player&,sf::RenderWindow&);
	void Collision(Obstacle&);
};
