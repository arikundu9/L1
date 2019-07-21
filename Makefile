CPP      = g++
CC       = gcc
ifeq ($(OS),Windows_NT)
	BIN	 = L1.exe
else
	BIN  = L1
endif
all: L1.cpp L1.hpp cui_interface.h lexer.hpp
	$(CPP) -I $(CURDIR) L1.cpp -o $(BIN)