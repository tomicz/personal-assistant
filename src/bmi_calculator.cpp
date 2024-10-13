#include <string>
#include "../include/bmi_calculator.hpp"

double BmiCalculator::get_bmi(const int age, const char gender, const double height, const double weight){
    double height_m = height / 100.0;
    double bmi = weight / (height_m * height_m);
    return bmi; 
}

std::string BmiCalculator::get_classification(const double bmi){

    std::string classification = "Normal";

    if(bmi < 16){
        classification = "Severe Thinness";
    }
    else if(bmi < 17){
        classification = "Moderate Thinness";
    }
    else if(bmi < 18.5){
        classification = "Mild Thinness";
    }
    else if(bmi < 25){
        classification = "Normal";
    }
    else if(bmi < 30){
        classification = "Overweight";
    }
    else if(bmi < 35){
        classification = "Obese Class I";
    }
    else if(bmi < 40){
        classification = "Obese Class II";
    }
    else{
        classification = "Obese Class III";
    }

    return classification;
}
