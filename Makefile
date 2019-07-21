CPP      = g++
CC       = gcc
BIN      = L1

all: L1.cpp L1.hpp cui_interface.h lexer.hpp
	$(CPP) -I $(CURDIR) L1.cpp -o $(BIN)