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

	// Méthodes de gestion de son
	sf::Music* get_son(std::string);
	void set_son(std::string nom_son,std::string chemin);
	void set_son_volume(std::string nom_son,float volume);

	//Méthode de gestion du joueur
	void ActionPlayer(sf::RenderWindow &window,Player* item);

	// Méthode de gestion des menus et commandes
	void Menu(sf::RenderWindow &window,std::vector<Background>& liste_menu,std::vector<Background>& liste_commande);
	std::vector<Background> liste_scintillement(std::vector<Background>& liste_menu);

	// Initialisation des variables globales
	void Init_var();

	// Réinitialisation des variables et des decors
	void Restart(std::vector<Decor*>&, Player&);

	// Changement de décors lorsque les conditions sont remplie
	void Changement(std::vector<Decor*>&, bool&, Obstacle&, sf::RenderWindow&, Player&);

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