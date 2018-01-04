#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Decor.hh"
#include "Player.hh"
#include "Background.hh"
#include "Variable_global.hh"
#include <vector>
// Evenement qui gère les décors

class Evenement
{
public:
	Evenement();
	void ActionPlayer(sf::RenderWindow &window,Player* item);
	void Menu(sf::RenderWindow &window,Background& Menu1,Background& Menu2,Background& Menu3,Background& Menu4,Background& Menu5);

	/* GESTION DES DIVERS OBJETS */
	void gestion_objet(sf::Clock& clock_piece,Piece& piece,sf::RenderWindow& window,Player& Perso,sf::Music& piece_son);
	void gestion_objet(sf::Clock& clock_obstacle,Obstacle& Trou,Obstacle& Vaisseau_ecrase,sf::RenderWindow& window,Player& Perso);
	void gestion_objet(sf::Clock& clock_missile, Missile& missile_rouge,sf::RenderWindow& window,Player& Perso,sf::Music& missile_son);
	void gestion_objet(sf::Clock& clock_r2d2,Ennemi& R2d2,sf::RenderWindow& window,Player& Perso,sf::Music& R2D2_son,sf::Music& mort_son);

	// gestion du scrore
	void gestion_vitesse(std::vector<Decor*>&);

private:
	int _lastKey; //connaitre le dernier bouton pressé gauche:0 droite:1 aucun:-1, car lorsque l'on presse une touche il enregistre plusieur fois la meme touche
	
};