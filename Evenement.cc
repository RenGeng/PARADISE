#include "Evenement.hh"

void Evenement::Action(sf::RenderWindow &window,Decor* item){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) item->move(1,0);
	
	item->Apparition(window);
}
