
CC = g++

LIB = -lpthread -lrt

#LIB_PATH = -L/usr/openwin/lib
#LIB_PATH = -L/usr/X11R6/lib

#FLAGS = -Wall -Wpointer-arith -Wcast-qual -Wstrict-prototypes -O -D__USE_FIXED_PROTOTYPES__ -ansi -pedantic -Wmissing-prototypes -Wshadow -Wcast-align -D_POSIX_SOURCE
#FLAGS = -g
FLAGS = -O2 -std=c++0x

EXE = task3
OBJ = main.o cam.o harness.o switch.o misc.o
SRC = main.cpp cam.cpp harness.cpp switch.cpp misc.cpp
H = defs.h ext.h cam.h harness.h switch.h misc.h


$(EXE): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(EXE) $(LIB_PATH) $(LIB)

main.o: main.cpp $(H)
	$(CC) -c $(FLAGS) main.cpp 

cam.o: cam.cpp $(H)
	$(CC) -c $(FLAGS) cam.cpp 

misc.o: misc.cpp $(H)
	$(CC) -c $(FLAGS) misc.cpp 

harness.o: harness.cpp $(H)
	$(CC) -c $(FLAGS) harness.cpp 

switch.o: switch.cpp $(H)
	$(CC) -c $(FLAGS) switch.cpp 

clean:
	rm -r *.o task3
