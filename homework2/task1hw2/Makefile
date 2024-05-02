CXX = g++
CXXFLAGS =-c -Wall 

all: program

hw2task1program.o: hw2task1program.cpp
	$(CXX) $(CXXFLAGS) -c hw2task1program.cpp hw2task1program.o

hw2task1swap.o: hw2task1swap.cpp
	$(CXX) $(CXXFLAGS) -c hw2task1swap.cpp -o hw2task1swap.o

program: hw2task1program.o hw2task1swap.o
	$(CXX) hw2task1program.o hw2task1swap.o -o program

clean:
	rm -f *.o program
