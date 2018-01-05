#pragma once

#include "Decor.hh"

class Player: public Decor
{
public:
	Player(std::string chemins,int cptcadre);
	void Apparition(sf::RenderWindow& window);
	void changement_cadre();
	int getPos();
	void setPos(int new_pos);
	bool getSaut();
	void setSaut(bool etat);
	int get_cpt_saut();
	void set_cpt_saut(int cpt);
	void inc_piece(); // méthode pour incrémenter cpt_pièce
	int get_cpt_piece();


private:
	int _cptcadre; //Permet de connaitre le numéro du cadre à avoir (pour dark vador cadre 0,1 pour qu'il marche et 2 à l'arret)
	int _pos; //0 gauche,1 milieu,2 droite
	bool _saut; //etat du saut
	int _cpt_saut; //permet de savoir ou on en est dans le saut
	int _cpt_piece; //compteur des pièces ramassées
};