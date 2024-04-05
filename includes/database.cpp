#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "database.h"

int get_comma_index(int at_index, std::string &data)
{
	int current_index{};
	int current_comma_index{};

	for(int i = 0; i < data.length(); i++)
	{
		if(data[i] == ',' )
		{
			if(current_index == at_index)
			{
				current_comma_index = i; 
				break;
			}
		
			current_index++;
		}else
		{
			current_comma_index = data.length() - 1;
		}
	}

	return current_comma_index;
}

std::string modify_data_at_index(int index, std::string &data)
{
	std::string value_str{};

	int current_comma = get_comma_index(index, data);
	int next_comma = get_comma_index(index + 1, data);
	
	for(int i  = current_comma + 2; i < next_comma; i++)
	{
		value_str += data[i];
	}

	return value_str; 
}

void enter_new_data_at_index(int index, double amount, std::string &data)
{
	int current_comma = get_comma_index(index, data);
	int next_comma = get_comma_index(index + 1, data);
	int string_length = next_comma - current_comma;
	
	data.replace(current_comma + 2, string_length - 2, std::to_string(amount));
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
