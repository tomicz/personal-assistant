#include <iostream>
#include <string>
#include "helpers.h"

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
