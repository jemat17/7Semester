CC = "g++"
CXXFLAGS = -Wall
PROJECT = opgaver # Navnet på dit projekt (Den mappe cpp filen ligger i)
SRC = filter.cpp myOpenCVFunctions.h myOpenCVFunctions.cpp  # Navnet på din cpp fil.

LIBS =  `pkg-config opencv4 --cflags --libs`

$(PROJECT) : $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS)  $(CXXFLAGS)