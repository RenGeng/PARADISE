#pragma once
#include <SFML/Graphics.hpp>
#include "Decor.hh"
#include "Player.hh"
#include "Background.hh"
// Evenement qui gère les décors

class Evenement
{
public:
	Evenement();
	void ActionPlayer(sf::RenderWindow &window,Player* item);
	void Menu(sf::RenderWindow &window,Background& Menu1,Background& Menu2,Background& Menu3,Background& Menu4,Background& Menu5);

private:
	int _lastKey; //connaitre le dernier bouton pressé gauche:0 droite:1 aucun:-1, car lorsque l'on presse une touche il enregistre plusieur fois la meme touche
	
};