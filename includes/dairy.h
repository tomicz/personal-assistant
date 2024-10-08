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
        Food* get_breakfast_total();
        Food* get_lunch_total();
        Food* get_dinner_total();
        Food* get_total_all_meals();

    private:
        Food* return_total(std::ifstream& file);
};

#endif
