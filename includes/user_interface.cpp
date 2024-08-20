#include <iostream>
#include <string>
#include "database.h"
#include "user_interface.h"

void create_folder();
void create_file();

void start_program()
{
	set_header("Home");
	std::cout << std::endl;

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
            std::cout << "Invalid command entered." << std::endl;
            break;
    }

}

void open_menu_home(std::string &command)
{
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "COMMAND LINE INFORMATION" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "1. Diary." << std::endl;
	std::cout << "2. Health." << std::endl;
	std::cout << "3. Enter weight." << std::endl;
	std::cout << "4. Enter goals." << std::endl;
	std::cout << "5. Help." << std::endl;
	std::cout << "6. Settings." << std::endl;
	std::cout << "Enter q to quit application." << std::endl;
	std::cout << "Enter command: ";
    std::getline(std::cin, command);
}

void open_menu_settings()
{
	set_header("Header");
	std::cout << "Use this menu to create and remove program folders and files." << std::endl;
	std::cout << std::endl;

	std::cout << "1. Create folder." << std::endl;
	std::cout << "2. Delete folder." << std::endl;
	std::cout << "3. Create database file." << std::endl;
	std::cout << "4. Delete database file." << std::endl;
	std::cout << std::endl;
	
	std::cout << "Select options: ";
    char command{};
    std::cin >> command;

    switch(command) 
	{
        case '1':
			create_folder();
            break;
        case '2':
            // Do something for case '2'
            break;
        case '3':
           	create_file(); 
            break;
        case '4':
            // Do something for case '4'
            break;
        default:
            std::cout << "Invalid command entered." << std::endl;
            break;
    }
}

void create_folder()
{
	std::string file_path{};
	std::cout << "Enter directory path: ";
	std::cin >> file_path;

	create_directory(file_path);
	std::cout << "Successfully created a directory at path: " << file_path << std::endl;
}

void create_file()
{
	std::string file_path{};
	std::cout << "Enter path: ";
	std::cin >> file_path;

	std::string file_name{};
	std::cout << "Enter name: ";
	std::cin >> file_name;

	create_db_file(file_path, file_name);
	std::cout << "Successfully created a database file at path: " << file_path << std::endl;
}

void add_category(std::string &category_name)
{
	std::string file_path = "db/";
	std::string file_name = "categories_list";
	write_to_file(file_path, file_name, category_name);		
}

void set_header(std::string header_name)
{
	std::transform(header_name.begin(), header_name.end(), header_name.begin(), ::toupper);	
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << header_name << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
}
