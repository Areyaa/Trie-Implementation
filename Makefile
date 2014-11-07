CC = g++
CFLAGS = -Wall
SRC = tema4.cpp
EXE = tema4
 
build:
	$(CC) -o $(EXE) $(SRC) $(CFLAGS)
 

.PHONY : clean
clean :
	rm -f $(EXE) *~
