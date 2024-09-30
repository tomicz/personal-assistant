#include <iostream>
#include <fstream>
#include <string>

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

void read_file(std::string &file_path)
{
	std::ifstream file(file_path);
	
	if(!file)
	{
		std::cerr << "File does not exist at this path" << std::endl;
		std::cerr << "File path: " << file_path << std::endl;
		return;
	}
	std::string output {};

	while(std::getline(file, output))	
	{
		std::cout << output << std::endl;
	}
}

std::string create_date_stamp() {
    std::time_t date_now = std::time(0);
    std::tm* time = std::localtime(&date_now);

    int year = time->tm_year + 1900;   
    int month = time->tm_mon + 1;      
    int day = time->tm_mday;

    std::string year_str = std::to_string(year);
    std::string month_str = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
    std::string day_str = (day < 10) ? "0" + std::to_string(day) : std::to_string(day);

    std::string date_string = year_str + month_str + day_str;

    return date_string;
}

std::string convert_to_date(const std::string& file_name) {
    if (file_name.length() != 8) {
        return "Invalid folder name format";
    }

    std::string year = file_name.substr(0, 4);   
    std::string month = file_name.substr(4, 2);  
    std::string day = file_name.substr(6, 2);    

    int day_int = std::stoi(day);
    int month_int = std::stoi(month);
    int year_int = std::stoi(year);

    std::tm time_in = {0, 0, 0, day_int, month_int - 1, year_int - 1900};  // month is 0-based in std::tm

    char buffer[100];

    std::strftime(buffer, sizeof(buffer), "%d %B %Y", &time_in);

    return std::string(buffer);
}
