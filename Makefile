# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Targets and rules
output: main.o database.o blood_pressure_controller.o parser.o
	$(CXX) $(CXXFLAGS) main.o database.o blood_pressure_controller.o parser.o -o output

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

database.o: includes/database.cpp includes/database.h
	$(CXX) $(CXXFLAGS) -c includes/database.cpp -o database.o

blood_pressure_controller.o: includes/blood_pressure_controller.cpp includes/blood_pressure_controller.h
	$(CXX) $(CXXFLAGS) -c includes/blood_pressure_controller.cpp -o blood_pressure_controller.o

parser.o: includes/parser.cpp includes/parser.h
	$(CXX) $(CXXFLAGS) -c includes/parser.cpp -o parser.o

clean: 
	rm -f *.o output