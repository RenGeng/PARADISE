#include "Evenement.hh"

Evenement::Evenement(){
	_lastKey=-1;
}



void Evenement::ActionPlayer(sf::RenderWindow &window,Player* item){
	int i;
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
	// else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) item->move(0,-5);
	// else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) item->move(0,5);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		item->setSaut(true);
		 _lastKey=-1;
	}
	else _lastKey=-1; //Si on ne presse rien on revient à l'état -1
	std::vector<float> tab_scale;

	//Si le player est en mode saut
	if(item->getSaut()){		
		for (i = 0; i < 25; ++i) tab_scale.push_back(1+i*0.75/25);
		for (i = 0; i < 15; ++i) tab_scale.push_back(1.75-i*0.75/15);
		item->setDimension(tab_scale[item->get_cpt_saut()],tab_scale[item->get_cpt_saut()]);
		item->set_cpt_saut(item->get_cpt_saut()+1);
		if(item->get_cpt_saut()==40){
			item->setSaut(false);
			item->set_cpt_saut(0);
		}
	}
	
	
	item->Apparition(window); 
	
	
}

void Evenement::Menu(sf::RenderWindow &window,Background &Menu1,Background &Menu2,Background &Menu3,Background &Menu4,Background &Menu5){
	//Clock pour pas devenir épilepthique ...
	int clock=0;
	//Définition des vectors menu pour le parcourir à chaque tour
	int selection_menu=0;
	std::vector<Background> liste_menu;
	liste_menu.push_back(Menu1);
	liste_menu.push_back(Menu2);
	liste_menu.push_back(Menu3);
	liste_menu.push_back(Menu4);
	liste_menu.push_back(Menu5);
	liste_menu.push_back(Menu4);
	liste_menu.push_back(Menu3);
	liste_menu.push_back(Menu2);

	while(1){
		clock+=1;
		window.clear();
		liste_menu[selection_menu].Apparition(window);
		if(clock==7){			
			selection_menu+=1;
			if(selection_menu==8) selection_menu=0;
			clock=0;
		}
		window.display();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) return;
		sf::Event event1;
    	while(window.pollEvent(event1)){
    		//Si on clique sur fermer
    		if(event1.type == sf::Event::Closed) window.close();
    	}
	}
}
