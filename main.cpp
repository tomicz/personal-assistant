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
    std::cout << "\n";
    std::cout << "Copyright @ Tomicz Engineering LLC" << std::endl;
    std::cout << "Visit our website at tomiczengineering.com for more information." << std::endl;
    std::cout << "\n";

    startApplication();
   
    return 0;
}
