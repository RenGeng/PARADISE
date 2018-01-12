#include "Evenement.hh"

using namespace std;

float VITESSE_SCROLLING;

// gestion temps apparition aléatoire obstacle
float borne_inf_obstacle;
float borne_sup_obstacle;
float DELAIS_APPARITION_OBSTACLE;

// gestion temps apparition aléatoire pièce
float borne_inf_piece;
float borne_sup_piece;
float DELAIS_APPARITION_PIECE;
// gestion temps apparition aléatoire r2d2
float borne_inf_r2d2;
float borne_sup_r2d2;
float DELAIS_APPARITION_R2D2;
// gestion temps apparition aléatoire missile
float DELAIS_MISSILE;

vector<Piece> liste_piece;
vector<Obstacle> liste_obstacle;
vector<Missile> liste_missile;
vector<Ennemi> liste_ennemi;

bool yoda_play; //Savoir si on a deja joué le son de yoda

// Pour afficher le score
unsigned long long score;

int main()
{

	srand(time(0));

    // Classe qui va gérer tout au niveau de la fenetre
    Evenement event;
    event.Init_var();

    yoda_play=false; //Permet de rejouer le son de yoda
    bool modifier_fond_vaisseau=true; //Permet de changer le fond qu'une seule fois

    //CHARGEMENT DU TEXT A AFFICHER
    sf::Font font;
    if (!font.loadFromFile("CaviarDreams.ttf")) cout<<"ERREUR CHARGEMENT POLICE"<<endl;
    sf::Text text_score;
    text_score.setFont(font);
    text_score.setCharacterSize(30);
    text_score.setStyle(sf::Text::Bold);
    
    sf::Text text_piece;
    text_piece.setFont(font);
    text_piece.setCharacterSize(30);
    text_piece.setStyle(sf::Text::Bold);
    text_piece.setColor(sf::Color::Black);

    //Création fenêtre 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Paperise Run");
    //Modifier position de la fenêtre
    window.setPosition(sf::Vector2i(200,200)); //A modifier selon les écrans
    window.setFramerateLimit(60);


    //Background Menu
    Background Menu1("Image/background_menu1.png",0,0);
    Background Menu2("Image/background_menu2.png",0,0);
    Background Menu3("Image/background_menu3.png",0,0);
    Background Menu4("Image/background_menu4.png",0,0);
    Background Menu5("Image/background_menu5.png",0,0);
    std::vector<Background> liste_menu;
    liste_menu.push_back(Menu1);
    liste_menu.push_back(Menu2);
    liste_menu.push_back(Menu3);
    liste_menu.push_back(Menu4);
    liste_menu.push_back(Menu5);
    //Background commande
    Background Commande1("Image/commande1.png",0,0);
    Background Commande2("Image/commande2.png",0,0);
    Background Commande3("Image/commande3.png",0,0);
    Background Commande4("Image/commande4.png",0,0);
    Background Commande5("Image/commande5.png",0,0);
    std::vector<Background> liste_commande;
    liste_commande.push_back(Commande1);
    liste_commande.push_back(Commande2);
    liste_commande.push_back(Commande3);
    liste_commande.push_back(Commande4);
    liste_commande.push_back(Commande5);
    Background Game_over("Image/game_over.png");

    event.Menu(window,liste_menu,liste_commande);

    // Conteneur pour la gestion de la vitesse
    vector<Decor*> liste_vitesse_scrolling;


    //Fond à scrolling infinie
    Background Fond1("Image/background_SW.jpg",VITESSE_SCROLLING,-800);
    liste_vitesse_scrolling.push_back(&Fond1);
    Background Fond2("Image/background_SW.jpg",VITESSE_SCROLLING,-800);
    liste_vitesse_scrolling.push_back(&Fond2);

    //Obstacle
    Obstacle Trou("Image/cratere.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&Trou);
    Obstacle Vaisseau_ecrase("Image/vaisseau_ecrase.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&Vaisseau_ecrase);
    Obstacle Vaisseau_fuite("Image/vaisseau_fuite.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&Vaisseau_fuite);
    Vaisseau_fuite.setPos((SCREEN_WIDTH/2)-Vaisseau_fuite.getSize_x()/2,-Vaisseau_fuite.getSize_y());

    //Piece
    Piece piece("Image/Bitcoin.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&piece);

    //Ennemi
    Ennemi R2d2("Image/r2d2.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&R2d2);
    Ennemi C3po("Image/c3po.png",VITESSE_SCROLLING);
    liste_vitesse_scrolling.push_back(&C3po);

    //Missile
    Missile missile_rouge("Image/missile.png",0);

    //Perso
    Player Perso("Image/ST1.png",1);

    // gestion du temps
    sf::Clock clock_obstacle;
    sf::Clock clock_piece;
    sf::Clock clock_ennemi;
    sf::Clock clock_missile;

    while(window.isOpen())
    {       
    	//Si la music de fond est arrété on recommence
    	if(event.get_son("Music_fond")->getStatus()==0) event.get_son("Music_fond")->play();

    	
        if(!Perso.get_Game_over())
        {        	
            event.ActionPlayer(window,&Perso);
            window.clear();
            Fond1.Apparition(window);
            Fond2.Apparition(window);
            Fond1.Scrolling(&Fond2);
            //Si on arrive à un certain score on change de fond
	    	if(score>300 && modifier_fond_vaisseau==true){
	    		liste_piece.clear();
				liste_obstacle.clear();
				liste_missile.clear();
				liste_ennemi.clear();
	    		Vaisseau_fuite.Scrolling();
	    		Vaisseau_fuite.Apparition(window);
	    		if(Perso.getPos_y()<Vaisseau_fuite.getPos_y()+Vaisseau_fuite.getSize_y()*1/2 && Perso.getPos_x()==200){
	    			modifier_fond_vaisseau=false;
	    			Fond1.Modifier("Image/background_vaisseau1.png");
	    			Fond2.Modifier("Image/background_vaisseau2.png");
	    		}
	    		else if(Perso.getPos_y()<Vaisseau_fuite.getPos_y()+Vaisseau_fuite.getSize_y()*1/2 && Perso.getPos_x()!=200) Perso.set_Game_over(true);
	    	}

            event.gestion_vitesse(liste_vitesse_scrolling);
            event.gestion_difficulte();

            // gestion des objets 
            event.gestion_objet(clock_obstacle,Trou,Vaisseau_ecrase,window,Perso);
            event.gestion_objet(clock_ennemi,R2d2,C3po,window,Perso);
            event.gestion_objet(clock_missile,missile_rouge,window,Perso);
            event.gestion_objet(clock_piece,piece,window,Perso);
            

            // affichage du score
            text_score.setColor(sf::Color::Black);
            text_score.setPosition(5,0);
            text_score.setString("Distance: "+to_string(score)+"m");
            window.draw(text_score);
            score++;

            // affichage du nombre de pièce ramassé
            piece.setPos(5,45);
            piece.Apparition(window);
            text_piece.setPosition(60,45);
            text_piece.setString(to_string(Perso.get_cpt_piece()));
            window.draw(text_piece);

            Perso.changement_cadre();
            Perso.Apparition(window);            
        }

        else
        {

        	event.get_son("Music_fond")->stop();
        	event.get_son("C3po_son")->stop();
        	if(event.get_son("yoda_son")->getStatus()==0 && yoda_play==false){
        		event.get_son("yoda_son")->play();        	
        		yoda_play=true;
        	}
            Game_over.Apparition(window);
                    //Réinitialisation
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                event.Restart();
                Perso.set_Game_over(false);
                Perso.set_cpt_piece(0);

            }
            text_score.setColor(sf::Color::White);
            text_score.setPosition(120,25);
            text_score.setString("Votre score: "+to_string(score*Perso.get_cpt_piece()));
            window.draw(text_score);

        }
       
        sf::Event ev;
        while(window.pollEvent(ev)){
            //Si on clique sur fermer
            if(ev.type == sf::Event::Closed) window.close();
        }
        window.display();
    }

    return 0;
}