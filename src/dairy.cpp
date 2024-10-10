#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "dairy.h"
#include "parser.h"

std::vector<Food*> Dairy::get_food_entries(std::string& meal_name) {
    std::vector<Food*> entries;
    std::string date = create_date_stamp();
    std::string file_path = "db/dailies/" + date + "/" + meal_name + ".txt";
    std::string output;
    std::ifstream file(file_path);

    if (!file.is_open()) {
        return entries;
    }

    while (std::getline(file, output)) {
        std::stringstream ss(output); 
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

    file.close();
    return entries; 
}

Food* Dairy::get_meal_total(std::string meal_name){
    std::string date = create_date_stamp();
    std::string file_path = "db/dailies/" + date + "/" + meal_name + ".txt";
    std::ifstream dairy_data(file_path);
    return return_total(dairy_data);
}

Food* Dairy::return_total(std::ifstream& file){
    Food* food = new Food();
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
            food->name = "Total";
            food->brand = "";
            food->amount = total_amount;
            food->calories = total_calories;
            food->fat = total_fat;
            food->carbs = total_carbs;
            food->protein = total_protein;
        }
        file.close();
    }
    return food;
}

Food* Dairy::get_total_all_meals() {
    std::vector<Food*> totals;
    Food* total = new Food();
    Food* breakfast_total = get_meal_total("breakfast");
    Food* lunch_total = get_meal_total("lunch");
    Food* dinner_total = get_meal_total("dinner");
    totals.push_back(breakfast_total);
    totals.push_back(lunch_total);
    totals.push_back(dinner_total);

    double total_amount = 0.0;
    double total_calories = 0.0;
    double total_fat = 0.0;
    double total_carbs = 0.0;
    double total_protein = 0.0;
    
    for(Food* entry: totals){
        total_amount += entry->amount;
        total_calories += entry->calories;
        total_fat += entry->carbs;
        total_carbs += entry->carbs;
        total_protein += entry->protein;
    }

    total->name =  "Total all";
    total->brand = "";
    total->amount = total_amount;
    total->calories = total_calories;
    total->fat = total_fat;
    total->carbs = total_carbs; 
    total->protein = total_protein; 

    return total;
}
