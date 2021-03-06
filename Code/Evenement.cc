#include "Evenement.hh"

Evenement::Evenement(){
	_lastKey=-1;

	//Chargement des sons
	sf::Music* Menu_son = new sf::Music();
	if (!Menu_son->openFromFile("../Son/menu.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	Menu_son->setLoop(true);
	_liste_son["Menu_son"] = Menu_son;
	sf::Music* Music_fond=new sf::Music();
	if (!Music_fond->openFromFile("../Son/music_fond.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	Music_fond->setVolume(50.0);
	Music_fond->setLoop(true);
	_liste_son["Music_fond"] = Music_fond;
	sf::Music* missile_son=new sf::Music();;
	if (!missile_son->openFromFile("../Son/missile.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	missile_son->setVolume(50.0);
	_liste_son["missile_son"]=missile_son;
	sf::Music* mort_son=new sf::Music();
	if (!mort_son->openFromFile("../Son/mort.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	mort_son->setVolume(50.0);
	_liste_son["mort_son"]=mort_son;
	sf::Music* ennemi1_son=new sf::Music();
	if (!ennemi1_son->openFromFile("../Son/R2D2.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	_liste_son["ennemi1_son"]=ennemi1_son;
	sf::Music* ennemi2_son=new sf::Music();
	if (!ennemi2_son->openFromFile("../Son/C3po.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	_liste_son["ennemi2_son"]=ennemi2_son;
	sf::Music* piece_son=new sf::Music();
	if (!piece_son->openFromFile("../Son/piece.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	_liste_son["piece_son"]=piece_son;
	sf::Music* yoda_son=new sf::Music();
	if (!yoda_son->openFromFile("../Son/yoda.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	_liste_son["ecran_fin_son"]=yoda_son;
	sf::Music* tie_fighter_son=new sf::Music();
	if (!tie_fighter_son->openFromFile("../Son/tie_fighter.wav")) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	_liste_son["tie_fighter_son"]=tie_fighter_son;
}


Evenement::~Evenement()
{
	for(std::map<std::string,sf::Music*>::iterator it = _liste_son.begin(); it!=_liste_son.end();it++) delete it->second;
}

sf::Music* Evenement::get_son(std::string nom_son)
{
	return _liste_son[nom_son];
}

void Evenement::set_son_volume(std::string nom_son,float volume)
{
	_liste_son[nom_son]->setVolume(volume);
}

void Evenement::set_son(std::string nom_son,std::string chemin)
{
	sf::Music* new_son = new sf::Music();
	if (!new_son->openFromFile(chemin)) std::cout<<"ERREUR CHARGEMENT SON"<<std::endl;
	delete _liste_son[nom_son];
	_liste_son[nom_son]=new_son;
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

void Evenement::Menu(sf::RenderWindow &window,std::vector<Background>& liste_menu,std::vector<Background>& liste_commande){
	//Clock pour pas devenir épilepthique ...
	int clock=0;
	bool menu=true,commande=false;
	//Définition des vectors menu pour le parcourir à chaque tour
	int selection_menu=0;
	std::vector<Background> liste_decor=this->liste_scintillement(liste_menu);
	_liste_son["Menu_son"]->play();
	while(1)
	{		
		//Gestion du scintillement
		clock+=1;
		window.clear();
		sf::Event event1;
		liste_decor[selection_menu].Apparition(window);
		if(clock==7){			
			selection_menu+=1;
			if(selection_menu==8) selection_menu=0;
			clock=0;
		}
		window.display();

		//Si on appuye sur Entrée on change de decor et on bloque le boolean commande pour pas directement sortir sinon on ne voit pas le décor
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && menu==true){
			liste_decor.clear();
			liste_decor=this->liste_scintillement(liste_commande);
			clock=0;
			selection_menu=0;
			commande=true;
			menu=false;
		}

		//On débloque le boolean commande si on a appuyé sur rien
		else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) commande=false;

		//On sort si les deux sont en false
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && menu==false && commande==false) break;

	   	while(window.pollEvent(event1))
	   	{
    		//Si on clique sur fermer
    		if(event1.type == sf::Event::Closed) 
    			{
    				window.close();
    				return;
    			}
    	}
	}
	_liste_son["Menu_son"]->stop();
}

std::vector<Background> Evenement::liste_scintillement(std::vector<Background>& liste_menu){
	std::vector<Background> liste_decor;
	liste_decor.push_back(liste_menu[0]);
	liste_decor.push_back(liste_menu[1]);
	liste_decor.push_back(liste_menu[2]);
	liste_decor.push_back(liste_menu[3]);
	liste_decor.push_back(liste_menu[4]);
	liste_decor.push_back(liste_menu[3]);
	liste_decor.push_back(liste_menu[2]);
	liste_decor.push_back(liste_menu[1]);
	return liste_decor;
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

	// gestion temps apparition aléatoire ennemi1
	borne_inf_ennemi1 = 0.05;
	borne_sup_ennemi1 = SCREEN_HEIGHT/(VITESSE_SCROLLING*60.0*10.0)-borne_inf_ennemi1;
	DELAIS_APPARITION_ennemi1 = (borne_inf_ennemi1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_ennemi1-borne_inf_ennemi1))))*10;

	// gestion temps apparition missile
	DELAIS_MISSILE = 0.5;
	// Pour afficher le score
	score=0;
}

void Evenement::Restart(std::vector<Decor*>& liste_modif, Player& Perso)
{
	Init_var();
	liste_piece.clear();
    liste_obstacle.clear();
    liste_missile.clear();
    liste_ennemi.clear();
    yoda_play=false;
    Perso.set_Game_over(false,"");
    Perso.set_cpt_piece(0);

    liste_modif[0]->Modifier("../Image/background_SW.png");
    liste_modif[1]->Modifier("../Image/background_SW.png");
    liste_modif[2]->Modifier("../Image/cratere.png");
    liste_modif[3]->Modifier("../Image/monstre_sable.png");
    liste_modif[4]->Modifier("../Image/r2d2.png");
    liste_modif[5]->Modifier("../Image/c3po.png");
    liste_modif[6]->Modifier("../Image/missile.png");
    Perso.Modifier("../Image/ST1.png");
   	set_son("ennemi2_son","../Son/C3po.wav");
    set_son("ennemi1_son","../Son/R2D2.wav");
    set_son_volume("ennemi1_son",70.0);
    set_son("mort_son","../Son/mort.wav");
}

void Evenement::Changement(std::vector<Decor*>& liste_modif,bool& modifier_fond_vaisseau, Obstacle& Vaisseau_fuite, sf::RenderWindow& window, Player& Perso)
{
	//Si on arrive à un certain score on change de fond
	if(Perso.get_cpt_piece()>=20 && modifier_fond_vaisseau==true)
    {
    	get_son("ennemi2_son")->stop();
        get_son("ennemi1_son")->stop();
        get_son("missile_son")->stop();
	    liste_piece.clear();
		liste_obstacle.clear();
		liste_missile.clear();
		liste_ennemi.clear();
	    Vaisseau_fuite.Scrolling();
	    Vaisseau_fuite.Apparition(window);

        if(Vaisseau_fuite.getPos_y()+Vaisseau_fuite.getSize_y()+50>Perso.getPos_y() && get_son("tie_fighter_son")->getStatus()==0)
        {
 	       set_son_volume("tie_fighter_son",150.0);
           get_son("tie_fighter_son")->play();
        }
      	if(Perso.getPos_y()<Vaisseau_fuite.getPos_y()+Vaisseau_fuite.getSize_y()*1/2 && Perso.getPos_x()==200)
        {                               
		  modifier_fond_vaisseau=false;
		  liste_modif[0]->Modifier("../Image/background_espace1.png");
		  liste_modif[1]->Modifier("../Image/background_espace2.png");
		  liste_modif[2]->Modifier("../Image/asteroide1.png");
		  liste_modif[3]->Modifier("../Image/trou_noir.png");
		  liste_modif[4]->Modifier("../Image/x-wing.png");
		  liste_modif[5]->Modifier("../Image/faucon_millenium.png");
		  liste_modif[6]->Modifier("../Image/double_missile.png");
		  Perso.Modifier("../Image/vaisseau.png");
		  set_son("ennemi2_son","../Son/faucon_millenium.wav");
		  set_son("ennemi1_son","../Son/x-wing.wav");
		  set_son_volume("ennemi1_son",70.0);
		  set_son("mort_son","../Son/mort2.wav");
		  set_son_volume("mort_son",40.0);
	   	}
        //Si le joueur ne va pas dans la porte du vaisseau mais sur le coté il a perdu
	   	else if(Perso.getPos_y()<Vaisseau_fuite.getPos_y()+Vaisseau_fuite.getSize_y()*1/2 && Perso.getPos_x()!=200) Perso.set_Game_over(true,"Le vaisseau ...");
 	}
}




void Evenement::gestion_objet(sf::Clock& clock_piece,Piece& piece,sf::RenderWindow& window,Player& Perso)
{
    size_t i;
    int j;
    //-----------Gestion des pieces-----------//
    if(clock_piece.getElapsedTime().asSeconds()>DELAIS_APPARITION_PIECE)
    {
        //Affectation aléatoire de la position des pieces en x
        piece.Random_x();
        piece.Centrer(Perso);

        //Affectation aléatoire du nombre de piece entre 3 et 5
        for(j=0;j<rand()%3+3;j++)
        {
            //On modifie la coordonnée y de chaque piece pour les avoir les unes à la suite des autres
            piece.setPos(piece.getPos_x(),-50*j);
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
	size_t i;
	//-----------Gestion des obstacles-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'obstacle à la liste 
	if(clock_obstacle.getElapsedTime().asSeconds()>DELAIS_APPARITION_OBSTACLE){

		//On choisit entre le vaisseau (1 chance sur 5) et le trou 
		if(rand()%5==0){
			//Affectation aléatoire de la position du trou ou du vaisseau
			Vaisseau_ecrase.Random_x();
			Vaisseau_ecrase.Centrer(Perso);
	    	liste_obstacle.push_back(Vaisseau_ecrase);
		}
		else{
			//Affectation aléatoire de la position du trou ou du vaisseau
	    	Trou.Random_x();
	    	Trou.Centrer(Perso);
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
	size_t i;
	//-----------Gestion des obstacles-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'obstacle à la liste 
	if(clock_missile.getElapsedTime().asSeconds()>DELAIS_MISSILE && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		missile_rouge.setPos(Perso.getPos_x(),Perso.getPos_y());
		missile_rouge.setPos(Perso.getPos());
		missile_rouge.Centrer(Perso);		
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

void Evenement::gestion_objet(sf::Clock& clock_ennemi, Ennemi& ennemi1,Ennemi& ennemi2,sf::RenderWindow& window,Player& Perso)
{
	size_t i,j;
	//-----------Gestion des ennemis-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'ennemi à la liste 
	if(clock_ennemi.getElapsedTime().asSeconds()>DELAIS_APPARITION_ennemi1)
	{
		if(rand()%3==0)
		{
			ennemi2.Random_x();
			ennemi2.Centrer(Perso);
			liste_ennemi.push_back(ennemi2);
			_liste_son["ennemi2_son"]->play();			
		}
		else
		{
			ennemi1.Random_x();
			ennemi1.Centrer(Perso);
			liste_ennemi.push_back(ennemi1);
			_liste_son["ennemi1_son"]->play();			
		}

	    //Réinitialisation du clock_ennemi
	    clock_ennemi.restart();
	    DELAIS_APPARITION_ennemi1 = (borne_inf_ennemi1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_ennemi1-borne_inf_ennemi1))))*10;
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
	    for(auto& it:liste_obstacle) liste_ennemi[i].Collision(it);
        
	    //On regarde si un missile touche pas l'ennemi sinon on supprime l'ennemi
	    for(j=0; j < liste_missile.size();++j){
	    	if(liste_missile[j].is_Collision(liste_ennemi[i],Perso))
	    	{
	    	 	liste_ennemi.erase(liste_ennemi.begin()+i);
	    	 	liste_missile.erase(liste_missile.begin()+j);
	    	 	_liste_son["mort_son"]->play();
	    	 	_liste_son["ennemi2_son"]->stop();
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

		if(borne_inf_ennemi1>0.05) borne_inf_ennemi1-=0.01;
		if(borne_sup_ennemi1>borne_inf_ennemi1+0.07) borne_sup_ennemi1-=0.02;

	}
}
