#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "dairy.h"
#include "parser.h"

std::string Dairy::get_breakfast_total(){
    std::string date = create_date_stamp();
    std::string file_path = "db/" + date + "/" + "breakfast.txt";
    std::ifstream dairy_data(file_path);
    return return_total(dairy_data);
}

std::string Dairy::get_lunch_total(){
    std::string date = create_date_stamp();
    std::string file_path = "db/" + date + "/" + "lunch.txt";
    std::ifstream dairy_data(file_path);
    return return_total(dairy_data);
}

std::string Dairy::get_dinner_total(){
    std::string date = create_date_stamp();
    std::string file_path = "db/" + date + "/" + "dinner.txt";
    std::ifstream dairy_data(file_path);
    return return_total(dairy_data);
}

std::string Dairy::return_total(std::ifstream& file){
    std::string total;
    double total_amount = 0.0;
    double total_calories = 0.0;
    double total_fat = 0.0;
    double total_carbs = 0.0;
    double total_protein = 0.0;

    if(file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            std::stringstream ss(line);
            std::string article_name, brand_name;
            double amount, calories, fat, carbs, protein;
            
            std::getline(ss, article_name, ',');
            std::getline(ss, brand_name, ',');
            ss >> amount;
            ss.ignore(1);
            ss >> calories;
            ss.ignore(1);
            ss >> fat;
            ss.ignore(1);
            ss >> carbs;
            ss.ignore(1);
            ss >> protein;

            total_amount += amount;
            total_calories += calories;
            total_fat += fat;
            total_carbs += carbs;
            total_protein += protein;
        }

        file.close();

        total = "amount(g):" + std::to_string(total_amount ) + ", calories: " + std::to_string(total_calories ) + ", fat: " + std::to_string(total_fat ) + ", carbs: " + std::to_string(total_carbs ) + ", protein: " + std::to_string(total_protein);
    }
    return total;
}
