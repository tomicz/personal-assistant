#include <iostream>
#include <fstream>
#include <string>

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
