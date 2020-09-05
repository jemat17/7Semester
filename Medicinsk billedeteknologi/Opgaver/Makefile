CC = "g++"
PROJECT = opgaver # Navnet på dit projekt (Den mappe cpp filen ligger i)
SRC = opgave1.cpp # Navnet på din cpp fil.

LIBS =  `pkg-config opencv4 --cflags --libs`

$(PROJECT) : $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS)