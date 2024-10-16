#include <iostream>
#include <filesystem>
#include <fstream>
#include "../../include/fitness_interface.hpp"
#include "../../include/user_interface.hpp"
#include "../../include/exercise_controller.hpp"

namespace fitness{
    void FitnessInterface::start(){
        UI ui;

        ui.set_header("Fitness Menu");

        std::vector<std::string> options = {
            "1. Fitness Runner",
            "2. Plan Maker",
            "(B)ack"
        };

        for(const auto& option: options){
            std::cout << option << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Select option: ";

        char command;
        std::cin >> command;
        std::cout << std::endl;

        switch(command){
            case '1':
                open_plan_maker();
                break;
            case '2':
                open_plan_maker();
                break;
            case 'b':
                ui.open_home_menu();
                break;
            case 'B':
                ui.open_home_menu();
                break;
            default:
                std::cout << "Invalid command\n";
                break;
        }
    }

    void FitnessInterface::open_plan_maker(){
        std::vector<std::string> options = {
            "1. Create Plan",
            "2. Delete Plan",
            "3. Update Plan",
            "4. List Plans",
            "(B)ack"
        };  

        for(const auto& option: options){
            std::cout << option << "\n";
        }

        std::cout << std::endl;

        std::cout << "Select option: ";
        char command;
        std::cin >> command;

        switch(command){
            case '1':
                create_plan();
                break;
            case '2':
                delete_plan();
                break;
            case '3':
                update_plan();
                break;
            case '4':
                list_plans();
                break;
            case 'b':
                start();
                break;
            case 'B':   
                start();
                break;
            default:
                std::cout << "Invalid command\n";
                break;
        }
    }

    void FitnessInterface::create_plan(){
        ExerciseController exercise_controller;

        std::string plan_name;
        std::cout << "Enter plan name: ";
        std::cin >> plan_name;

        std::string path = create_fitness_folder() + "/" + plan_name + ".txt";

        if(std::filesystem::exists(path)){
            std::cout << "Plan already exists\n";
            return;
        }

        std::ofstream file(path);

        if (std::filesystem::exists(path)) {
            std::cout << "Plan '" << plan_name << "' created successfully.\n";

            while(true){
                std::cout << std::endl;
                std::cout << "Create new exercise? (y/n): ";
                char command;
                std::cin >> command;

                if(command == 'y'){
                    std::string exercise_name, exercise_description;
                    int reps, sets;
                    float interval;

                    std::cout << "Enter exercise name: ";
                    std::cin >> exercise_name;
                    std::cout << "Enter exercise description: ";
                    std::cin >> exercise_description;
                    std::cout << "Enter exercise reps: ";
                    std::cin >> reps;
                    std::cout << "Enter exercise sets: ";
                    std::cin >> sets;
                    std::cout << "Enter exercise interval: ";
                    std::cin >> interval;

                    file << exercise_name + ", " + exercise_description + ", " + std::to_string(reps) + ", " + std::to_string(sets) + ", " + std::to_string(interval) + "\n";
                    std::cout << "Exercise created successfully.\n";
                }
                else if(command == 'n'){
                    break;
                }
                else{
                    std::cout << "Invalid command\n";
                }
            }
            file.close();
        } else {
            std::cerr << "Error: Unable to create plan file.\n";
        }

        open_plan_maker();
    }

    void FitnessInterface::delete_plan(){
        std::cout << "Delete plan\n";
    }

    void FitnessInterface::update_plan(){
        std::cout << "Update plan\n";
    }

    void FitnessInterface::list_plans(){
        std::cout << "List plans\n";
    }

    std::string FitnessInterface::create_fitness_folder(){
        std::filesystem::path fitness_dir = "../db/fitness";
        if (!std::filesystem::exists(fitness_dir)) {
            if (std::filesystem::create_directory(fitness_dir)) {
                std::cout << "Created 'fitness' directory.\n";
            } 
        }
        return fitness_dir;
    }
}