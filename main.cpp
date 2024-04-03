#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <ctime>
#include <filesystem>
#include "includes/database.h"
#include "includes/helpers.h"

namespace fs = std::filesystem;

std::string add_meal_entry()
{
	std::cout << "Select a meal from database by entering a number" << std::endl;
	read_db(true);
	std::cout << "Enter meal number: ";

	int option{};
	
	std::cin >> option;
	std::cout << "You selected: " << option << std::endl;
	
	std::string result = get_element_from_db(option);
	std::cout << result << std::endl;

	return result;
}

std::string get_meal_time()
{
	std::cout << "Select:" << std::endl;
	std::cout << "1. Breakfast" <<std::endl;	
	std::cout << "2. Lunch" <<std::endl;	
	std::cout << "3. Dinner" <<std::endl;	

	char option{};

	std::cout << "Enter option: ";
	std::cin >> option;
	
	if(option == '1')
	{
		return "Breakfast";
	}
	else if(option == '2')
	{
		return "Lunch";
	}
	else if(option == '3')
	{
		return "Dinner";	
	}

	return "Invalid option";
}

void create_directory(const std::string& file_path)
{
	if(!fs::exists(file_path))
	{
		fs::create_directories(file_path);		
	}
}

void add_new_daily_entry()
{
    std::time_t date_now = std::time(0);
    std::tm* time = std::localtime(&date_now);

    int year = time->tm_year + 1900;
    int month = time->tm_mon + 1;
    int day = time->tm_mday;

    std::string year_str = std::to_string(year);
    std::string month_str = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
    std::string day_str = (day < 10) ? "0" + std::to_string(day) : std::to_string(day);
    std::string date_string = year_str + "-" + month_str + "-" + day_str;
	
	std::string file_path = "db/" + remove_symbols(date_string) + "/";
	
	create_directory(file_path);
	std::cout << file_path << std::endl;
	std::string meal_data = add_meal_entry();
	
    std::ofstream timestamp(file_path + get_meal_time() + ".txt", std::ios::app);
	timestamp << '\n' << meal_data;
	timestamp.close();
}

void read_help()
{
    std::cout << "Commands are: " << std::endl;
    std::cout << "(A)dd" << std::endl;
    std::cout << "(N)ew" << std::endl;
    std::cout << "(R)ead" << std::endl;
    std::cout << "(H)elp" << std::endl;
    std::cout << "(Q)uit" << std::endl;
}

void add_calories()
{
    std::string item_name;
    std::string brand_name;
    float quantity = {0};
    float calories = {0};
    float fat = {0};
    float carbohydrates = {0};
    float protein = {0};
    std::string itemData;
    
    std::cout << "Enter item name: ";
    std::getline(std::cin, item_name);

    std::cout << "Enter brand name: ";
    std::getline(std::cin, brand_name);
	
    std::cout << "Enter quantity:";
    std::cin >> quantity;

    std::cout << "Enter calories per 100g: ";
    std::cin >> calories;  

    std::cout << "Enter fat per 100g: ";
    std::cin >> fat;

    std::cout << "Enter carbohydrates per 100g: ";
    std::cin >> carbohydrates;
    
    std::cout << "Enter protein per 100g: ";
    std::cin >> protein;

    std::cout << "You added item " << item_name << std::endl;
    
    std::cout << "Brand: " << brand_name << std::endl;
    std::cout << "Quantity: " << quantity << " units" << std::endl;
    std::cout << "Calories: " << calories << "g" << std::endl;
    std::cout << "Fat: " << fat << "g" << std::endl;
    std::cout << "Carbohydrates: " << carbohydrates << "g" << std::endl;
    std::cout << "Protein: " << protein << "g" << std::endl;

    itemData = item_name + ", "
        + brand_name 
        +  ", "+ std::to_string(quantity) 
        + ", " + std::to_string(calories) 
        + ", " + std::to_string(fat) 
        + ", " + std::to_string(carbohydrates) 
        + ", " + std::to_string(protein);

    write_to_db(itemData);
}

void start_application()
{
    std::string command = "";
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "COMMAND LINE INFORMATION" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "1. Type command (A)dd to start the applicaiton." << std::endl;
    std::cout << "2. To add a new day entry type (N)ew." << std::endl;
    std::cout << "3. Read database (R)ead." << std::endl;
	std::cout << "4. Enter (H)elp for help." << std::endl;
	std::cout << "5. To quit enter (Q)uit." << std::endl;
	std::cout << "Enter command: ";
    std::getline(std::cin, command);

    if(command == "a" || command == "A")
    {
        std::cout << "To add new items to database, enter required information requested below." << std::endl;
        add_calories();
    }
    else if(command == "h" || command == "H")
    { 
		read_help();
    }
    else if(command == "n" || command == "N")
    {
		add_new_daily_entry();
    }
    else if(command == "r" || command == "R")
    {
        read_db(false);
    }
    else if(command == "q" || command == "Q")
    {
        std::cout << "Exited application. Copyright @ Tomicz Engineering LLC" << std::endl;
    }else
	{
		std::cout << "Command does not exist, please try another." << std::endl;
	}
}

int main()
{
    clock_t start;
    clock_t end;

    start = clock();
    std::cout << "\n";
    std::cout << "Copyright @ Tomicz Engineering LLC" << std::endl;
    std::cout << "Visit our website at tomiczengineering.com for more information." << std::endl;
    std::cout << "\n";

    start_application();

    end = clock();

    double timeToExecute = double(end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Time to execute: " << timeToExecute << std::endl;

    return 0;
}
