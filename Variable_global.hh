#pragma once
#include "Piece.hh"
#include "Obstacle.hh"
#include <vector>

 // Taille de la fenêtre : 800x480 pixels
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 800;
using namespace std;


float VITESSE_SCROLLING = 3.0;

// gestion temps apparition aléatoire obstacle
float borne_inf_obstacle = 0.05;
float borne_sup_obstacle = SCREEN_HEIGHT/(VITESSE_SCROLLING*60.0*10.0)-borne_inf_obstacle;
float DELAIS_APPARITION_OBSTACLE = (borne_inf_obstacle + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_obstacle-borne_inf_obstacle))))*10;

// gestion temps apparition aléatoire pièce
float borne_inf_piece = 0.2;
float borne_sup_piece = borne_sup_obstacle+0.2;
float DELAIS_APPARITION_PIECE = (borne_inf_piece + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_piece-borne_inf_piece))))*10;

// gestion temps apparition aléatoire r2d2
float borne_inf_r2d2 = 0.05;
float borne_sup_r2d2 = SCREEN_HEIGHT/(VITESSE_SCROLLING*60.0*10.0)-borne_inf_r2d2;
float DELAIS_APPARITION_R2D2 = (borne_inf_r2d2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_r2d2-borne_inf_r2d2))))*10;

// gestion temps apparition aléatoire missile
float borne_inf_missile = 0.05;
float borne_sup_missile = 0.06;
float DELAIS_APPARITION_MISSILE = (borne_inf_missile + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(borne_sup_missile-borne_inf_missile))))*10;

vector<Piece> liste_piece;

// à effacer plus tard
bool stop=false;

vector<Obstacle> liste_obstacle;