#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
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
            "3. List Plans",
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
        const std::string RED_COLOR = "\033[1;31m";
        const std::string RESET_COLOR = "\033[0m";

        std::filesystem::path plans_path = "../db/fitness";
        if(std::filesystem::exists(plans_path)){
            std::string plan_name;

            int index = 1;
            for(const auto& file: std::filesystem::directory_iterator(plans_path)){
                if(file.path().filename().string().find(".txt") != std::string::npos){    
                    std::string file_name = file.path().filename().string();
                    file_name.erase(file_name.size() - 4, 4);
                    std::cout << index << ". " << file_name << std::endl;
                    index++;
                }
            }

            std::cout << std::endl;
            std::cout << "Select plan to delete: ";
            int plan_index;
            std::cin >> plan_index;

            int current_index = 1;
            for(const auto& file: std::filesystem::directory_iterator(plans_path)){

                std::string file_name = file.path().filename().string();
                file_name.erase(file_name.size() - 4, 4);

                if(current_index == plan_index){

                    std::cout << "Are you sure you want to delete plan " << file_name << "? (y/n): ";
                    char command;
                    std::cin >> command;
                    std::cout << std::endl;

                    if(command == 'y'){
                        std::filesystem::remove(file.path());
                        std::cout << RED_COLOR << "Plan " << file_name << " deleted successfully." << RESET_COLOR << std::endl;
                        list_plans();
                    }
                    else if(command == 'n'){
                        open_plan_maker();
                    }
                    else{
                        std::cout << "Invalid command\n";
                    }
                    break;
                }
                current_index++;
            }
        }
        else{
            std::cout << "No plans found.\n";
        }

        open_plan_maker();
    }

    void FitnessInterface::list_plans(){
        UI ui;
        ui.set_header("All Plans");
        std::filesystem::path fitness_dir = "../db/fitness";

        if(std::filesystem::exists(fitness_dir)){
            int index = 1;
            for(const auto& file: std::filesystem::directory_iterator(fitness_dir)){
                std::string file_name = file.path().filename().string();
                if(file_name.find(".txt") != std::string::npos){    
                    file_name.erase(file_name.size() - 4, 4);
                    std::cout << index << ". " << file_name << std::endl;
                    index++;
                }
            }
            std::cout << std::endl;
        }
        else{
            std::cout << "No plans found.\n";
        }

        open_plan_maker();
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