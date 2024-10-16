#include <iostream>
#include <filesystem>
#include <fstream>  // Add this line
#include "../../include/goals_interface.hpp"
#include "../../include/user_interface.hpp"

void GoalsInterface::set_header(const std::string& header_name)
{
    const std::string CYAN = "\033[36m";
    const std::string RESET = "\033[0m";

    std::cout << std::endl;
    std::cout << "  " << CYAN << header_name << RESET << std::endl;
    std::cout << std::endl;
}

void GoalsInterface::start()
{
    UI ui;

    std::cout << std::endl;
    const std::vector<std::string> options = {
        "1. Add Goal", 
        "2. View Goals", 
        "(B)ack"
    };

    for (const auto& option : options) {
        std::cout << option << "\n";
    }

    std::cout << std::endl;
    while(true)
    {
        std::cout << "Select option: ";
        char command{};
        std::cin >> command;

        switch(command)
        {
            case '1':
                add_goal();
                break;
            case '2':
                view_goals();
                break;
            case 'B':
                ui.open_home_menu();
                return;
            case 'b':
                ui.open_home_menu();
                return;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}
void GoalsInterface::print_goal_types()
{
    const std::vector<std::string> goal_types = {
        "1. Weight Goal",
        "2. Calorie Goal",
        "(B)ack"
    };

    std::cout << std::endl;
    for (size_t i = 0; i < goal_types.size(); ++i) {
        std::cout << goal_types[i] << "\n";
    }
    std::cout << std::endl;

    std::cout << "Select goal type: ";
    char command{};
    std::cin >> command;

    switch(command)
    {
        case '1':
            add_weight_goal();
            break;
        case '2':
            add_calorie_goal();
            break;
        case 'B':
            start();
            break;
        case 'b':
            start();
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
    }
}


void GoalsInterface::add_goal()
{
    print_goal_types();
}

void GoalsInterface::view_goals()
{
    set_header("Goals");
    std::filesystem::path file_path = "../db/goals.txt";
    std::ifstream goals(file_path);

    std::string line;
    while (std::getline(goals, line)) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
    start();
}

void GoalsInterface::add_weight_goal()
{
    double weight = 0.0;
    std::filesystem::path file_path = "../db/goals.txt";
    std::ifstream inFile(file_path);
    std::vector<std::string> lines;
    std::string line;
    bool weightGoalExists = false;

    while (std::getline(inFile, line)) {
        if (line.find("Weight:") == 0) {
            weightGoalExists = true;
            continue;
        }
        lines.push_back(line);
    }
    inFile.close();

    std::cout << std::endl;
    std::cout << "Enter weight goal: ";
    std::cin >> weight;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid number." << std::endl;
    } else {
        std::ofstream outFile(file_path);
        for (const auto& l : lines) {
            outFile << l << std::endl;
        }
        outFile << "Weight: " << weight << std::endl;
        outFile.close();

        if (weightGoalExists) {
            std::cout << "Weight goal updated successfully." << std::endl;
        } else {
            std::cout << "Weight goal added successfully." << std::endl;
        }
        start();
    }
}

void GoalsInterface::add_calorie_goal()
{
    double calories = 0.0;
    std::filesystem::path file_path = "../db/goals.txt";
    std::ifstream in_file(file_path);
    std::vector<std::string> lines;
    std::string line;
    bool calorieGoalExists = false;

    while (std::getline(in_file, line)) {
        if (line.find("Calories:") == 0) {
            calorieGoalExists = true;
            continue;
        }
        lines.push_back(line);
    }

    std::cout << std::endl;
    std::cout << "Enter calorie goal: ";
    std::cin >> calories;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid number." << std::endl;
    } else {
        std::ofstream outFile(file_path);
        for (const auto& l : lines) {
            outFile << l << std::endl;
        }
        outFile << "Calories: " << calories << std::endl;

        if (calorieGoalExists) {
            std::cout << "Calorie goal updated successfully." << std::endl;
        } else {
            std::cout << "Calorie goal added successfully." << std::endl;
        }
        start();
    }
}