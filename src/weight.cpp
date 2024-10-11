#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "../include/weight.h"
#include "../include/parser.h"

namespace fs = std::filesystem;

std::vector<std::string> Weight::get_weight_all() {
    std::string file_path = "../db/dailies/";
    std::vector<std::pair<std::string, std::string>> weight_entries;

    try {
        for (const auto& entry : fs::directory_iterator(file_path)) {
            if (fs::is_directory(entry.status())) {
                std::string directory_name = entry.path().filename().string();
                
                std::string full_directory_path = file_path + directory_name + "/daily_entry.txt";
                std::ifstream daily_file(full_directory_path);
                
                if (!daily_file.is_open()) {
                    continue;  
                }

                std::string line;
                while (std::getline(daily_file, line)) {
                    if (line.rfind("weight:", 0) == 0) {  
                        std::string weight_value = line.substr(7);  
                        std::string human_readable_date = convert_to_date(directory_name);  
                        std::string daily_weight = human_readable_date + ": " + weight_value;
                        
                        weight_entries.push_back(std::make_pair(directory_name, daily_weight));
                        break;  
                    }
                }
                daily_file.close();
            }
        }
    } catch (const fs::filesystem_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
    }

    std::sort(weight_entries.begin(), weight_entries.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;  
    });

    std::vector<std::string> sorted_weight_entries;
    const int date_width = 20;
    const int weight_width = 10;
    for (const auto& entry : weight_entries) {
        std::string::size_type colon_pos = entry.second.find(':');
        if (colon_pos != std::string::npos) {
            std::string date = entry.second.substr(0, colon_pos);
            std::string weight = entry.second.substr(colon_pos + 1);
            std::ostringstream formatted_entry;
            formatted_entry << std::setw(date_width) << std::left << date
                            << ": " << std::setw(weight_width) << std::right << std::fixed << std::setprecision(1) << weight;
            sorted_weight_entries.push_back(formatted_entry.str());
        }
    }

    return sorted_weight_entries;
}

