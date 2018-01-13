#pragma once

#include "Background.hh"

class Player: public Decor
{
public:
	Player(std::string chemins,int cptcadre);
	void Apparition(sf::RenderWindow& window);
	void changement_cadre();
	bool getSaut() const;
	void setSaut(bool etat);
	int get_cpt_saut() const;
	void set_cpt_saut(int cpt);
	void inc_piece(); // méthode pour incrémenter cpt_pièce
	int get_cpt_piece() const;
	void set_cpt_piece(int val);
	void set_Game_over(bool etat);
	bool get_Game_over() const;

private:
	int _cptcadre; //Permet de connaitre le numéro du cadre à avoir (pour dark vador cadre 0,1 pour qu'il marche et 2 à l'arret)
	bool _saut; //etat du saut
	int _cpt_saut; //permet de savoir ou on en est dans le saut
	int _cpt_piece; //compteur des pièces ramassées
	bool _etat_game_over; //Etat du joueur
};