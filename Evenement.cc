#include "Evenement.hh"

Evenement::Evenement(){
	_lastKey=-1;
}

void Evenement::ActionPlayer(sf::RenderWindow &window,Player* item){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		//Si on est pas tout à droite et que le dernier bouton pressé n'est pas droite
		if(item->getPos()!=2 && _lastKey!=1){
			item->move(150,0);
			item->setPos(item->getPos()+1);
		}
		_lastKey=1;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){	
		if(item->getPos()!=0 && _lastKey!=0){
			item->move(-150,0);
			item->setPos(item->getPos()-1);
		}
		_lastKey=0;
	}
	else _lastKey=-1; //Si on ne presse rien on revient à l'état -1
	item->Apparition(window); 
	
	
}

void Evenement::Menu(sf::RenderWindow &window,Background* Menu){
	while(window.isOpen()){
		window.clear();
		Menu->Apparition(window);
		window.display();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) return;
		sf::Event event1;
    	while(window.pollEvent(event1)){
    		//Si on clique sur fermer
    		if(event1.type == sf::Event::Closed) window.close();
    	}
	}
}
