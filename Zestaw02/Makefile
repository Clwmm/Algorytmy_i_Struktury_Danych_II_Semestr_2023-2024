CC = g++
CFLAGS = -Wall -Wextra -O3 -pedantic

all: main.x

main.x: main.cpp
	$(CC) $(CFLAGS) -o main.x main.cpp

run: main.x
	./main.x

clean:
	rm -f *.x
