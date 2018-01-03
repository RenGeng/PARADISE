#include "Decor.hh"

using namespace std;

Decor::Decor(string chemins)
{
	if (!_texture.loadFromFile(chemins))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image." << endl;
	}
	else
	{
		_texture.setSmooth(true);
		_image.setTexture(_texture);
	}
	_vitesse_scrolling=0;


}

Decor::Decor(string chemins,int vitesse_scrolling)
{
	if (!_texture.loadFromFile(chemins))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image." << endl;
	}
	else
	{
		_texture.setSmooth(true);
		_image.setTexture(_texture);
	}
	_vitesse_scrolling=vitesse_scrolling;
}


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

int Decor::getPos_x(){
	return _image.getPosition().x;
}

int Decor::getPos_y(){
	return _image.getPosition().y;
}

int Decor::getSize_x(){
	return _texture.getSize().x;
}
int Decor::getSize_y(){
	return _texture.getSize().y;
}

void Decor::setVitesse_Scrolling(int vitesse){
	_vitesse_scrolling=vitesse;
}