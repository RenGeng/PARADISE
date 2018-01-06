#pragma once
#include "Objet.hh"

class Piece:public Objet
{
public:
	Piece(std::string chemins, int vitesse_scrolling);
	bool is_Collision(const Player&) const;
	int get_val_piece() const;

private:
	int _val_piece; // valeur de la pièce à ajouter au score quand on le ramsse
	
};