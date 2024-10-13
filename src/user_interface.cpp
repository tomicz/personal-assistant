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

const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

void UI::start_program()
{
	set_header("Home");

    std::cout << "1. Diary." << std::endl;
	std::cout << "2. Health." << std::endl;
	std::cout << "(Q)uit application." << std::endl;
	
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
        default:
            std::cout << "Invalid command" << std::endl;
    }
}

void UI::set_header(std::string header_name)
{
    std::cout << std::endl;
	std::transform(header_name.begin(), header_name.end(), header_name.begin(), ::toupper);	
	std::cout << std::string(100, '-') << std::endl;
	std::cout << "--- " << CYAN << header_name << RESET << " " << std::string(96 - header_name.size()-1, '-') << std::endl;
	std::cout << std::string(100, '-') << std::endl;
    std::cout << std::endl;
}

void UI::open_health_menu(){
    set_header("Health Menu");
    std::string menu_options = "1. Enter Weight \n2. Read Weight \n3. Enter Height \n4. Read Height \n5. Read BMI \n(Q)uit";
    std::cout << menu_options;
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
        case 'Q':
           start_program(); 
            break;
        case 'q':
           start_program(); 
            break;
        default:
           start_program(); 
    }
}

void UI::open_food_database(bool show_as_list){
    Dairy* dairy = new Dairy();
    set_header("Food Database");
    std::string seperator = show_as_list ? "| " : "\n";
    std::string menu_options = 
        "1. Add " + seperator + 
        "2. Remove " + seperator +
        "3. Read " + seperator +
        "(Q)uit";
    std::cout << menu_options;
    std::cout << std::endl;
    std::cout << "Enter command: ";

    char command{};
    std::cin >> command;
    if(command == '1'){
        dairy->add_new_food(); 
        open_food_database(true);
        delete dairy;
    }
    else if(command == '2'){
        dairy->remove_food();
        open_food_database(true);
        delete dairy;
    }
    else if(command == '3'){
        read_db();                
        open_food_database(true);
    }
    else if(command == 'q'){

        open_dairy_menu();
    }
}

void UI::open_dairy_menu(){
    set_header("Dairy Menu");
    std::string menu_options = "1. Daily Entries \n2. Food Database \n(Q)uit";
    std::cout << menu_options;
    std::cout << std::endl;
    std::cout << "Enter command: ";

    char command{};
    std::cin >> command;
    switch(command){
        case '1':
            open_daily_entries_menu();
            break;
        case '2':
            open_food_database(false);
            break;
        case 'q':
            start_program();  
            break;
        case 'Q':
            start_program();  
            break;
        default: 
            start_program();  
    }
}

void UI::open_daily_entries_menu(){
    Dairy* dairy = new Dairy();
    set_header("Daily Entries Menu");
    std::string menu_options = "1. Add | 2. Read | (Q)uit";
    std::cout << menu_options;
    std::cout << std::endl;
    std::cout << "Enter command: ";

    char command{};
    std::cin >> command;
    switch(command){
        case '1':
            dairy->add_new_daily_entry();
            open_daily_entries_menu();
            delete dairy;
            break;
        case '2':
            read_daily_entry();
            open_daily_entries_menu();
            delete dairy;
            break;
        case 'q':
            open_dairy_menu();
            break;
        case 'Q':
            open_dairy_menu();
            break;
        default: 
            open_dairy_menu();
    }
}
void UI::read_daily_entry(){
    const std::string CYAN = "\033[36m";
    const std::string RESET = "\033[0m";
    std::cout << std::endl;
    std::cout << CYAN << "YOUR DAILY ENTRIES" << RESET;
    std::cout << std::endl;
    read_meal_data("breakfast");
    read_meal_data("lunch");
    read_meal_data("dinner");

    std::cout << std::string(128, '-') << std::endl;
    Dairy* dairy = new Dairy();
    Food* total = dairy->get_total_all_meals();
    std::cout << std::left 
        << std::setw(3)  << ""
        << CYAN << std::setw(30) << total->name
        << std::setw(25) << total->brand
        << std::setw(15) << total->amount
        << std::setw(15) << total->calories
        << std::setw(15) << total->fat
        << std::setw(15) << total->carbs
        << std::setw(15) << total->protein << RESET
        << std::endl;

    std::cout << std::string(128, '-') << std::endl;

}

void UI::read_meal_data(std::string meal_name){
    const std::string CYAN = "\033[36m";
    const std::string RESET = "\033[0m";
    Dairy* dairy = new Dairy();
    std::string entry_path = meal_name;
    std::vector<Food*> entries = dairy->get_food_entries(entry_path);
    if(entries.empty()){
        delete dairy;
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
    for(Food* entry: entries){
        i++;
        std::cout << std::left
            << std::setw(3)  << std::to_string(i) + "."
            << std::setw(29) << entry->name
            << std::setw(26) << entry->brand
            << std::setw(15) << entry->amount
            << std::setw(15) << entry->calories
            << std::setw(15) << entry->fat
            << std::setw(15) << entry->carbs
            << std::setw(15) << entry->protein
            << std::endl;
    }
    Food* meal = dairy->get_meal_total(entry_path);
    std::cout << std::left 
        << std::setw(3)  << ""
        << CYAN << std::setw(30) << meal->name
        << std::setw(25) << meal->brand
        << std::setw(15) << meal->amount
        << std::setw(15) << meal->calories
        << std::setw(15) << meal->fat
        << std::setw(15) << meal->carbs
        << std::setw(15) << meal->protein << RESET
        << std::endl;


    delete dairy;
}

void UI::enter_weight(){
    double weight;
    std::cout << "Enter weight: ";
    std::cin >> weight;
    std::string file_path = "../db/dailies/" + create_date_stamp();

    create_directory(file_path);
    add_weight(file_path, weight);

    std::cin.ignore(1000, '\n');
}

void UI::read_weight(){
    set_header("Total weight entries");
    Weight* weight = new Weight();
    weight->get_weight_all();
    for(std::string entry: weight->get_weight_all()){
        std::cout << entry << "\n";
    }
    delete weight;
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
    BmiCalculator* calculator = new BmiCalculator();

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

    delete calculator;
}
