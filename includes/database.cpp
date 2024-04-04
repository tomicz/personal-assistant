#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "database.h"

std::string modify_data_at_index(int index, std::string &data)
{
	int current_index = 0;
	int current_comma_index = {};
	int next_comma_index {};

	for(size_t i = 0; i < data.length(); i++)
	{
		if(data[i] == ',')
		{
			if(current_index == index - 1)
			{
				current_comma_index = i; 
				break;
			}
		
			current_index++;
		}
	}
	
	for(size_t i = current_comma_index + 2; i < data.length(); i++)
	{
		if(data[i] == ',')
		{
			next_comma_index = i;
			break;
		}
	}
	
	double amount{};
	
	std::cout << "Enter amount(g): " << std::endl;
	std::cin >> amount;	
	
	current_comma_index +=  2;
	next_comma_index -= 2;
	data.replace(current_comma_index, next_comma_index - current_comma_index, std::to_string(amount));

	return data;
}

void read_db(bool ordered)
{
    std::ifstream database("db.txt");
    
    if(!database.is_open())
    {
        std::cout << "Error: File stream is not open" << std::endl;
    }
    
    std::vector<std::string> lines;
    std::string line;
    
    while(std::getline(database, line))
    {
        lines.push_back(line);     
    }

    database.close();

    for(size_t i = 0; i < lines.size(); i++)
    {
        std::cout << std::fixed << std::setprecision(1);

		if(!ordered)
		{
        	std::cout << lines.at(i) << ::std::endl;
		}
		else
		{
        	std::cout << i << ": " << lines.at(i) << ::std::endl;
		}
    }
}


std::string get_element_from_db(int index)
{
    std::ifstream database("db.txt");
    std::vector<std::string> lines;
    std::string line;
    
    while(std::getline(database, line))
    {
        lines.push_back(line);     
    }

    database.close();

    for(int i = 0; i <= index; i++)
    {
		if(i == index)
		{
			line = lines.at(i);
			break;
		}
    }

	return line;
}

void write_to_db(const std::string &itemData)
{
    std::ofstream database ("db.txt", std::ios::app);
    database << "\n" << itemData;    
    database.close();
    std::cout << "Added an item to database." << std::endl;
}
