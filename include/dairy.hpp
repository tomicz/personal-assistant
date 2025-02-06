#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "user_interface.hpp"
#include <limits>

struct Food{
    std::string name;
    std::string brand;
    double amount;
    double calories;
    double fat;
    double carbs;
    double protein;
};

class Dairy {
    public:
        std::vector<Food> get_food_entries(const std::string& date, const std::string& meal_name);
        Food get_meal_total(const std::string& date, const std::string& meal_name);
        Food get_total_all_meals(const std::string& date);
        void add_new_food();
        void remove_food();
        void add_new_daily_entry();
        void write_to_db(const std::string& itemData);

    private:
        Food return_total(std::ifstream& file);
        std::string add_meal_entry();
        std::string get_meal_time();
};
