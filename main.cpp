#include <iostream>
#include <string>

void addCalories()
{
    std::string itemName = "";
    int calories = {0};
     
    std::cout << "Enter item name" << std::endl;
    std::cin >> itemName;

    std::cout << "Enter calories: " << std::endl;
    std::cin >> calories;  
    std::cout << "You added item " << itemName << " with " << calories << " calories to a database." << std::endl;
}

void startApplication()
{
    std::string commandsArray[10];
    commandsArray[0] = "a"; 
    commandsArray[1] = "h";
    commandsArray[2] = "q";  

    std::string command = "";
    std::cout << "Type command (a)add to start the applicaiton. Enter (h)elp for help.To quit enter (q)uit." << std::endl;
    std::cin >> command;

    for(int i = 0; i < sizeof(commandsArray); i++)
    {
        if(command == commandsArray[i])
        {
            std::cout << "This is a program for adding calories to data base" << std::endl;
            addCalories();
            break;
        }
    }
}

int main()
{
    std::cout << "\n";
    std::cout << "Copyright @ Tomicz Engineering LLC" << std::endl;
    std::cout << "Visit our website at tomiczengineering.com for more information." << std::endl;
    std::cout << "\n";

    startApplication();
   
    return 0;
}
