#include "main.hh"

using namespace std;

int main()
{

	srand(time(0));

    // Classe qui va gérer tout au niveau de la fenetre
    Evenement event;
    event.Init_var();

    //Création fenêtre 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Paperise Run");
    //Modifier position de la fenêtre
    window.setPosition(sf::Vector2i(200,200)); //A modifier selon les écrans
    window.setFramerateLimit(60);


    //Background Menu
    std::vector<Background> liste_menu;
    liste_menu.push_back(Menu1);
    liste_menu.push_back(Menu2);
    liste_menu.push_back(Menu3);
    liste_menu.push_back(Menu4);
    liste_menu.push_back(Menu5);

    std::vector<Background> liste_commande;
    liste_commande.push_back(Commande1);
    liste_commande.push_back(Commande2);
    liste_commande.push_back(Commande3);
    liste_commande.push_back(Commande4);
    liste_commande.push_back(Commande5);
    
    event.Menu(window,liste_menu,liste_commande);

    yoda_play=false; //Permet de rejouer le son de yoda
    bool modifier_fond_vaisseau=true; //Permet de changer le fond qu'une seule fois

    //CHARGEMENT DU TEXT A AFFICHER
    sf::Font font;
    if (!font.loadFromFile("CaviarDreams.ttf")) cout<<"ERREUR CHARGEMENT POLICE"<<endl;
    sf::Text text_score;
    text_score.setFont(font);
    text_score.setCharacterSize(30);
    text_score.setStyle(sf::Text::Bold);
    text_score.setColor(sf::Color::White);
    
    sf::Text text_piece;
    text_piece.setFont(font);
    text_piece.setCharacterSize(30);
    text_piece.setStyle(sf::Text::Bold);
    text_piece.setColor(sf::Color::White);

    sf::Text text_mort;
    text_mort.setFont(font);
    text_mort.setCharacterSize(30);
    text_mort.setStyle(sf::Text::Bold);
    text_mort.setColor(sf::Color::White);


    // Conteneur pour la gestion de la vitesse
    vector<Decor*> liste_vitesse_scrolling;

    // Conteneur à donner argument pour la modification des images
    vector<Decor*> liste_modif;


    liste_vitesse_scrolling.push_back(&Fond1);
    liste_modif.push_back(&Fond1);
    
    liste_vitesse_scrolling.push_back(&Fond2);
    liste_modif.push_back(&Fond2);


    liste_vitesse_scrolling.push_back(&obstacle1);
    liste_modif.push_back(&obstacle1);
    
    liste_vitesse_scrolling.push_back(&obstacle2);
    liste_modif.push_back(&obstacle2);
    
    liste_vitesse_scrolling.push_back(&Vaisseau_fuite);
    Vaisseau_fuite.setPos((SCREEN_WIDTH/2)-Vaisseau_fuite.getSize_x()/2,-Vaisseau_fuite.getSize_y());

    liste_vitesse_scrolling.push_back(&piece);

    liste_vitesse_scrolling.push_back(&ennemi1);
    liste_modif.push_back(&ennemi1);
    
    liste_vitesse_scrolling.push_back(&ennemi2);
    liste_modif.push_back(&ennemi2);

    liste_modif.push_back(&missile_rouge);

    sf::Event ev;
    while(window.isOpen())
    {       
        if(!Perso.get_Game_over())
        {        	
            event.ActionPlayer(window,&Perso);
            window.clear();
            Fond1.Apparition(window);
            Fond2.Apparition(window);
            Fond1.Scrolling(&Fond2);


            event.gestion_vitesse(liste_vitesse_scrolling);
            event.gestion_difficulte();


            event.Changement(liste_modif,modifier_fond_vaisseau,Vaisseau_fuite,window,Perso);

            // gestion des objets 
            event.gestion_objet(clock_obstacle,obstacle1,obstacle2,window,Perso);
            event.gestion_objet(clock_ennemi,ennemi1,ennemi2,window,Perso);
            event.gestion_objet(clock_missile,missile_rouge,window,Perso);
            event.gestion_objet(clock_piece,piece,window,Perso);
            

            // affichage du score
            
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
            event.get_son("mort_son")->stop();
            event.get_son("ennemi1_son")->stop();
        	event.get_son("ennemi2_son")->stop();
        	if(event.get_son("ecran_fin_son")->getStatus()==0 && yoda_play==false){
        		event.get_son("ecran_fin_son")->play();        	
        		yoda_play=true;
        	}
            Game_over.Apparition(window);
                    //Réinitialisation
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                event.Restart(liste_modif,Perso);
                Vaisseau_fuite.setPos((SCREEN_WIDTH/2)-Vaisseau_fuite.getSize_x()/2,-Vaisseau_fuite.getSize_y());
                modifier_fond_vaisseau=true;

            }
            text_score.setColor(sf::Color::White);
            text_score.setPosition(120,25);
            text_score.setString("Votre score: "+to_string(score*Perso.get_cpt_piece()));
            window.draw(text_score);

            text_mort.setColor(sf::Color::White);
            text_mort.setPosition(50,550);
            text_mort.setString("Tu t'es pris :\n"+Perso.get_message_mort());
            window.draw(text_mort);
        }

        while(window.pollEvent(ev)){
            //Si on clique sur fermer
            if(ev.type == sf::Event::Closed) window.close();
        }
        window.display();
    }

    return 0;
}