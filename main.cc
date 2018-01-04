#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <deque>
#include <vector>
#include <ctime>
#include "Decor.hh"
#include "Player.hh"
#include "Background.hh"
#include "Evenement.hh"
#include "Objet.hh"
#include "Ennemi.hh"
#include "Obstacle.hh"
#include "Piece.hh"
#include "Missile.hh"
#include "Variable_global.hh"


// vector<Piece> liste_piece;
void gestion_objet(sf::Clock& clock_piece, float& DELAIS_APPARITION_PIECE, Piece& piece,sf::RenderWindow& window,Player& Perso,sf::Music& piece_son)
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

        //Gestion collision si on touche l'objet on retire la piece de la liste
        if((liste_piece[i].getPos_x()==Perso.getPos_x() && 
           ((liste_piece[i].getPos_y()+liste_piece[i].getSize_y()>=Perso.getPos_y()
            && liste_piece[i].getPos_y()<=Perso.getPos_y()) || (liste_piece[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y() && 
            liste_piece[i].getPos_y()+liste_piece[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()))) || liste_piece[i].getPos_y()>800){
            	liste_piece.erase(liste_piece.begin()+i);
            	piece_son.play();
            }                                       
    }
}


// vector<Obstacle> liste_obstacle;
void gestion_objet(sf::Clock& clock_obstacle, float& DELAIS_APPARITION_OBSTACLE, Obstacle& Trou,Obstacle& Vaisseau_ecrase,sf::RenderWindow& window,Player& Perso)
{
	int i,j;
	srand(time(0));
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
	    if(liste_obstacle[i].getPos_x()==Perso.getPos_x() && 
	        (liste_obstacle[i].getPos_y()+liste_obstacle[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()*3/4 
	            && liste_obstacle[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y()*3/4) && Perso.getSaut()==false) stop=true;
	    //S'il sort de l'écran on le retire de la liste
	    else if(liste_obstacle[i].getPos_y()>800) liste_obstacle.erase(liste_obstacle.begin()+i);                           
	}

}

vector<Missile> liste_missile;
void gestion_objet(sf::Clock& clock_missile, float& DELAIS_APPARITION_MISSILE, Missile& missile_rouge,sf::RenderWindow& window,Player& Perso,sf::Music& missile_son)
{
	int i;
	srand(time(0));
	//-----------Gestion des obstacles-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'obstacle à la liste 
	if(clock_missile.getElapsedTime().asSeconds()>DELAIS_APPARITION_MISSILE	&& sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		missile_rouge.setPos(Perso.getPos_x()+Perso.getSize_x()/4,Perso.getPos_y());
		liste_missile.push_back(missile_rouge);
		missile_son.play();

	    //Réinitialisation du clock_r2d2
	    clock_missile.restart();
	    DELAIS_APPARITION_MISSILE = (borne_inf_missile + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_missile-borne_inf_missile))))*10;
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

vector<Ennemi> liste_ennemi;
void gestion_objet(sf::Clock& clock_r2d2, float& DELAIS_APPARITION_R2D2, Ennemi& R2d2,sf::RenderWindow& window,Player& Perso,sf::Music& R2D2_son,sf::Music& mort_son)
{
	int i,j;
	srand(time(0));
	//-----------Gestion des ennemis-----------//

	//Si la clock est supérieur au délai d'apparation on ajoute l'ennemi à la liste 
	if(clock_r2d2.getElapsedTime().asSeconds()>DELAIS_APPARITION_R2D2){
		R2d2.Random_x();
		liste_ennemi.push_back(R2d2);
		R2D2_son.play();

	    //Réinitialisation du clock_r2d2
	    clock_r2d2.restart();
	    DELAIS_APPARITION_R2D2 = (borne_inf_r2d2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_r2d2-borne_inf_r2d2))))*10;
	}

	//On parcourt les ennemis pour les afficher
	for (i = 0; i < liste_ennemi.size(); ++i)
	{
	   liste_ennemi[i].Scrolling();
	   liste_ennemi[i].Avance();
	   liste_ennemi[i].Apparition(window);

	    //Gestion collision si on touche l'objet on arrete et on ne peut pas sauter par dessus un ennemi !
	    if(liste_ennemi[i].getPos_x()==Perso.getPos_x() && 
	        (liste_ennemi[i].getPos_y()+liste_ennemi[i].getSize_y()>=Perso.getPos_y()+Perso.getSize_y()
	            && liste_ennemi[i].getPos_y()<=Perso.getPos_y()+Perso.getSize_y())) stop=true;
	    //S'il sort de l'écran on le retire de la liste
	    else if(liste_ennemi[i].getPos_y()>800) liste_ennemi.erase(liste_ennemi.begin()+i); 

	    //On regarde si un ennemi ne tombe pas contre un ennemi car dans ce cas il disparait
	    for(j=0; j < liste_obstacle.size();++j){
	    	if(liste_ennemi[i].getPos_x()==liste_obstacle[j].getPos_x() &&
	    	 (liste_ennemi[i].getSize_y()*1/2+liste_ennemi[i].getPos_y() > liste_obstacle[j].getPos_y() &&
	    	 	liste_ennemi[i].getPos_y()<liste_obstacle[j].getPos_y())) liste_ennemi.erase(liste_ennemi.begin()+i); 
	    }           

	    //On regarde si un missile touche pas l'ennemi sinon on supprime l'ennemi
	    for(j=0; j < liste_missile.size();++j){
	    	if(liste_ennemi[i].getPos_x()==liste_missile[j].getPos_x()-Perso.getSize_x()/4 &&
	    	 (liste_ennemi[i].getSize_y()*1/2+liste_ennemi[i].getPos_y() > liste_missile[j].getPos_y() &&
	    	 	liste_ennemi[i].getPos_y()<liste_missile[j].getPos_y())){
	    	 	liste_ennemi.erase(liste_ennemi.begin()+i);
	    	 	liste_missile.erase(liste_missile.begin()+j);
	    	 	mort_son.play();
	    	 }
	    }              
	}
}

int main()
{
	//Chargement des sons
	sf::Music Menu_son;
	if (!Menu_son.openFromFile("Son/menu.wav")) return -1; // erreur
	sf::Music missile_son;
	if (!missile_son.openFromFile("Son/missile.wav")) return -1; // erreur
	sf::Music mort_son;
	if (!mort_son.openFromFile("Son/mort.wav")) return -1; // erreur
	sf::Music R2D2_son;
	if (!R2D2_son.openFromFile("Son/R2D2.wav")) return -1; // erreur
	sf::Music piece_son;
	if (!piece_son.openFromFile("Son/piece.wav")) return -1; // erreur

    int i;
    // Pour afficher le score
    unsigned long long score=0;
    sf::Font font;
    if (!font.loadFromFile("CaviarDreams.ttf"))
    {
        cout<<"ERREUR CHARGEMENT POLICE"<<endl;
    }
    sf::Text text_a_afficher;
    text_a_afficher.setFont(font);
    text_a_afficher.setCharacterSize(30);
    text_a_afficher.setStyle(sf::Text::Bold);
    text_a_afficher.setColor(sf::Color::Black);
    text_a_afficher.setPosition(0,0);

    //Création fenêtre 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Paperise Run");
    //Modifier position de la fenêtre
    window.setPosition(sf::Vector2i(200,200)); //A modifier selon les écrans
    window.setFramerateLimit(60);
    //Background
    Background Menu1("Image/background_menu1.png",0,0);
    Background Menu2("Image/background_menu2.png",0,0);
    Background Menu3("Image/background_menu3.png",0,0);
    Background Menu4("Image/background_menu4.png",0,0);
    Background Menu5("Image/background_menu5.png",0,0);

    Background Fond1("Image/background_SW.jpg",VITESSE_SCROLLING,-800);
    Background Fond2("Image/background_SW.jpg",VITESSE_SCROLLING,-800);

    Fond1.Apparition(window);    
    //Perso
    Player Perso("Image/ST1.png",1);

    //Obstacle
    Obstacle Trou("Image/cratere.png",VITESSE_SCROLLING);
    Obstacle Vaisseau_ecrase("Image/vaisseau_ecrase.png",VITESSE_SCROLLING);

    //Piece
    Piece piece("Image/Bitcoin.png",VITESSE_SCROLLING);

    //Ennemi
    Ennemi R2d2("Image/r2d2.png",VITESSE_SCROLLING);

    //Missile
    Missile missile_rouge("Image/missile.png",0);

    Perso.Apparition(window);
    Evenement event;


    // gestion du temps
    sf::Clock clock_obstacle;
    sf::Clock clock_piece;
    sf::Clock clock_r2d2;
    sf::Clock clock_missile;

    Menu_son.play();
    event.Menu(window,Menu1,Menu2,Menu3,Menu4,Menu5);
    Menu_son.stop();

    while(window.isOpen())
    {       
        if(stop==false){
            event.ActionPlayer(window,&Perso);
            window.clear();
            Fond1.Apparition(window);
            Fond2.Apparition(window);
            Fond1.Scrolling(&Fond2);

            //Gestion de la vitesse de scrolling à chaque fois que le score augmente de 10 jusqu'à ce que la vitesse soit egale à 15
            if(score%20==0 && VITESSE_SCROLLING<8){
            	VITESSE_SCROLLING+=0.05;
				borne_sup_obstacle = SCREEN_HEIGHT/(VITESSE_SCROLLING*60.0*10.0)-0.05;
				DELAIS_APPARITION_OBSTACLE = (borne_inf_obstacle + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_obstacle-borne_inf_obstacle))))*10;
				borne_sup_piece = borne_sup_obstacle+0.2;
				DELAIS_APPARITION_PIECE = (borne_inf_piece + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_piece-borne_inf_piece))))*10;
				Fond1.setVitesse_Scrolling(VITESSE_SCROLLING);
				Fond2.setVitesse_Scrolling(VITESSE_SCROLLING);
				Trou.setVitesse_Scrolling(VITESSE_SCROLLING);
				Vaisseau_ecrase.setVitesse_Scrolling(VITESSE_SCROLLING);
				piece.setVitesse_Scrolling(VITESSE_SCROLLING);
				R2d2.setVitesse_Scrolling(VITESSE_SCROLLING);
				for (i = 0; i < liste_obstacle.size(); ++i) liste_obstacle[i].setVitesse_Scrolling(VITESSE_SCROLLING);
				for (i = 0; i < liste_piece.size(); ++i) liste_piece[i].setVitesse_Scrolling(VITESSE_SCROLLING);
					for (i = 0; i < liste_ennemi.size(); ++i) liste_ennemi[i].setVitesse_Scrolling(VITESSE_SCROLLING);
            }

            // affichage du score
            text_a_afficher.setString("Score: "+to_string(score));
            window.draw(text_a_afficher);
            score++;

            // gestion des objets 
            gestion_objet(clock_obstacle,DELAIS_APPARITION_OBSTACLE,Trou,Vaisseau_ecrase,window,Perso);
             
            gestion_objet(clock_r2d2,DELAIS_APPARITION_R2D2,R2d2,window,Perso,R2D2_son,mort_son);
            gestion_objet(clock_missile,DELAIS_APPARITION_MISSILE,missile_rouge,window,Perso,missile_son);

            Perso.changement_cadre();
            Perso.Apparition(window);
        }
        else if(stop==true){
            Fond1.Apparition(window);
            Fond2.Apparition(window);
            Perso.Apparition(window);               
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) stop=false;
       
        sf::Event event;
        while(window.pollEvent(event)){
            //Si on clique sur fermer
            if(event.type == sf::Event::Closed) window.close();
        }
        window.display();
    }

    return 0;
}