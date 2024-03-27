#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

void write_to_create_db(std::string itemData)
{
    std::ofstream database ("db.txt", std::ios::app);
    database << "\n" << itemData;    
    database.close();
    std::cout << "Created a database successfully" << std::endl;
}

void add_calories()
{
    std::string itemName = "";
    std::string brand_name = "";
    float quantity = {0};
    float calories = {0};
    float fat = {0};
    float carbohydrates = {0};
    float protein = {0};
    std::string itemData;

    std::cout << "Enter item name" << std::endl;
    std::cin >> itemName;
    
    std::cout << "Enter brand name: "  << std::endl;
    std::cin >> brand_name;

    std::cout << "Enter quantity " << std::endl;
    std::cin >> quantity;

    std::cout << "Enter calories per 100g: " << std::endl;
    std::cin >> calories;  

    std::cout << "Enter fat per 100g: " << std::endl;
    std::cin >> fat;

    std::cout << "Enter carbohydrates per 100g: " << std::endl;
    std::cin >> carbohydrates;
    
    std::cout << "Enter protein per 100g: " << std::endl;
    std::cin >> protein;

    std::cout << "You added item " << itemName << std::endl;
    
    std::cout << "Brand: " << brand_name << std::endl;
    std::cout << "Quantity: " << quantity << " units" << std::endl;
    std::cout << "Calories: " << calories << "g" << std::endl;
    std::cout << "Fat: " << fat << "g" << std::endl;
    std::cout << "Carbohydrates: " << carbohydrates << "g" << std::endl;
    std::cout << "Protein: " << protein << "g" << std::endl;
    
    itemData = itemName + ", "
        + brand_name 
        +  ", "+ std::to_string(quantity) 
        + ", " + std::to_string(calories) 
        + ", " + std::to_string(fat) 
        + ", " + std::to_string(carbohydrates) 
        + ", " + std::to_string(protein);

    write_to_create_db(itemData);
}

void startApplication()
{
    std::string command = "";
    std::cout << "Type command (A)dd to start the applicaiton. Enter (H)elp for help.To quit enter (Q)uit." << std::endl;
    std::cout << "To add a new day entry type (N)ew. << std::endl" << std::endl;
    std::cin >> command;

    if(command == "a" || command == "A")
    {
        std::cout << "This is a program for adding calories to data base" << std::endl;
        add_calories();
    }
    else if(command == "h" || command == "H")
    { 
       std::cout << "Commands are: " << std::endl;
       std::cout << "(A)dd" << std::endl;
       std::cout << "(N)ew" << std::endl;
       std::cout << "(H)elp" << std::endl;
       std::cout << "(Q)uit" << std::endl;
    }
    else if(command == "n" || command == "N")
    {
        std::cout << "Trying to creaete a new daily entry" << std::endl;
    }
    else if(command == "q" || command == "Q")
    {
        std::cout << "Command does not exit, please try agian." << std::endl;
       exit(0); 
    }
}

int main()
{
    clock_t start;
    clock_t end;

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
