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
	std::cout << "5. Help." << std::endl;
	std::cout << "6. Settings." << std::endl;
	std::cout << "Enter q to quit application." << std::endl;
	
	std::cout << "Select options: ";
    char command{};

    std::cin >> command;
    switch(command) 
    {
        case '1':
            open_dairy_menu(false);
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

void UI::open_dairy_menu(bool show_as_list){
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
        open_dairy_menu(true);
        delete dairy;
    }
    else if(command == '2'){
        dairy->remove_food();
        open_dairy_menu(true);
    }
    else if(command == '3'){
        read_db();                
        open_dairy_menu(true);
    }
    else if(command == 'q'){
        start_program();
    }
}
