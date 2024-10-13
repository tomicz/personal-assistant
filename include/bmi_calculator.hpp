#pragma once

#include <string>

class BmiCalculator{
    public:
        double get_bmi(const int age, const char gender, const double height, const double weight);        
        std::string get_classification(const double bmi);
};
