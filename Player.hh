#pragma once

#include "Decor.hh"

class Player: public Decor
{
public:
	Player(std::string chemins,int cptcadre);//,int top, int left, int largeur, int hauteur);
	void Apparition(sf::RenderWindow& window);
	void changement_cadre();
	int getPos();
	void setPos(int new_pos);


private:
	int _cptcadre; //Permet de connaitre le numéro du cadre à avoir (pour dark vador cadre 0,1 pour qu'il marche et 2 à l'arret)
	int _pos; //0 gauche,1 milieu,2 droite
};