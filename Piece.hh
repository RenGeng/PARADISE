#pragma once
#include "Objet.hh"

class Piece:public Objet
{
public:
	Piece(std::string chemins, int vitesse_scrolling);
	int get_val_piece() const;
	bool operator<=(const Player&) const;
	bool operator>=(const Player&) const;
	bool operator==(const Player&) const;

private:
	int _val_piece; // valeur de la pièce à ajouter au score quand on le ramsse
	
};