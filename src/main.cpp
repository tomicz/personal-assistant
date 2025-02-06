#include <iostream>
#include <chrono>
#include "../include/user_interface.hpp"

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "\n";
    std::cout << "Copyright \u00A9 2024 Tomicz Engineering LLC" << std::endl;
    std::cout << "Visit tomiczengineering.com for more information." << std::endl;
    
    UI ui;
    ui.open_home_menu();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeToExecute = end - start;
    std::cout << "Time to execute: " << timeToExecute.count() << std::endl;

    return 0;
}
