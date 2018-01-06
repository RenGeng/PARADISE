#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Decor.hh"
#include "Player.hh"
#include "Background.hh"
#include "Variable_global.hh"
#include <vector>
#include <map>
// Evenement qui gère les décors

class Evenement
{
public:
	Evenement();
	~Evenement();
	sf::Music* get_son(std::string);
	void ActionPlayer(sf::RenderWindow &window,Player* item);
	void Menu(sf::RenderWindow &window,Background& Menu1,Background& Menu2,Background& Menu3,Background& Menu4,Background& Menu5,Background& Commande);
	void Init_var();
	void Restart();

	/* GESTION DES DIVERS OBJETS */
	void gestion_objet(sf::Clock& clock_piece,Piece& piece,sf::RenderWindow& window,Player& Perso);
	void gestion_objet(sf::Clock& clock_obstacle,Obstacle& Trou,Obstacle& Vaisseau_ecrase,sf::RenderWindow& window,Player& Perso);
	void gestion_objet(sf::Clock& clock_missile, Missile& missile_rouge,sf::RenderWindow& window,Player& Perso);
	void gestion_objet(sf::Clock& clock_ennemi, Ennemi& R2d2,Ennemi& C3po,sf::RenderWindow& window,Player& Perso);

	// gestion du niveau du jeu
	void gestion_vitesse(std::vector<Decor*>&);
	void gestion_difficulte();

private:
	int _lastKey; //connaitre le dernier bouton pressé gauche:0 droite:1  espace:2 aucun:-1, car lorsque l'on presse une touche il enregistre plusieur fois la meme touche
	std::map<std::string,sf::Music*> _liste_son; // map contenant les sons à jouer et a pour clé son nom
	
};