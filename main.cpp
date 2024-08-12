#include <iostream>
#include <random>
#include <string>
#include <time.h>
#include <fstream>
#include <ctime>
#include "includes/database.h"
#include "includes/blood_pressure_controller.h"

void enter_goals() 
{
	double goal_weight;
	std::cout << "Enter goal weight:";
	std::cin >> goal_weight; 

	double calories_goal;
	std::cout << "Enter calories daily goal:";
	std::cin >> calories_goal; 

	std::string file_path = "db/";
	create_directory(file_path);
	create_db_file(file_path, "goals");
	write_to_file(file_path, "goals", "goal weight, " + std::to_string(goal_weight));
	write_to_file(file_path, "goals", "calories goal, " + std::to_string(calories_goal));
}

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

	double amount{};
	std::cout << "Enter amount(g): ";
	std::cin >> amount;

	std::string calories = modify_data_at_index(2, result);
	std::string fat = modify_data_at_index(3, result);
	std::string ug = modify_data_at_index(4, result);
	std::string protein = modify_data_at_index(5, result);

	double calories_formula = std::stod(calories) / 100.0 * amount;
	double fat_formula = std::stod(fat) / 100.0 * amount;
	double ug_formula = std::stod(ug) / 100.0 * amount;
	double protein_formula = std::stod(protein) / 100.0 * amount;

	enter_new_data_at_index(1, amount, result); 
	enter_new_data_at_index(2, calories_formula, result); 
	enter_new_data_at_index(3, fat_formula, result); 
	enter_new_data_at_index(4, ug_formula, result); 
	enter_new_data_at_index(5, protein_formula, result); 

	std::cout << "Data: " << result << std::endl;

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
    std::string date_string = day_str + "-" + month_str + "-" + year_str;
	
	std::string file_path = "db/" + remove_symbols(date_string) + "/";
	
	create_directory(file_path);
	std::cout << file_path << std::endl;
	std::string meal_data = add_meal_entry();
	
    std::ofstream timestamp(file_path + get_meal_time() + ".txt", std::ios::app);
	timestamp << meal_data << '\n';
	timestamp.close();
}

void read_help()
{
    std::cout << "Commands: " << std::endl;
    std::cout << "1. (A)dd - Add new food to a database." << std::endl;
    std::cout << "2. (H)elp - Get help." << std::endl;
    std::cout << "3. (N)ew - Enter food into a dairy." << std::endl;
    std::cout << "4. (R)ead - Read all food data in database." << std::endl;
	std::cout << "5. (E)nter your weight(kg)." << std::endl;
	std::cout << "6. (D)elete - Delete food from database." << std::endl;
    std::cout << "7. (Q)uit" << std::endl;
	std::cout << "8. Enter weight and calorie goals." << std::endl;
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
	std::string command{}; 
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "COMMAND LINE INFORMATION" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "1. (A)dd to database." << std::endl;
	std::cout << "2. (H)elp." << std::endl;
    std::cout << "3. (N)ew to create a new daily entry." << std::endl;
    std::cout << "4. (R)ead database." << std::endl;
	std::cout << "5. (E)nter weight." << std::endl;
	std::cout << "6. (D)elete element." << std::endl;
	std::cout << "7. (Q)uit." << std::endl;
	std::cout << "8. Enter goals." << std::endl;
	std::cout << "9. Health." << std::endl;
	std::cout << "Enter command: ";
    std::getline(std::cin, command);

	if(command == "a" || command == "A" || command == "1")
	{
		std::cout << "To add new items to database, enter required information requested below." << std::endl;
		add_calories();
	}
	else if(command == "h" || command == "H" || command == "2")
	{ 
		read_help();
	}
	else if(command == "n" || command == "N" || command == "3")
	{
		add_new_daily_entry();
	}
	else if(command == "r" || command == "R" || command == "4")
	{
		read_db(false);
	}
	else if(command == "q" || command == "Q" || command == "7")
	{
		std::cout << "Application closed" << std::endl;	
	}
	else if(command == "e" || command == "E" || command == "5")
	{
		double weight;
		std::cout << "Enter weight: ";
		std::cin >> weight;
		std::string file_path = "db/" + create_date_stamp();

		create_directory(file_path);
		add_weight(file_path, weight);

		std::cin.ignore(1000, '\n');
		start_application();	
	}
	else if(command == "8")
	{
		enter_goals();	
	}
	else if(command == "9")
	{
		std::cout << "This is medical panel where you can see all your medical information. Select options below." << std::endl;
		std::cout << "1. Enter blood pressure" << std::endl;
		std::cout << "2. Enter pulse" << std::endl;
		std::cout << "3. Back" << std::endl;
		
		int selected_option = 0;
		const int exit_condition = 3;

		do{
			std::cout << "Select option: ";	
			std::cin >> selected_option;

			if(selected_option == 1)
			{
				int sys = 0;
				std::cout << "Enter SYS: ";	
				std::cin >> sys; 

				int dia = 0;
				std::cout << "Enter DIA: ";	
				std::cin >> dia; 

				enter_sys_and_dia(sys, dia);

				std::cout << "You entered SYS: " << sys << " and DIA: " << dia << std::endl;

				selected_option = exit_condition;
			}
			else if(selected_option == 2)
			{
				int pulse = 0;
				std::cout << "Enter pulse: ";
				std::cin >> pulse;

				enter_pulse(pulse);

				std::cout << "You entered pulse: " << pulse << std::endl;	

				selected_option = exit_condition;
			}
		}while(selected_option != exit_condition);
		
		std::cin.ignore(1000, '\n');
		start_application();	
	}
	else if(command == "d" || command == "D" || command == "6")
	{
		remove_element_at_index();	
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
