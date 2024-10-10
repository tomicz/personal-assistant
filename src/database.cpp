#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sys/wait.h>
#include <vector>
#include <filesystem>
#include <sstream>
#include "database.h"
#include "dairy.h"

namespace fs = std::filesystem;

const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

void write_to_file(std::string file_path, std::string file_name, std::string data)
{
	std::ofstream file(file_path + file_name + ".txt", std::ios::app);

	if(!file)
	{
		std::cerr << "File path does not exist: " << file_path << file_name << std::endl;
	}
	
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

void create_directory(const std::string& file_path)
{
	if(!fs::exists(file_path))
	{
		fs::create_directories(file_path);		
	}
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

void display_lines_with_indices(std::ifstream& file)
{
    int index = 0;
    std::string line;
    while (std::getline(file, line))
    {
        std::cout << index << ": " << line << std::endl;
        ++index;
    }
}

void remove_element_at_index()
{
    std::ifstream database("db/db.txt");
    std::ofstream temp_database("temp_database.txt");

    if (!database || !temp_database)
    {
        std::cout << "Error: Cannot open database" << std::endl;
        return;
    }

    // Display all lines with indices
    std::cout << "Current entries in the database:\n";
    display_lines_with_indices(database);

    // Reopen the file to reset the read position
    database.clear(); // Clear EOF and other flags
    database.seekg(0); // Rewind to the beginning of the file

    char user_choice;
    std::cout << "\nEnter 'q' to quit or any other key to proceed: ";
    std::cin >> user_choice;

    if (user_choice == 'q' || user_choice == 'Q')
    {
        std::cout << "Operation cancelled.\n";
        return;
    }

    int index{};
    std::cout << "\nEnter food index to delete: ";
    std::cin >> index;

    std::string temp_line{};
    int current_index = 0;
    bool line_deleted = false;

    while (std::getline(database, temp_line))
    {
        if (current_index == index)
        {
            std::cout << "Line deleted: " << temp_line << std::endl;
            line_deleted = true;
        }
        else
        {
            temp_database << temp_line << std::endl;
        }
        ++current_index;
    }

    if (!line_deleted)
    {
        std::cout << "Error: Invalid index. No line was deleted." << std::endl;
    }

    database.close();
    temp_database.close();

    // Replace the original file with the modified file
    remove("db/db.txt");
    rename("temp_database.txt", "db/db.txt");
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

void read_db()
{
    std::cout << std::endl;
    std::cout << CYAN << "FOOD DATABASE" << RESET << std::endl;
    std::ifstream database("db/db.txt");
    
    if(!database.is_open())
    {
        std::cout << "Error: File stream is not open" << std::endl;
    }
    
    std::vector<Food*> entries;
    std::string line;
    
    while (std::getline(database, line)) {
        std::stringstream ss(line); 
        Food* entry = new Food();
        std::getline(ss, entry->name, ','); 
        std::getline(ss, entry->brand, ',');
        ss >> entry->amount;
        ss.ignore(1);
        ss >> entry->calories;
        ss.ignore(1);
        ss >> entry->fat;
        ss.ignore(1); 
        ss >> entry->carbs; 
        ss.ignore(1);
        ss >> entry->protein; 
        entries.push_back(entry);
    }

    database.close();

    std::cout << std::string(140, '-') << std::endl;
    std::cout << std::left
        << std::setw(5) << "" 
        << std::setw(40) << "Name" 
        << std::setw(25) << "Brand"
        << std::setw(15) << "Amount(g)"
        << std::setw(15) << "Calories"
        << std::setw(15) << "Fat"
        << std::setw(15) << "Carbs"
        << std::setw(15) << "Protein"
        << std::endl;
    std::cout << std::string(140, '-') << std::endl;

    for(size_t i = 0; i < entries.size(); i++)
    {
        std::cout 
            << std::left
            << CYAN << std::setw(5) << i << RESET
            << std::setw(40) << entries[i]->name 
            << std::setw(25) << entries[i]->brand
            << std::setw(15) << entries[i]->amount
            << std::setw(15) << entries[i]->calories
            << std::setw(15) << entries[i]->fat
            << std::setw(15) << entries[i]->carbs
            << std::setw(15) << entries[i]->protein
            << std::endl;
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

	std::string formattedData = "weight: " + std::to_string(weight) + "\n";

	daily_entry << formattedData;
    daily_entry.close();

    std::cout << "Added weight to daily entry." << std::endl;
}

void write_to_db(const std::string &item_data)
{
    std::ofstream database ("db/db.txt", std::ios::app);
	std::string formatted_data = item_data + "\n";

    database << formatted_data;    
    database.close();

    std::cout << "Added an item to database." << std::endl;
}
