#include "Piece.hh"

Piece::Piece(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling),_val_piece(20){
}

int Piece::get_val_piece() const
{
	return _val_piece;
}