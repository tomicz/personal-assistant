#include <iostream>
#include <filesystem>
#include <fstream>
#include <sys/syslimits.h>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <filesystem>
#include "../include/weight.hpp"

std::vector<std::pair<std::string, double>> Weight::get_everyday_weight() {
    std::filesystem::path dailies_path = "../db/dailies/";
    std::vector<std::pair<std::string, double>> directory_names;

    if(std::filesystem::is_directory(dailies_path)){
        for(const auto& entry: std::filesystem::directory_iterator(dailies_path)){

            if(entry.is_directory()){

                std::string directory_name = entry.path().filename().string();
                std::filesystem::path directory_with_weight_entry = std::filesystem::path(dailies_path) / directory_name / "daily_entry.txt";

                if(std::filesystem::exists(directory_with_weight_entry)){
                    
                    double weight;
                    std::string weight_label;
                    std::ifstream file(directory_with_weight_entry);
                    std::string line;
                    std::stringstream ss(line);

                    while (std::getline(file, line)) {
                        if (line.find("weight:") != std::string::npos) {

                            std::stringstream ss(line);
                            ss >> weight_label;
                            ss >> weight; 
                            directory_name.insert(4, ".");
                            directory_name.insert(7, ".");
                            directory_names.emplace_back(std::make_pair(directory_name, weight));
                        
                            break;
                        }
                    }
                }
            }
        }

        std::sort(directory_names.begin(), directory_names.end());
    }

    return directory_names;    
}

