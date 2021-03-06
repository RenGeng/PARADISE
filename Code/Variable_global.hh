#pragma once
#include "Piece.hh"
#include "Obstacle.hh"
#include "Missile.hh"
#include "Ennemi.hh"
#include <vector>

 // Taille de la fenêtre : 480*800 pixels
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 800;

extern float VITESSE_SCROLLING;

// gestion temps apparition aléatoire obstacle
extern float borne_inf_obstacle;
extern float borne_sup_obstacle;
extern float DELAIS_APPARITION_OBSTACLE;

// gestion temps apparition aléatoire pièce
extern float borne_inf_piece;
extern float borne_sup_piece;
extern float DELAIS_APPARITION_PIECE;
// gestion temps apparition aléatoire ennemi1
extern float borne_inf_ennemi1;
extern float borne_sup_ennemi1;
extern float DELAIS_APPARITION_ennemi1;
// gestion temps apparition aléatoire missile
extern float DELAIS_MISSILE;

// le score
extern unsigned long long score;

extern std::vector<Piece> liste_piece;
extern std::vector<Missile> liste_missile;
extern std::vector<Obstacle> liste_obstacle;
extern std::vector<Ennemi> liste_ennemi;

extern bool yoda_play; //Savoir si on a deja joué le son de yoda