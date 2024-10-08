#ifndef _DIARY_H_
#define _DIARY_H_

#include <string>
#include <fstream>

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
        std::vector<Food*> get_food_entries(std::string& meal_name);
        Food* get_meal_total(std::string meal_name);
        Food* get_total_all_meals();

    private:
        Food* return_total(std::ifstream& file);
};

#endif
