CPP      = g++.exe
CC       = gcc.exe
BIN      = L1.exe

all: L1.cpp L1.hpp cui_interface.h lexer.hpp
	$(CPP) -I $(CURDIR) L1.cpp -o $(BIN)