#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "dairy.h"
#include "parser.h"

Food* Dairy::get_breakfast_total(){
    std::string date = create_date_stamp();
    std::string file_path = "db/dailies/" + date + "/" + "breakfast.txt";
    std::ifstream dairy_data(file_path);
    return return_total(dairy_data);
}

Food* Dairy::get_lunch_total(){
    std::string date = create_date_stamp();
    std::string file_path = "db/dailies/" + date + "/" + "lunch.txt";
    std::ifstream dairy_data(file_path);
    return return_total(dairy_data);
}

Food* Dairy::get_dinner_total(){
    std::string date = create_date_stamp();
    std::string file_path = "db/dailies" + date + "/" + "dinner.txt";
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

        total = "amount(g):" + std::to_string(total_amount ) + ", calories: " + std::to_string(total_calories ) + ", fat: " + std::to_string(total_fat ) + ", carbs: " + std::to_string(total_carbs ) + ", protein: " + std::to_string(total_protein);
    }
    return food;
}

Food* Dairy::get_total_all_meals() {
    Food* breakfast_total = get_breakfast_total();
    Food* lunch_total = get_lunch_total();
    Food* dinner_total = get_dinner_total();

    double total_amount = 0.0;
    double total_calories = 0.0;
    double total_fat = 0.0;
    double total_carbs = 0.0;
    double total_protein = 0.0;

    auto accumulate_totals = [&](const std::string& meal_total) {
        std::stringstream ss(meal_total);
        std::string token;
        
        while (std::getline(ss, token, ',')) {
            std::string key;
            double value;
            std::stringstream token_stream(token);
            std::getline(token_stream, key, ':');
            token_stream >> value;
            
            if (key == "amount(g)") total_amount += value;
            else if (key == " calories") total_calories += value;
            else if (key == " fat") total_fat += value;
            else if (key == " carbs") total_carbs += value;
            else if (key == " protein") total_protein += value;
        }
    };

    //accumulate_totals(breakfast_total);
    //accumulate_totals(lunch_total);
    //accumulate_totals(dinner_total);

    std::string total = "Total Amount(g): " + std::to_string(total_amount) +
                        ", Total Calories: " + std::to_string(total_calories) +
                        ", Total Fat: " + std::to_string(total_fat) +
                        ", Total Carbohydrates: " + std::to_string(total_carbs) +
                        ", Total Protein: " + std::to_string(total_protein);

    return nullptr;
}
