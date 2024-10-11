#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <ctime>
#include "../include/database.h"
#include "../include/blood_pressure_controller.h"
#include "../include/parser.h"
#include "../include/user_interface.h"
#include "../include/dairy.h"
#include "../include/weight.h"

void start_application();
void read_commands(std::string &command);
UI ui;

void read_diary_options()
{
	std::cout << "1. Add food to a database." << std::endl;
	std::cout << "2. Remove food from database." << std::endl;
	std::cout << "3. Read food database." << std::endl;
	std::cout << "4. Add daily entry." << std::endl;
	std::cout << "5. Read daily entry." << std::endl;
	std::cout << "Enter q to go back." << std::endl;
}

void enter_goals() 
{
	double goal_weight;
	std::cout << "Enter goal weight:";
	std::cin >> goal_weight; 

	double calories_goal;
	std::cout << "Enter calories daily goal:";
	std::cin >> calories_goal; 

	std::string file_path = "db/dailies/";
	create_directory(file_path);
	create_db_file(file_path, "goals");
	write_to_file(file_path, "goals", "goal weight, " + std::to_string(goal_weight));
	write_to_file(file_path, "goals", "calories goal, " + std::to_string(calories_goal));
}

std::string add_meal_entry()
{
	std::cout << "Select a meal from database by entering a number" << std::endl;
	read_db();
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
		return "breakfast";
	}
	else if(option == '2')
	{
		return "lunch";
	}
	else if(option == '3')
	{
		return "dinner";	
	}

	return "Invalid option";
}

void add_new_daily_entry()
{
	std::string file_path = "db/dailies/" + create_date_stamp() + "/";
	
	create_directory(file_path);
	std::cout << file_path << std::endl;
	std::string meal_data = add_meal_entry() + "\n";
	
    std::ofstream timestamp(file_path + get_meal_time() + ".txt", std::ios::app);
	timestamp << meal_data;
	timestamp.close();
}

void read_help()
{
	ui.set_header("Help");	

    std::cout << "Commands: " << std::endl;
    std::cout << "1. Food database and dairy entries." << std::endl;
    std::cout << "2. Blood pressure and pulse." << std::endl;
    std::cout << "3. Enter current weight. Only once per day." << std::endl;
	std::cout << "4. Enter goals like weight." << std::endl;
    std::cout << "5. Get description of all commands." << std::endl;
    std::cout << "6. Settings menu allows to create new folders and database files." << std::endl;
    std::cout << "To quit application enter lower case q" << std::endl;

	start_application();
}

void read_meal_data(std::string meal_name){
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

void start_diary()
{
	read_diary_options();	

	char selected_option{};
	char exit_condition = 'q';

	do{
		std::cout << "Select option: ";	
		std::cin >> selected_option;

		if(selected_option == '3')
		{
			read_db();
			read_diary_options();	
		}
		else if(selected_option == '4')
		{
			add_new_daily_entry();
			read_diary_options();	
		}
		else if(selected_option == '5')
		{
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
            delete dairy;
		}
	}while(selected_option != exit_condition);

	std::cin.ignore(1000, '\n');
	start_application();
}

void start_application()
{
	std::string command{}; 
	//ui.open_menu_home(command);

	if(command == "1")
	{
		start_diary();
	}
	else if(command == "5")
	{ 
		read_help();
	}
	else if(command == "q")
	{
		std::cout << "Application closed" << std::endl;	
	}
	else if(command == "3")
	{
		double weight;
		std::cout << "Enter weight: ";
		std::cin >> weight;
		std::string file_path = "db/dailies/" + create_date_stamp();

		create_directory(file_path);
		add_weight(file_path, weight);

		std::cin.ignore(1000, '\n');
		start_application();	
	}
	else if(command == "4")
	{
		enter_goals();	
		std::cin.ignore(1000, '\n');
		start_application();
	}
	else if(command == "2")
	{
		std::cout << "This is medical panel where you can see all your medical information. Select options below." << std::endl;
		std::cout << "1. Enter blood pressure" << std::endl;
		std::cout << "2. Enter pulse" << std::endl;
		std::cout << "3. Read" << std::endl;
		std::cout << "4. Read weight entries" << std::endl;
		std::cout << "q. Back" << std::endl;
		
		char selected_option = 0;
		const char exit_condition = 'q';

		do{
			std::cout << "Select option: ";	
			std::cin >> selected_option;

			if(selected_option == '1')
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
			else if(selected_option == '2')
			{
				int pulse = 0;
				std::cout << "Enter pulse: ";
				std::cin >> pulse;

				enter_pulse(pulse);

				std::cout << "You entered pulse: " << pulse << std::endl;	

				selected_option = exit_condition;
			}
			else if(selected_option == '3')
			{
				std::string date = create_date_stamp();
				std::string file_path = "db/dailies/" + date + "/" + "daily_entry.txt";	

				ui.set_header("Daily health data");
				read_file(file_path);
			}
			else if(selected_option == '4')
			{
				ui.set_header("Total weight entries");
                Weight* weight = new Weight();
                weight->get_weight_all();
                for(std::string entry: weight->get_weight_all()){
                    std::cout << entry << "\n";
                }
                delete weight;
			}
		}while(selected_option != exit_condition);
		
		std::cin.ignore(1000, '\n');
		start_application();	
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
    std::cout << "Visit tomiczengineering.com for more information." << std::endl;
    
    ui.start_program();

    end = clock();

    double timeToExecute = double(end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Time to execute: " << timeToExecute << std::endl;

    return 0;
}
