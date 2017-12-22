#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Decor
{
public:
	Decor(std::string chemins);
	Decor(std::string chemins,int top, int left, int largeur, int hauteur);
	// ~Decor();
	virtual void Apparition(sf::RenderWindow& window); // Pour faire apparaitre sur la fenetre
	void setDimension(double coeffLargeur, double coeffHauteur); // Pour redimensionner l'image
	void move(int x, int y);
	void setPos(int x, int y);

protected:
	sf::Texture _texture;
	sf::Sprite _image;
};
