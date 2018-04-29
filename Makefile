COMPILER = g++
FLAGS = -Wall -pedantic -std=c++11

all: hotel

hotel: clean
	$(COMPILER) src/*.cpp -o hotel $(FLAGS)

run: hotel
	./hotel

clean:
	rm -f hotel hotel.txt
