#include "Decor.hh"

using namespace std;

Decor::Decor(string chemins)
{
	if (!_texture.loadFromFile(chemins))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image de background." << endl;
	}
	else
		_image.setTexture(_texture);
}

Decor::Decor(std::string chemins,int cptcadre)//top, int left, int largeur, int hauteur)
{
	if (!_texture.loadFromFile(chemins))//,sf::IntRect(top,left,largeur,hauteur)))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image de background." << endl;
	}
	else
	{
		_texture.setSmooth(true);
		_image.setTexture(_texture);
	}
}

// void Decor::Apparition(sf::RenderWindow& window)
// {
// 	window.draw(_image);
// }

void Decor::setDimension(double coeffLargeur, double coeffHauteur)
{
	_image.setScale(coeffLargeur,coeffHauteur);
}

void Decor::move(int x, int y)
{
	_image.move(x,y);
}

void Decor::setPos(int x, int y)
{
	_image.setPosition(x,y);
}