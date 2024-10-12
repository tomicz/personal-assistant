#include <iostream>
#include <time.h>
#include <ctime>
#include "../include/user_interface.h"


int main()
{
    UI ui;
    clock_t start;
    clock_t end;

    start = clock();

    std::cout << "\n";
    std::cout << "Copyright \u00A9 2024 Tomicz Engineering LLC" << std::endl;
    std::cout << "Visit tomiczengineering.com for more information." << std::endl;
    
    ui.start_program();

    end = clock();

    double timeToExecute = double(end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Time to execute: " << timeToExecute << std::endl;

    return 0;
}
