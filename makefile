# Makefile for Hangman Game
# ENGG1340 / COMP2113 Course Project
# Compiles all source files into the hangman executable

CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = hangman

SRCS = src/main.cpp src/game.cpp src/fileio.cpp src/history.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

cleanall: clean
	rm -f history/game_history.txt

.PHONY: clean cleanall
