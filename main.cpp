#include <iostream>

void AddCalories()
{
    std::string itemName = "";
    int calories = 0;
     
    std::cout << "Enter item name" << std::endl;
    std::cin >> itemName;

    std::cout << "Enter calories: " << std::endl;
    std::cin >> calories;  
    std::cout << "You added item " << itemName << " with " << calories << " calories to a database." << std::endl;
}

void StartApplication()
{
    std::string commandsArray[10];
    commandsArray[0] = "/help"; 
    commandsArray[1] = "/add";
    commandsArray[2] = "/remove";  

    std::string command = "";
    std::cout << "Type command </add> to start the applicaiton. Enter /help for help.To quit enter q" << std::endl;
    std::cin >> command;

    for(int i = 0; i < commandsArray.size(); i++)
    {
        if(command == comandsArray[i])
        {
            std::cout << "This is a program for adding calories to data base" << std::endl;
            AddCalories();
        }
        else
        {
            std::string commandHelp = "";
            std::cout << "Type command </add> to start the applicaiton. Enter /help for help." << std::endl;
            std::cin >> commandHelp;
        }
    }
}

int main()
{
    std::cout << "\n";
    std::cout << "Copyright @ Tomicz Engineering LLC" << std::endl;
    std::cout << "Visit our website at tomiczengineering.com for more information." << std::endl;
    std::cout << "\n";

    StartApplication();
   
    return 0;
}
