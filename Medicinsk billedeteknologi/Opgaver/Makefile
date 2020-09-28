CC = "g++"
CXXFLAGS = -std=c++11 -Wall -g
PROJECT = opgaver # Navnet på dit projekt (Den mappe cpp filen ligger i)
SRC = main.cpp myOpenCVFunctions.h myOpenCVFunctions.cpp  # Navnet på din cpp fil.

LIBS =  `pkg-config opencv4 --cflags --libs`

$(PROJECT) : $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS)  $(CXXFLAGS)