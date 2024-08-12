#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sys/wait.h>
#include <vector>
#include "database.h"
#include <filesystem>

namespace fs = std::filesystem;

void write_to_file(std::string file_path, std::string file_name, std::string data)
{
	std::ofstream file(file_path + file_name + ".txt", std::ios::app);
	
	if(file.is_open())
	{
		file << data << std::endl;
	}

	file.close();
}

void create_db_file(std::string file_path, std::string file_name)
{
	std::ofstream file(file_path + file_name + ".txt", std::ios::app);
	std::cout << "Created a file " << file_name << " at path " << file_path << std::endl;
}

std::string remove_symbols(const std::string& input) 
{
    std::string result;
	
    for (char c : input)
	{
        if (std::isalnum(c)) 
		{
            result += c;
        }
    }

    return result;
}

void create_directory(const std::string& file_path)
{
	if(!fs::exists(file_path))
	{
		fs::create_directories(file_path);		
	}
}

std::string create_date_stamp()
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
	std::string date = remove_symbols(date_string);

	return date;
}

int get_database_size()
{
	int count{};
	std::ifstream database("db/db.txt");
	std::string line;

	while(std::getline(database, line))
	{
		count++;	
	}

	return count;
}

void remove_element_at_index()
{
	std::ifstream database("db/db.txt");
	std::ofstream temp_database("temp_database.txt");

	if(!database || !temp_database)
	{
		std::cout << "Error: Cannot open database";
	}

	read_db(true);
	int index{};
	int i{};

	std::cout << "Enter food index: ";
	std::cin >> index;

	std::string temp_line{};
	std::string line_to_delete{};

	while(std::getline(database, temp_line))
	{
		if(index == i)
		{
			line_to_delete = get_element_from_db(index);	
			break;
		}
		
		i++;
	}

	while(std::getline(database, temp_line))
	{
		if(temp_line != line_to_delete)
		{
			temp_database << temp_line << std::endl;
		}
	}

	std::cout << "Line deleted: " << line_to_delete << std::endl;

	database.close();
	temp_database.close();

	remove("db/db.txt");
	rename("temp_database.txt", "db.txt");	
}

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
    std::ifstream database("db/db.txt");
    
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
    std::ifstream database("db/db.txt");
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

void write_to_table(std::string &file_path, std::string &data)
{
	std::ofstream entry(file_path, std::ios::app);

	entry << data + "\n";
	entry.close(); 

	std::cout << "Added data to a database " << data << std::endl;
}

void add_weight(std::string &file_path, const double &weight)
{
    std::ofstream daily_entry(file_path + "/daily_entry.txt", std::ios::app);

	daily_entry << "weight: " << weight << "\n";
    daily_entry.close();

    std::cout << "Added weight to daily entry." << std::endl;
}

void write_to_db(const std::string &item_data)
{
    std::ofstream database ("db/db.txt", std::ios::app);

	int count = get_database_size();
	
	if(count <= 0)
	{
    	database << item_data;    
	}else
	{
		database << "\n" << item_data; 
	}

    database.close();
    std::cout << "Added an item to database." << std::endl;
}
