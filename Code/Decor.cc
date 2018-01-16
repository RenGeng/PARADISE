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
	_pos=0;


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
	_pos=0;
}

void Decor::Modifier(string chemins){
		
	if (!_texture.loadFromFile(chemins))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image." << endl;
	}
	else
	{
		_texture.setSmooth(true);
		_image.setTexture(_texture,true);
	}
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

int Decor::getPos_x() const{
	return _image.getPosition().x;
}

int Decor::getPos_y() const{
	return _image.getPosition().y;
}

int Decor::getSize_x() const{
	return _texture.getSize().x;
}
int Decor::getSize_y() const{
	return _texture.getSize().y;
}

void Decor::setVitesse_Scrolling(int vitesse){
	_vitesse_scrolling=vitesse;
}

//Methode permettant de centrer un decor par rapport à un autre
void Decor::Centrer(Decor& decor1){	
	//On divise decor par 4 car ca sera tout le temps le personnage qui a deux images pour l'animation donc divisé par 4
	if((int)_texture.getSize().x/2>decor1.getSize_x()/4) _image.setPosition(_image.getPosition().x-(_texture.getSize().x/2-decor1.getSize_x()/4),_image.getPosition().y);
	else _image.setPosition(_image.getPosition().x+(decor1.getSize_x()/4-_texture.getSize().x/2),_image.getPosition().y);
}

int Decor::getPos() const{
	return _pos;
}

void Decor::setPos(int pos){
	_pos=pos;
}
