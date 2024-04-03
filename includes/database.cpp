#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "database.h"

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
