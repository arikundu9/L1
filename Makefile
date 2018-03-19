CPP      = g++.exe
CC       = gcc.exe
BIN      = L1.exe

all: L1.cpp L1.h cui_interface.h
	$(CPP) L1.cpp -o $(BIN)