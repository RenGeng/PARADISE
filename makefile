# options de compilation
CC = g++
CCFLAGS = -Wall
OPTION = -std=c++11 -g
LIBS =-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# fichiers du projet
SRC = main.cc Decor.cc Player.cc Evenement.cc Background.cc Objet.cc Ennemi.cc Obstacle.cc Piece.cc Missile.cc
OBJ = $(SRC:.c=.o)
EXEC = main


# règle initiale
all: $(EXEC)

# dépendance des .hh
Decor.o: Decor.hh
Player.o: Player.hh Decor.hh
Evenement.o: Evenement.hh
Background.o: Background.hh Decor.hh
Objet.o: Objet.hh Decor.hh
Ennemi.o: Objet.hh Ennemi.hh
Obstacle.o: Objet.hh Obstacle.hh
Piece.o: Objet.hh Piece.hh
Missile.o: Objet.hh Missile.hh


# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(OPTION) 	

# règles supplémentaires
clean:
	rm -f *.o
rmproper:
	rm -f $(EXEC) *.o