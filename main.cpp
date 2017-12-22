 //Rabidja 3 - nouvelle version convertie en SFML 2
//Copyright / Droits d'auteur : www.meruvia.fr - Jérémie F. Bellanger
//Big Tuto C++/SFML 2.2 - Février 2015 - Mise à jour 1.2
 
#include "main.h"
 
 
int main(int argc, char *argv[])
{
// Création d'une fenêtre en SFML
RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),
"Rabidja 3.0 - Chapitre 3 - Big Tuto SFML2 - www.meruvia.fr");
 
//Limite les fps à 60 images / seconde
window.setFramerateLimit(60);
 
//On active la synchro verticale
window.setVerticalSyncEnabled(true);
 
//Instanciation des classes
Input input;
 
// Boucle infinie, principale, du jeu
while (window.isOpen())
{
/** GESTION DES INPUTS (CLAVIER, JOYSTICK) **/
input.gestionInputs(window);
 
/** DESSIN - DRAW **/
//On efface l'écran et on l'affiche
window.clear();
window.display();
}
 
// On quitte
return 0;
 
}