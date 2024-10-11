#include <iostream>
#include <string>
#include "../include/database.h"
#include "../include/user_interface.h"
#include "../include/dairy.h"

const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

void UI::start_program()
{
	set_header("Home");

    std::cout << "1. Diary." << std::endl;
	std::cout << "2. Health." << std::endl;
	std::cout << "3. Enter weight." << std::endl;
	std::cout << "4. Enter goals." << std::endl;
	std::cout << "Enter q to quit application." << std::endl;
	
	std::cout << "Select options: ";
    char command{};

    std::cin >> command;
    switch(command) 
    {
        case '1':
            open_dairy_menu();
            break;
        case '2':

            break;
        case '3':
            break;
        case '4':
            // Do something for case '4'
            break;
        case '5':
            // Do something for case '4'
            break;
        case '6':
            // Do something for case '4'
            break;
        default:
            std::cout << "Invalid command" << std::endl;
            break;
    }
}

void UI::open_menu_home()
{
    set_header("Home");
    std::cout << "1. Diary." << std::endl;
	std::cout << "2. Health." << std::endl;
	std::cout << "3. Enter weight." << std::endl;
	std::cout << "4. Enter goals." << std::endl;
	std::cout << "5. Help." << std::endl;
	std::cout << "6. Settings." << std::endl;
	std::cout << "Enter q to quit application." << std::endl;
	std::cout << "Enter command: ";
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
