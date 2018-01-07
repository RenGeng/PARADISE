#include "Evenement.hh"

Evenement::Evenement(){
	_lastKey=-1;

	//Chargement des sons
	sf::Music* Menu_son = new sf::Music();
	if (!Menu_son->openFromFile("Son/menu.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	Menu_son->setLoop(true);
	_liste_son["Menu_son"] = Menu_son;
	sf::Music* Music_fond=new sf::Music();
	if (!Music_fond->openFromFile("Son/music_fond.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	Music_fond->setVolume(50.0);
	_liste_son["Music_fond"] = Music_fond;
	sf::Music* missile_son=new sf::Music();;
	if (!missile_son->openFromFile("Son/missile.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	missile_son->setVolume(50.0);
	_liste_son["missile_son"]=missile_son;
	sf::Music* mort_son=new sf::Music();
	if (!mort_son->openFromFile("Son/mort.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	mort_son->setVolume(50.0);
	_liste_son["mort_son"]=mort_son;
	sf::Music* R2D2_son=new sf::Music();
	if (!R2D2_son->openFromFile("Son/R2D2.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	_liste_son["R2D2_son"]=R2D2_son;
	sf::Music* C3po_son=new sf::Music();
	if (!C3po_son->openFromFile("Son/C3po.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	_liste_son["C3po_son"]=C3po_son;
	sf::Music* piece_son=new sf::Music();
	if (!piece_son->openFromFile("Son/piece.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	_liste_son["piece_son"]=piece_son;
	sf::Music* yoda_son=new sf::Music();
	if (!yoda_son->openFromFile("Son/yoda.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	_liste_son["yoda_son"]=yoda_son;
}


Evenement::~Evenement()
{
	for(std::map<std::string,sf::Music*>::iterator it = _liste_son.begin(); it!=_liste_son.end();it++) delete it->second;
}

sf::Music* Evenement::get_son(std::string nom_son)
{
	return _liste_son[nom_son];
}


void Evenement::ActionPlayer(sf::RenderWindow &window,Player* item){
	int i;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && item->getSaut()==false){
		//Si on est pas tout à droite et que le dernier bouton pressé n'est pas droite
		if(item->getPos()!=2 && _lastKey!=1){
			item->move(150,0);
			item->setPos(item->getPos()+1);
		}
		_lastKey=1;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && item->getSaut()==false){	
		if(item->getPos()!=0 && _lastKey!=0){
			item->move(-150,0);
			item->setPos(item->getPos()-1);
		}
		_lastKey=0;
	}
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

void Evenement::Menu(sf::RenderWindow &window,Background &Menu1,Background &Menu2,Background &Menu3,Background &Menu4,Background &Menu5,Background& Commande){
	//Clock pour pas devenir épilepthique ...
	int clock=0;
	bool next=true;
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
	_liste_son["Menu_son"]->play();
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
			next=false;
			break;
		}
		
    	while(window.pollEvent(event1)){
    		//Si on clique sur fermer
    		if(event1.type == sf::Event::Closed) window.close();
    	}
	}

	while(1)
	{
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) next=true;
		window.clear();
		Commande.Apparition(window);
		window.display();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && next==true) break;
	}
	_liste_son["Menu_son"]->stop();
}


void Evenement::Init_var()
{
		// Initialisation des variables globales
	VITESSE_SCROLLING = 3.0;

	// gestion temps apparition aléatoire obstacle
	borne_inf_obstacle = 0.05;
	borne_sup_obstacle = SCREEN_HEIGHT/(VITESSE_SCROLLING*60.0*10.0)-borne_inf_obstacle;
	DELAIS_APPARITION_OBSTACLE = (borne_inf_obstacle + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_obstacle-borne_inf_obstacle))))*10;

	// gestion temps apparition aléatoire pièce
	borne_inf_piece = 0.2;
	borne_sup_piece = borne_sup_obstacle+0.2;
	DELAIS_APPARITION_PIECE = (borne_inf_piece + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_piece-borne_inf_piece))))*10;

	// gestion temps apparition aléatoire r2d2
	borne_inf_r2d2 = 0.05;
	borne_sup_r2d2 = SCREEN_HEIGHT/(VITESSE_SCROLLING*60.0*10.0)-borne_inf_r2d2;
	DELAIS_APPARITION_R2D2 = (borne_inf_r2d2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_r2d2-borne_inf_r2d2))))*10;

	// gestion temps apparition missile
	DELAIS_MISSILE = 0.5;
	// Pour afficher le score
	score=0;
}

void Evenement::Restart()
{
	Init_var();
	liste_piece.clear();
    liste_obstacle.clear();
    liste_missile.clear();
    liste_ennemi.clear();
    yoda_play=false;

}

void Evenement::gestion_objet(sf::Clock& clock_piece,Piece& piece,sf::RenderWindow& window,Player& Perso)
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

        if(liste_piece[i]==Perso)
        {
        		Perso.inc_piece();
            	liste_piece.erase(liste_piece.begin()+i);
            	_liste_son["piece_son"]->play();
        }

        if (liste_piece[i].getPos_y()>800) liste_piece.erase(liste_piece.begin()+i);                                  
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
	   	liste_obstacle[i].Collision(Perso);
	    //S'il sort de l'écran on le retire de la liste
	    if(liste_obstacle[i].getPos_y()>800) liste_obstacle.erase(liste_obstacle.begin()+i);                           
	}

}



void Evenement::gestion_objet(sf::Clock& clock_missile,Missile& missile_rouge,sf::RenderWindow& window,Player& Perso)
{
	int i;
	//-----------Gestion des obstacles-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'obstacle à la liste 
	if(clock_missile.getElapsedTime().asSeconds()>DELAIS_MISSILE && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		missile_rouge.setPos(Perso.getPos_x()+Perso.getSize_x()/4,Perso.getPos_y());
		liste_missile.push_back(missile_rouge);
		_liste_son["missile_son"]->play();

	    //Réinitialisation du clock_missile
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

void Evenement::gestion_objet(sf::Clock& clock_ennemi, Ennemi& R2d2,Ennemi& C3po,sf::RenderWindow& window,Player& Perso)
{
	int i,j;
	//-----------Gestion des ennemis-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'ennemi à la liste 
	if(clock_ennemi.getElapsedTime().asSeconds()>DELAIS_APPARITION_R2D2)
	{
		if(rand()%3==0)
		{
			C3po.Random_x();
			liste_ennemi.push_back(C3po);
			_liste_son["C3po_son"]->play();			
		}
		else
		{
			R2d2.Random_x();
			liste_ennemi.push_back(R2d2);
			_liste_son["R2D2_son"]->play();			
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
	   liste_ennemi[i].Collision(Perso);

	    //S'il sort de l'écran on le retire de la liste
	    if(liste_ennemi[i].getPos_y()>800) liste_ennemi.erase(liste_ennemi.begin()+i); 

	    //On regarde si un ennemi ne tombe pas contre un obstacle car dans ce cas il se décale
	    for(auto& it:liste_obstacle)	liste_ennemi[i].Collision(it);
        
	    //On regarde si un missile touche pas l'ennemi sinon on supprime l'ennemi
	    for(j=0; j < liste_missile.size();++j){
	    	if(liste_missile[j].is_Collision(liste_ennemi[i],Perso))
	    	{
	    	 	liste_ennemi.erase(liste_ennemi.begin()+i);
	    	 	liste_missile.erase(liste_missile.begin()+j);
	    	 	_liste_son["mort_son"]->play();
	    	 	_liste_son["C3po_son"]->stop();
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
		if(borne_inf_obstacle>0.05)	borne_inf_obstacle-=0.01;
		if(borne_sup_obstacle>borne_inf_obstacle+0.05)	borne_sup_obstacle-=0.05;

		if(borne_inf_r2d2>0.05) borne_inf_r2d2-=0.01;
		if(borne_sup_r2d2>borne_inf_r2d2+0.07) borne_sup_r2d2-=0.02;

	}
}