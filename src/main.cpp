#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include "../include/database.h"
#include "../include/blood_pressure_controller.h"
#include "../include/parser.h"
#include "../include/user_interface.h"

void start_application();
void read_commands(std::string &command);
UI ui;

void start_application()
{
	std::string command{}; 

	if(command == "2")
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
