#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "../include/database.hpp"
#include "../include/user_interface.hpp"
#include "../include/dairy.hpp"
#include "../include/parser.hpp"
#include "../include/weight.hpp"
#include "../include/bmi_calculator.hpp"
#include "../include/goals_interface.hpp"
#include "../include/fitness_interface.hpp"

const std::string RED = "\033[31m";
const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

void UI::open_home_menu()
{
    GoalsInterface goals_interface;
    fitness::FitnessInterface fitness_interface;

	set_header("Home");

    std::cout << "1. Diary" << std::endl;
	std::cout << "2. Health" << std::endl;
	std::cout << "3. Goals" << std::endl;
	std::cout << "4. Fitness" << std::endl;
	std::cout << "(Q)uit application" << std::endl;
    std::cout << std::endl;
	std::cout << "Select options: ";

    char command{};
    std::cin >> command;

    switch(command) 
    {
        case '1':
            open_dairy_menu();
            break;
        case '2':
            open_health_menu();
            break;
        case '3':
            goals_interface.start();
            break;
        case '4':
            fitness_interface.start();
            break;
        case 'q':
            exit(0);
        case 'Q':
            exit(0);
        default:
            std::cout << "Invalid command" << std::endl;
            open_home_menu();
    }
}

void UI::set_header(const std::string& header_name)
{
    std::cout << std::endl;
	std::cout << "    " << CYAN << header_name << RESET << std::endl;
    std::cout << std::endl;
}

void UI::open_health_menu(){
    set_header("Health Menu");
    std::vector<std::string> menu_options = {
        "1. Enter Weight",
        "2. Read Weight",
        "3. Enter Height",
        "4. Read Height",
        "5. Read BMI",
        "(B)ack"
    };
    for (const auto& option : menu_options) {
        std::cout << option << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Enter command: ";

    char command{};
    std::cin >> command;
    switch(command){
        case '1':        
            enter_weight();
            open_health_menu();
            break;
        case '2':
            read_weight();
            open_health_menu();
            break;
        case '3':
            enter_height();
            open_health_menu();
            break;
        case '4':
            read_height();
            open_health_menu();
            break;
        case '5':
            read_bmi();
            open_health_menu();
            break;
        case 'B':
           open_home_menu(); 
            break;
        case 'b':
           open_home_menu(); 
            break;
        default:
           open_home_menu(); 
    }
}

void UI::open_food_database(bool show_as_list){
    std::unique_ptr<Dairy> dairy = std::make_unique<Dairy>();
    std::cout << std::endl;
    read_db();
    std::cout << std::endl;

    std::string seperator = show_as_list ? "| " : "\n";

    std::string menu_options = 
        "1. Add " + seperator + 
        "2. Remove " + seperator +
        "3. Read " + seperator +
        "(B)ack";

    std::cout << menu_options;
    std::cout << std::endl;
    std::cout << "Enter command: ";

    char command{};
    std::cin >> command;
    switch (command) {
        case '1':
            dairy->add_new_food();
            open_food_database(true);
            break;
        case '2':
            dairy->remove_food();
            open_food_database(true);
            break;
        case '3':
            read_db();
            open_food_database(true);
            break;
        case 'b':
            open_dairy_menu();
            break;
        case 'B':
            open_dairy_menu();
            break;
        default:
            open_food_database(true);
            break;
    }
}

void UI::open_dairy_menu(){
    set_header("Dairy Menu");

    std::vector<std::string> menu_options = {
        "1. Daily Entries",
        "2. Food Database",
        "(B)ack"
    };

    for (const auto& option : menu_options) {
        std::cout << option << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Enter command: ";
    char command{};
    std::cin >> command;

    switch(command){
        case '1':
            open_daily_entries_menu();
            break;
        case '2':
            open_food_database(true);
            break;
        case 'b':
            open_home_menu();  
            break;
        case 'B':
            open_home_menu();  
            break;
        default: 
            open_home_menu();  
    }
}

void UI::open_daily_entries_menu(){
    auto dairy = std::make_unique<Dairy>();
    Parser parser;
    read_daily_entry(parser.create_date_stamp());

    std::vector<std::string> menu_options = {
        "1. Add",
        "2. Read",
        "3. Read by date",
        "(B)ack"
    };

    for (const auto& option : menu_options) {
        std::cout << option << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Enter command: ";
    char command{};
    std::cin >> command;

    switch(command){
        case '1':
            dairy->add_new_daily_entry();
            open_daily_entries_menu();
            break;
        case '2':
            read_daily_entry(parser.create_date_stamp());
            open_daily_entries_menu();
            break;
        case '3':
            read_daily_entry_by_date();
            open_daily_entries_menu();
            break;
        case 'b':
            open_dairy_menu();
            break;
        case 'B':
            open_dairy_menu();
            break;
        default: 
            open_dairy_menu();
    }
}
void UI::read_daily_entry(const std::string& date){
    std::cout << std::endl;
    std::cout << CYAN << "YOUR DAILY ENTRIES" << RESET;
    std::cout << std::endl;

    read_meal_data(date, "breakfast");
    read_meal_data(date, "lunch");
    read_meal_data(date, "dinner");

    std::cout << std::string(128, '-') << std::endl;

    std::unique_ptr<Dairy> dairy = std::make_unique<Dairy>();
    Food total = dairy->get_total_all_meals(date);

    std::cout << std::left 
        << std::setw(3)  << ""
        << CYAN << std::setw(30) << total.name
        << std::setw(25) << total.brand
        << std::setw(15) << total.amount
        << std::setw(15) << total.calories
        << std::setw(15) << total.fat
        << std::setw(15) << total.carbs
        << std::setw(15) << total.protein << RESET
        << std::endl;

    std::cout << std::string(128, '-') << std::endl;
    read_remaining(total.calories);
    std::cout << std::string(128, '-') << std::endl;
}

void UI::read_daily_entry_by_date(){
    std::cout << std::endl;
    std::cout << "Enter date(dd/mm/yyyy): ";
    std::string date;
    std::cin >> date;
    std::string original_date = date;

    date.erase(std::remove(date.begin(), date.end(), '/'), date.end());

    if (date.length() == 8) {
        std::string year = date.substr(4, 4);
        std::string month = date.substr(2, 2);
        std::string day = date.substr(0, 2);
        date = year + month + day;
    } else {
        std::cerr << "Invalid date format. Please use dd/mm/yyyy." << std::endl;
        return;
    }
    std::cout << date << std::endl;
    std::cout << std::endl;
    std::cout << CYAN << "Your entry on date " << RESET << original_date << std::endl;

    read_daily_entry(date);
}

void UI::read_remaining(double calories){
    std::filesystem::path goal_path = "../db/goals.txt";
    std::ifstream goal_file(goal_path);
    std::string line;
    double calories_goal = 0;

    while(std::getline(goal_file, line)){
        if(line.find("Calories:") != std::string::npos){
            std::stringstream ss(line);
            std::string label;
            ss >> label >> calories_goal;
        }
    }

    double remaining_calories = calories_goal - calories;
    std::cout 
    << std::left 
    << std::setw(3) << ""
    << CYAN << "Remaining: " << RESET 
    << std::setw(59) << "" 
    << (calories > calories_goal ? RED : CYAN) 
    << remaining_calories 
    << RESET
    << std::endl;
}

void UI::read_meal_data(const std::string& date, const std::string& meal_name){
    std::unique_ptr<Dairy> dairy = std::make_unique<Dairy>();
    std::string entry_path = meal_name;
    std::vector<Food> entries = dairy->get_food_entries(date, entry_path);

    if(entries.empty()){
        return;
    }

    std::cout << std::string(128, '-') << std::endl;
    std::cout << std::left
        << std::setw(3) << "" 
        << std::setw(30) << "Name" 
        << std::setw(25) << "Brand"
        << std::setw(15) << "Amount(g)"
        << std::setw(15) << "Calories"
        << std::setw(15) << "Fat"
        << std::setw(15) << "Carbs"
        << std::setw(15) << "Protein"
        << CYAN << std::setw(15) << meal_name << RESET
        << std::endl;
    std::cout << std::endl;

    int i = 0;
    for(Food entry: entries){
        i++;
        std::cout << std::left
            << std::setw(3)  << std::to_string(i) + "."
            << std::setw(29) << entry.name
            << std::setw(26) << entry.brand
            << std::setw(15) << entry.amount
            << std::setw(15) << entry.calories
            << std::setw(15) << entry.fat
            << std::setw(15) << entry.carbs
            << std::setw(15) << entry.protein
            << std::endl;
    }

    Food meal = dairy->get_meal_total(date, entry_path);
    std::cout << std::left 
        << std::setw(3)  << ""
        << CYAN << std::setw(30) << meal.name
        << std::setw(25) << meal.brand
        << std::setw(15) << meal.amount
        << std::setw(15) << meal.calories
        << std::setw(15) << meal.fat
        << std::setw(15) << meal.carbs
        << std::setw(15) << meal.protein << RESET
        << std::endl;
}

void UI::enter_weight(){
    double weight;
    Parser parser;
    std::cout << "Enter weight: ";
    std::cin >> weight;
    std::string file_path = "../db/dailies/" + parser.create_date_stamp();

    create_directory(file_path);
    add_weight(file_path, weight);

    std::cin.ignore(1000, '\n');
}

void UI::read_weight(){
    auto weight = std::make_unique<Weight>();
    auto all_weight = weight->get_everyday_weight();
    
    int table_width = 27; 
    std::cout << std::string(table_width, '-') << std::endl;
    std::cout << CYAN << std::left << std::setw(12) << "Date" << RESET << "|" << CYAN << std::right << std::setw(14) << "Weight(kg)" << RESET << std::endl;
    std::cout << std::string(table_width, '-') << std::endl;

    for(const auto& entry: all_weight){
        std::cout <<std::left << std::setw(12) << entry.first << "|" << std::right << std::setw(11) << entry.second << " kg"<< std::endl;
    }

    std::cout << std::string(table_width, '-') << std::endl;
}

void UI::enter_height(){
    double height;
    std::cout << "Enter height: ";
    std::cin >> height;
    std::filesystem::path file_path = "../db/personal_data.txt";
    std::ofstream weightstream(file_path, std::ios_base::app);

    if(!weightstream) return;

    std::string data = "height: " + std::to_string(height);
    weightstream << data << std::endl;

    std::cout << "Successfully added height " << height << " to a database.";
} 

void UI::read_height(){
    double height = 0;
    std::filesystem::path file_path = "../db/personal_data.txt";
    std::fstream file(file_path); 
    std::string line;

    if(!file) return;

    while(std::getline(file, line)){
        if(line.find("height:") != std::string::npos){
            std::stringstream ss(line);
            std::string label;
            ss >> label >> height;
            std::cout << std::endl;
            std::cout << "Your height is: " << height << "cm"<< std::endl;
            break;
        }
    }
}

void UI::read_bmi(){
    std::unique_ptr<BmiCalculator> calculator = std::make_unique<BmiCalculator>();

    int age = 0;
    double height = 0.0;
    double weight = 0.0;
    char gender = 'm';
    
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cout << "Enter your gender m/f: ";
    std::cin >> gender;
    std::cout << "Enter height(cm): ";
    std::cin >> height;
    std::cout << "Enter weight(kg): ";
    std::cin >> weight;
    
    std::cout << std::endl;
    std::cout << CYAN << "BMI table for adults" << RESET << std::endl;
    std::cout << std::string(38, '-') << std::endl;
    std::cout << std::left << std::setw(20) << "Classification" << "|" << std::right << std::setw(10) << "BMI range - kg/m2" << std::endl;
    std::cout << std::string(38, '-') << std::endl;
    std::cout 
        << std::left << std::setw(20) << "Severe Thinness" << "|"<< std::setw(17) << std::right << "< 16" << std::endl
        << std::left << std::setw(20) << "Moderate Thinness" << "|" << std::setw(17) << std::right << "16 - 17" << std::endl
        << std::left << std::setw(20) << "Mild Thinness" << "|" << std::setw(17) << std::right << "17 - 18.5" << std::endl
        << std::left << std::setw(20) << "Normal" << "|" << std::setw(17) << std::right << "18.5 - 25" << std::endl
        << std::left << std::setw(20) << "Overweight" << "|" << std::setw(17) << std::right << "25 - 30" << std::endl
        << std::left << std::setw(20) << "Obese Class I" << "|" << std::setw(17) << std::right << "30 - 35" << std::endl
        << std::left << std::setw(20) << "Obese Class II" << "|" << std::setw(17) << std::right << "35 - 40" << std::endl
        << std::left << std::setw(20) << "Obese Class III" << "|" << std::setw(17) << std::right << "> 40" << std::endl;
    std::cout << std::string(38, '-') << std::endl;

    double bmi = calculator->get_bmi(age, gender, height, weight);

    std::string selected_gender = "Male"; 
    if(gender == 'm' || gender == 'M'){
        selected_gender = "Male";
    }
    if(gender == 'f' || gender == 'F'){
        selected_gender = "Female";
    }

    std::cout << "Your BMI is " << "(" << selected_gender << "): " << bmi << std::endl;

    std::string classification = calculator->get_classification(bmi);
    std::cout << "Your Classification is: " << classification << std::endl;
}
