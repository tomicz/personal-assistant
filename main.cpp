#include <iostream>
#include <string>
#include <time.h>
#include <typeinfo>

void addCalories()
{
    std::string itemName = "";
    float quantity = {100};
    float calories = {0};
    float fat = {0};
    float carbohydrates = {0};
    float protein = {0};
    float caloriesFormula;
    
    caloriesFormula = calories / 100 * quantity;
     
    std::cout << "Enter item name" << std::endl;
    std::cin >> itemName;

    std::cout << "Enter calories per 100g: " << std::endl;
    std::cin >> calories;  

    std::cout << "Enter fat per 100g: " << std::endl;
    std::cin >> fat;

    std::cout << "Enter carbohydrates per 100g: " << std::endl;
    std::cin >> carbohydrates;
    
    std::cout << "Enter protein per 100g: " << std::endl;
    std::cin >> protein;

    std::cout << "You added item " << itemName << std::endl;
    std::cout << "Calories: " << calories << "g" << std::endl;
    std::cout << "Fat: " << fat << "g" << std::endl;
    std::cout << "Carbohudrates: " << carbohydrates << "g" << std::endl;
    std::cout << "Protein: " << protein << "g" << std::endl;
}

void startApplication()
{
    std::string command = "";
    std::cout << "Type command (a)dd to start the applicaiton. Enter (h)elp for help.To quit enter (q)uit." << std::endl;
    std::cin >> command;

    if(command == "a")
    {
        std::cout << "This is a program for adding calories to data base" << std::endl;
        addCalories();
    }
    else if(command == "h")
    { 
       std::cout << "Commands are: " << std::endl;
       std::cout << "(a)dd" << std::endl;
       std::cout << "(h)elp" << std::endl;
       std::cout << "(q)uit" << std::endl;
    }
    else if(command == "q")
    {
       exit(0); 
    }
}

int main()
{
    clock_t start;
    clock_t end;
    double cycle_count;

    start = clock();

    std::cout << "\n";
    std::cout << "Copyright @ Tomicz Engineering LLC" << std::endl;
    std::cout << "Visit our website at tomiczengineering.com for more information." << std::endl;
    std::cout << "\n";

    startApplication();

    end = clock();

    double timeToExecute = double(end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Time to execute: " << timeToExecute << std::endl;

    return 0;
}
