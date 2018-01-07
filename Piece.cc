#include "Piece.hh"

Piece::Piece(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling),_val_piece(20){
}

int Piece::get_val_piece() const
{
	return _val_piece;
}

bool Piece::operator<=(const Player& Perso) const
{
	if(getPos_y()<=Perso.getPos_y()+Perso.getSize_y()*0.2) return true;

	return false;
}

bool Piece::operator>=(const Player& Perso) const
{
	if(getPos_y()+getSize_y()>=Perso.getPos_y()+Perso.getSize_y()*0.2) return true;
	
	return false;
}


bool Piece::operator==(const Player& Perso) const
{
	if((getPos_x()==Perso.getPos_x() && (*this<=Perso && *this>=Perso))) return true;

	return false;
}