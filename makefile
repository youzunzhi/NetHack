CC = g++
CXXFLAGS = -Wall --std=c++11 -I$(INC)

SRC=./src/*.cpp
INC=./include/

all: nethack

nethack: $(SRC)
	$(CC) $(CXXFLAGS) $(SRC) -o $@

run:
	./nethack

clean:
	rm nethack
