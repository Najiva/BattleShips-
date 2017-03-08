#Author: Juraj Skvarla
#skvarjur@fit.cvut.cz
 
#This is makefile I've used to submit my semestral project from BI-PA2.
#allowed commands: rm, gcc, g++, mkdir, doxygen, cp, mv, cd, ar, make

CXXFLAGS=-Wall -pedantic -std=c++11 -Wno-long-long -O0 -ggdb
CLIBS=
CXX=g++
RM=rm -rf
BINARY=./skvarjur
SRCDIR=src
DOCDIR=doc
OBJECTS =\
        bin/CAI1.o\
        bin/CAI2.o\
        bin/CAI3.o\
        bin/CPerson.o\
        bin/CPlayer.o\
        bin/CShip.o\
        bin/ships.o

#generates final binary and documentation

all: compile doc

#build all objects and merge them into final binary

compile: $(BINARY)

#run program
run: $(BINARY)
	$(BINARY) test #with no parameter return code 1 is returned, param "test" returns 0

#delete all folders with binary files (including documentation)
clean:
	$(RM) bin doc $(BINARY)

#count no. of total lines
count:
	wc -l $(SRCDIR)/*.cpp $(SRCDIR)/*.h
 
#generate documentation in 'skvarjur/doc' folder
doc:\
	$(SRCDIR)/CAI1.cpp $(SRCDIR)/CAI2.cpp $(SRCDIR)/CAI3.cpp $(SRCDIR)/CPlayer.cpp $(SRCDIR)/CPerson.cpp $(SRCDIR)/CShip.cpp $(SRCDIR)/ships.cpp
	$(RM) $(DOCDIR)
	mkdir -p $(DOCDIR)
	doxygen Doxyfile 
#rm -Rf $(DOCDIR)
#mkdir $(DOCDIR)
#doxygen Doxyfile
 
#rules to make objects ----------------------------------------------------------------------------------
$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BINARY) $(CLIBS)

bin/CAI1.o: src/CAI1.cpp src/CAI1.h src/CPlayer.h src/CShip.h
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c src/CAI1.cpp -o bin/CAI1.o

bin/CAI2.o: src/CAI2.cpp src/CAI2.h src/CPlayer.h src/CShip.h
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c src/CAI2.cpp -o bin/CAI2.o

bin/CAI3.o: src/CAI3.cpp src/CAI3.h src/CPlayer.h src/CShip.h
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c src/CAI3.cpp -o bin/CAI3.o

bin/CPerson.o: src/CPerson.cpp src/CPlayer.h src/CShip.h src/CPerson.h
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c src/CPerson.cpp -o bin/CPerson.o

bin/CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CShip.h
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c src/CPlayer.cpp -o bin/CPlayer.o

bin/CShip.o: src/CShip.cpp src/CShip.h
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c src/CShip.cpp -o bin/CShip.o

bin/ships.o: src/ships.cpp src/CPlayer.h src/CShip.h src/CPerson.h src/CAI1.h src/CAI2.h src/CAI3.h
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c src/ships.cpp -o bin/ships.o

