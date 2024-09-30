#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include "weight.h"
#include "parser.h"

namespace fs = std::filesystem;

std::vector<std::string> Weight::get_weight_all(){
    std::string file_path = "db/dailies/";
    std::vector<std::string> directories;
    std::vector<std::string> weight_entries;
    try{
        for(const auto& entry : fs::directory_iterator(file_path)){
            if(fs::is_directory(entry.status())){
                std::string directory_name = entry.path().filename().string();
                directories.push_back(directory_name);
            }
        }
    }catch(const fs::filesystem_error& error){
        std::cerr << "Error: " << error.what() << std::endl;
    }

    for(std::string d_name : directories){
        std::string full_directory_path = file_path + d_name + "/daily_entry.txt";
        std::ifstream daily_file(full_directory_path);
        
        if (!daily_file.is_open()) {
            continue;  
        }

        std::string line;
        while (std::getline(daily_file, line)) {
            if (line.rfind("weight:", 0) == 0) {  
                std::string weight_value = line.substr(7);  
                std::string daily_weight = convert_to_date(d_name) + ": " + weight_value;
                weight_entries.push_back(daily_weight);
                break;  
            }
        }
        daily_file.close();  
    }
    return weight_entries;
}
