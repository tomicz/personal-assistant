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
        std::string get_breakfast_total();
        std::string get_lunch_total();
        std::string get_dinner_total();
        std::string get_total_all_meals();

    private:
        std::string return_total(std::ifstream& file);
};

#endif
