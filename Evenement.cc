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

void Evenement::Menu(sf::RenderWindow &window,Background &Menu1,Background &Menu2,Background &Menu3,Background &Menu4,Background &Menu5,Background& Commande) const{
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
	sf::Event event1;

	while(1)
	{
		clock+=1;
		window.clear();
		liste_menu[selection_menu].Apparition(window);
		if(clock==7){			
			selection_menu+=1;
			if(selection_menu==8) selection_menu=0;
			clock=0;
		}
		window.display();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) break;
		
    	while(window.pollEvent(event1)){
    		//Si on clique sur fermer
    		if(event1.type == sf::Event::Closed) window.close();
    	}
	}

	while(1)
	{
		window.clear();
		Commande.Apparition(window);
		window.display();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) break;
	}
}

void Evenement::gestion_objet(sf::Clock& clock_piece,Piece& piece,sf::RenderWindow& window,Player& Perso,sf::Music& piece_son)
{
    int i;
    //-----------Gestion des pieces-----------//
    if(clock_piece.getElapsedTime().asSeconds()>DELAIS_APPARITION_PIECE)
    {
        //Affectation aléatoire de la position des pieces en x
        piece.Random_x();

        //Affectation aléatoire du nombre de piece entre 3 et 6
        for(i=0;i<rand()%5+3;i++)
        {
            //On modifie la coordonnée y de chaque piece pour les avoir les unes à la suite des autres
            piece.setPos(piece.getPos_x(),-50*i);
            liste_piece.push_back(piece);           

            //réinitialisation du clock_pièce
            clock_piece.restart();
            DELAIS_APPARITION_PIECE = (borne_inf_piece + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_piece-borne_inf_piece))))*10;
        }
    }
    //On parcourt les pieces pour les afficher
    for (i = 0; i < liste_piece.size(); ++i)
    {
        liste_piece[i].Scrolling();
        liste_piece[i].Apparition(window);

        if((liste_piece[i].getPos_x()==Perso.getPos_x() && 
           ((liste_piece[i].getPos_y()+liste_piece[i].getSize_y()>=Perso.getPos_y()
            && liste_piece[i].getPos_y()<=Perso.getPos_y()) || (liste_piece[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y() && 
            liste_piece[i].getPos_y()+liste_piece[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()))))
        {
        		Perso.inc_piece();
        		score+=liste_piece[i].get_val_piece();
            	liste_piece.erase(liste_piece.begin()+i);
            	piece_son.play();
        }

        else if (liste_piece[i].getPos_y()>800) liste_piece.erase(liste_piece.begin()+i);                                  
    }
}


void Evenement::gestion_objet(sf::Clock& clock_obstacle,Obstacle& Trou,Obstacle& Vaisseau_ecrase,sf::RenderWindow& window,Player& Perso)
{
	int i;
	//-----------Gestion des obstacles-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'obstacle à la liste 
	if(clock_obstacle.getElapsedTime().asSeconds()>DELAIS_APPARITION_OBSTACLE){

		//On choisit entre le vaisseau (1 chance sur 5) et le trou 
		if(rand()%5==0){
			//Affectation aléatoire de la position du trou ou du vaisseau
			Vaisseau_ecrase.Random_x();
	    	liste_obstacle.push_back(Vaisseau_ecrase);
		}
		else{
			//Affectation aléatoire de la position du trou ou du vaisseau
	    	Trou.Random_x();
	    	liste_obstacle.push_back(Trou);
	    }

	    //Réinitialisation du clock_obstacle
	    clock_obstacle.restart();
	    DELAIS_APPARITION_OBSTACLE = (borne_inf_obstacle + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_obstacle-borne_inf_obstacle))))*10;
	}

	//On parcourt les obstacles pour les afficher
	for (i = 0; i < liste_obstacle.size(); ++i)
	{
	   liste_obstacle[i].Scrolling();
	   liste_obstacle[i].Apparition(window);

	    //Gestion collision si on touche l'objet on arrete
	   	liste_obstacle[i].Collision(Perso,window);
	    //S'il sort de l'écran on le retire de la liste
	    if(liste_obstacle[i].getPos_y()>800) liste_obstacle.erase(liste_obstacle.begin()+i);                           
	}

}



void Evenement::gestion_objet(sf::Clock& clock_missile,Missile& missile_rouge,sf::RenderWindow& window,Player& Perso,sf::Music& missile_son)
{
	int i;
	//-----------Gestion des obstacles-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'obstacle à la liste 
	if(clock_missile.getElapsedTime().asSeconds()>DELAIS_MISSILE	&& sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		missile_rouge.setPos(Perso.getPos_x()+Perso.getSize_x()/4,Perso.getPos_y());
		liste_missile.push_back(missile_rouge);
		missile_son.play();

	    //Réinitialisation du clock_ennemi
	    clock_missile.restart();
	}

	//On parcourt les obstacles pour les afficher
	for (i = 0; i < liste_missile.size(); ++i)
	{
	   liste_missile[i].Avance();
	   liste_missile[i].Apparition(window);

	   //Si le missile sort de l'écran on le supprime de la liste      
	   if(liste_missile[i].getPos_y()<0) liste_missile.erase(liste_missile.begin()+i);                
	}
}

void Evenement::gestion_objet(sf::Clock& clock_ennemi, Ennemi& R2d2,Ennemi& C3po,sf::RenderWindow& window,Player& Perso,sf::Music& R2D2_son,sf::Music& C3po_son,sf::Music& mort_son)
{
	int i,j;
	//-----------Gestion des ennemis-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'ennemi à la liste 
	if(clock_ennemi.getElapsedTime().asSeconds()>DELAIS_APPARITION_R2D2){
		if(rand()%3==0){
			C3po.Random_x();
			liste_ennemi.push_back(C3po);
			C3po_son.play();			
		}
		else{
			R2d2.Random_x();
			liste_ennemi.push_back(R2d2);
			R2D2_son.play();			
		}

	    //Réinitialisation du clock_ennemi
	    clock_ennemi.restart();
	    DELAIS_APPARITION_R2D2 = (borne_inf_r2d2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_r2d2-borne_inf_r2d2))))*10;
	}

	//On parcourt les ennemis pour les afficher
	for (i = 0; i < liste_ennemi.size(); ++i)
	{
	   liste_ennemi[i].Scrolling();
	   liste_ennemi[i].Avance();
	   liste_ennemi[i].Apparition(window);

	    //Gestion collision si on touche l'objet on arrete et on ne peut pas sauter par dessus un ennemi !
	   liste_ennemi[i].Collision(Perso,window);

	    //S'il sort de l'écran on le retire de la liste
	    if(liste_ennemi[i].getPos_y()>800) liste_ennemi.erase(liste_ennemi.begin()+i); 

	    //On regarde si un ennemi ne tombe pas contre un obstacle car dans ce cas il se décale
	    for(auto& it:liste_obstacle)	liste_ennemi[i].Collision(it);
        

	    //On regarde si un missile touche pas l'ennemi sinon on supprime l'ennemi
	    for(j=0; j < liste_missile.size();++j){
	    	if(liste_ennemi[i].getPos_x()==liste_missile[j].getPos_x()-Perso.getSize_x()/4 &&
	    	 (liste_ennemi[i].getSize_y()*1/2+liste_ennemi[i].getPos_y() > liste_missile[j].getPos_y() &&
	    	 	liste_ennemi[i].getPos_y()<liste_missile[j].getPos_y()))
	    	{
	    	 	liste_ennemi.erase(liste_ennemi.begin()+i);
	    	 	liste_missile.erase(liste_missile.begin()+j);
	    	 	mort_son.play();
	    	 	C3po_son.stop();
	    	 }
	    }              
	}
}


void Evenement::gestion_vitesse(std::vector<Decor*>& liste_vitesse_scrolling)
{
	//Gestion de la vitesse de scrolling à chaque fois que le score augmente de 10 jusqu'à ce que la vitesse soit egale à 15
	if(score%20==0 && VITESSE_SCROLLING<10)
	{
		VITESSE_SCROLLING+=0.05;
		for(auto& it: liste_vitesse_scrolling) it->setVitesse_Scrolling(VITESSE_SCROLLING);
		for (auto& it: liste_obstacle) it.setVitesse_Scrolling(VITESSE_SCROLLING);
		for (auto& it:liste_piece) it.setVitesse_Scrolling(VITESSE_SCROLLING);
		for (auto& it: liste_ennemi) it.setVitesse_Scrolling(VITESSE_SCROLLING);
	}
}

void Evenement::gestion_difficulte()
{
	if(score%250==0)
	{
		if(borne_inf_obstacle>0.01)	borne_inf_obstacle-=0.01;
		if(borne_sup_obstacle>borne_inf_obstacle+0.05)	borne_sup_obstacle-=0.05;

		if(borne_inf_r2d2>0.04) borne_inf_r2d2-=0.01;
		if(borne_sup_r2d2>borne_inf_r2d2+0.07) borne_sup_r2d2-=0.02;

	}
	
}