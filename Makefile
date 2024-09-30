# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Targets and rules
output: main.o database.o blood_pressure_controller.o parser.o user_interface.o dairy.o weight.o
	$(CXX) $(CXXFLAGS) main.o database.o blood_pressure_controller.o parser.o user_interface.o dairy.o weight.o -o output

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

database.o: includes/database.cpp includes/database.h
	$(CXX) $(CXXFLAGS) -c includes/database.cpp -o database.o

blood_pressure_controller.o: includes/blood_pressure_controller.cpp includes/blood_pressure_controller.h
	$(CXX) $(CXXFLAGS) -c includes/blood_pressure_controller.cpp -o blood_pressure_controller.o

parser.o: includes/parser.cpp includes/parser.h
	$(CXX) $(CXXFLAGS) -c includes/parser.cpp -o parser.o

user_interface.o: includes/user_interface.cpp includes/user_interface.h
	$(CXX) $(CXXFLAGS) -c includes/user_interface.cpp -o user_interface.o

dairy.o: includes/dairy.cpp includes/dairy.h
	$(CXX) $(CXXFLAGS) -c includes/dairy.cpp -o dairy.o

weight.o: includes/weight.cpp includes/weight.h
	$(CXX) $(CXXFLAGS) -c includes/weight.cpp -o weight.o

clean: 
	rm -f *.o output
