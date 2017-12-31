#include "Bonus.hh"

Bonus::Bonus(std::string chemins, int vitesse_scrolling):Objet(chemins,vitesse_scrolling){
}

int Bonus::Random_x()
{
	srand(time(0));
	return _tableau_pos[rand()%4];
}

