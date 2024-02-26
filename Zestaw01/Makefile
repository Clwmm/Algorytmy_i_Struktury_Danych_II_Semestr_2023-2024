CC = g++
CFLAGS = -Wall -Wextra -O3 -pedantic

all: Set.x

Set.x: Set.cpp
	$(CC) $(CFLAGS) -o Set.x Set.cpp

run: Set.x
	./Set.x

clean:
	rm -f *.x