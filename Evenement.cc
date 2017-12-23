#include "Evenement.hh"

void Evenement::ActionPlayer(sf::RenderWindow &window,Player* item){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if(item->getPos()!=2){
			item->move(100,0);
			item->setPos(item->getPos()+1);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){	
		if(item->getPos()!=0){
			item->move(-100,0);
			item->setPos(item->getPos()-1);
		}
	}
	if(item->getPos()==1) std::cout<<"éLOLé"<<std::endl;
	else std::cout<<"nop"<<std::endl;
	
	item->Apparition(window); 
	
	
}
