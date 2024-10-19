# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

# Targets and rules
output: $(BUILD_DIR)/main.o $(BUILD_DIR)/database.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/user_interface.o $(BUILD_DIR)/dairy.o $(BUILD_DIR)/weight.o $(BUILD_DIR)/bmi_calculator.o $(BUILD_DIR)/goals_interface.o $(BUILD_DIR)/fitness_interface.o
	$(CXX) $(CXXFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/database.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/user_interface.o $(BUILD_DIR)/dairy.o $(BUILD_DIR)/weight.o $(BUILD_DIR)/bmi_calculator.o $(BUILD_DIR)/goals_interface.o $(BUILD_DIR)/fitness_interface.o -o $(BUILD_DIR)/output

# Rule to create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Object file rules
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/database.o: $(SRC_DIR)/database.cpp $(INCLUDE_DIR)/database.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/database.cpp -o $(BUILD_DIR)/database.o

$(BUILD_DIR)/parser.o: $(SRC_DIR)/parser.cpp $(INCLUDE_DIR)/parser.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/parser.cpp -o $(BUILD_DIR)/parser.o

$(BUILD_DIR)/user_interface.o: $(SRC_DIR)/interface/user_interface.cpp $(INCLUDE_DIR)/user_interface.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/interface/user_interface.cpp -o $(BUILD_DIR)/user_interface.o

$(BUILD_DIR)/dairy.o: $(SRC_DIR)/dairy.cpp $(INCLUDE_DIR)/dairy.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/dairy.cpp -o $(BUILD_DIR)/dairy.o

$(BUILD_DIR)/weight.o: $(SRC_DIR)/weight.cpp $(INCLUDE_DIR)/weight.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/weight.cpp -o $(BUILD_DIR)/weight.o

# Add the BmiCalculator files
$(BUILD_DIR)/bmi_calculator.o: $(SRC_DIR)/bmi_calculator.cpp $(INCLUDE_DIR)/bmi_calculator.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/bmi_calculator.cpp -o $(BUILD_DIR)/bmi_calculator.o

$(BUILD_DIR)/goals_interface.o: $(SRC_DIR)/interface/goals_interface.cpp $(INCLUDE_DIR)/goals_interface.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/interface/goals_interface.cpp -o $(BUILD_DIR)/goals_interface.o

$(BUILD_DIR)/fitness_interface.o: $(SRC_DIR)/interface/fitness_interface.cpp $(INCLUDE_DIR)/fitness_interface.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/interface/fitness_interface.cpp -o $(BUILD_DIR)/fitness_interface.o

# Clean rule
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/output
