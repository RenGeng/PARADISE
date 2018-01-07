#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Decor
{
public:
	Decor(std::string chemins);
	Decor(std::string chemins,int vitesse_scrolling);
	virtual void Apparition(sf::RenderWindow& window)=0; // Pour faire apparaitre sur la fenetre
	void setDimension(double coeffLargeur, double coeffHauteur); // Pour redimensionner l'image
	void move(int x, int y);
	void setPos(int x, int y);
	int getPos_x() const;
	int getPos_y() const ;
	int getSize_x() const;
	int getSize_y() const;
	void setVitesse_Scrolling(int vitesse);

protected:
	sf::Texture _texture;
	sf::Sprite _image;
	int _vitesse_scrolling;
};

