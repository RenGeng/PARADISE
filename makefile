# options de compilation
CC = g++
CCFLAGS = -Wall
OPTION = -std=c++11
LIBS =-lsfml-graphics -lsfml-window -lsfml-system

# fichiers du projet
SRC = main.cc Decor.cc Player.cc Evenement.cc Background.cc Objet.cc
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