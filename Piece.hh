#pragma once
#include "Objet.hh"

class Piece:public Objet
{
public:
	Piece(std::string chemins, int vitesse_scrolling);
	bool operator<=(const Player&) const;
	bool operator>=(const Player&) const;
	bool operator==(const Player&) const;
};