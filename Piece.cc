#include "Piece.hh"

Piece::Piece(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling),_val_piece(20){
}

int Piece::get_val_piece() const
{
	return _val_piece;
}

bool Piece::is_Collision(const Player& Perso) const
{
	if((getPos_x()==Perso.getPos_x() && 
      ((getPos_y()+getSize_y()>=Perso.getPos_y()
      && getPos_y()<=Perso.getPos_y()) || (getPos_y()<=Perso.getPos_y()+Perso.getSize_y() && 
      getPos_y()+getSize_y()>=Perso.getPos_y()+Perso.getSize_y())))) return true;
}