# options de compilation
CC = g++
CCFLAGS = -Wall -std=c++11 -g
LIBS =-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# fichiers du projet
SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
EXEC = main


# règle initiale
all: $(EXEC)

# dépendance des .hh

Decor.o: Decor.hh
Player.o: Player.hh Decor.hh
Evenement.o: Evenement.hh Variable_global.hh
Background.o: Background.hh Decor.hh
Objet.o: Objet.hh Decor.hh
Ennemi.o: Objet.hh Ennemi.hh
Obstacle.o: Objet.hh Obstacle.hh
Piece.o: Objet.hh Piece.hh
Missile.o: Objet.hh Missile.hh
main.o: Variable_global.hh Evenement.hh

# règles de compilation
%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)	

# règles supplémentaires
clean:
	rm -f *.o
rmproper:
	rm -f $(EXEC) *.o