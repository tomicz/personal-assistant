#include <iostream>
#include <filesystem>
#include <fstream>
#include <limits>
#include <sstream>
#include <thread>
#include <chrono>
#include <queue>
#include "../../include/fitness_interface.hpp"
#include "../../include/user_interface.hpp"
#include "../../include/exercise.hpp"

namespace fitness{
    const std::string CYAN = "\033[1;36m";
    const std::string RESET = "\033[0m";
    const std::string CLEAR = "\033[2J\033[H"; 

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
                open_fitness_runner();
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
            "4. List Exercises",
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
            case '4':
                list_exercises();
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
        std::string plan_name;
        std::cout << "Enter plan name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::getline(std::cin, plan_name);

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
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    int reps, sets = 0;
                    float interval = 0;
                    float set_pause = 0;
                    float exercies_pause = 0;

                    std::cout << "Enter exercise name: ";
                    std::getline(std::cin, exercise_name);
                    std::cout << "Enter exercise description: ";
                    std::getline(std::cin, exercise_description);
                    std::cout << "Enter exercise reps: ";
                    std::cin >> reps;
                    std::cout << "Enter exercise sets: ";
                    std::cin >> sets;
                    std::cout << "Enter exercise interval: ";
                    std::cin >> interval;
                    std::cout << "Enter pause between sets: ";
                    std::cin >> set_pause;
                    std::cout << "Enter pause ater exercies: ";
                    std::cin >> exercies_pause;

                    file << exercise_name + ", " + exercise_description + ", " + std::to_string(reps) + ", " + std::to_string(sets) + ", " + std::to_string(interval) + ", " + std::to_string(set_pause) + ", " + std::to_string(exercies_pause) + "\n";

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

    void FitnessInterface::list_exercises(){
        std::filesystem::path fitness_dir = "../db/fitness";
        if(std::filesystem::exists(fitness_dir)){

            int index = 1;
            for(const auto& file: std::filesystem::directory_iterator(fitness_dir)){
                if(file.path().filename().string().find(".txt") != std::string::npos){    
                    std::string file_name = file.path().filename().string();
                    file_name.erase(file_name.size() - 4, 4);
                    std::cout << index << ". " << file_name << std::endl;
                    index++;
                }
            }
            std::cout << std::endl;

            std::cout << "Select plan: ";
            int plan_index;
            std::cin >> plan_index;
            std::cout << std::endl;

            const int WIDTH = 108;
            std::cout << CYAN << std::string(WIDTH, '-') << RESET << std::endl;
            std::cout << std::setw(3) << "" 
                      << std::left 
                      << std::setw(21) << "Name" 
                      << std::setw(25) << "Description" 
                      << std::right
                      << std::setw(9) << "Sets" 
                      << std::setw(10) << "Reps" 
                      << std::setw(10) << "Interval" 
                      << std::setw(15) << "Set pause"
                      << std::setw(15) << "Pause"
                      << std::endl;
            std::cout << CYAN << std::string(WIDTH, '-') << RESET << std::endl;
            
            size_t file_iterator = 0;
            int exercise_index = 1;

            for(const auto& file: std::filesystem::directory_iterator(fitness_dir)){
                if(file.path().filename().string().find(".txt") != std::string::npos && file_iterator == plan_index){    
                    std::string file_name = file.path().filename().string();
                    file_name.erase(file_name.size() - 4, 4);
                    std::ifstream file((fitness_dir / (file_name + ".txt")).string());
                    std::string line;

                    std::string name, description;
                    int sets, reps = 0;
                    float interval = 0;
                    float set_pause = 0; 
                    float exercise_pause = 0;

                    while(std::getline(file, line)){
                        std::stringstream ss(line);
                        std::getline(ss, name, ',');
                        std::getline(ss, description, ',');
                        ss >> sets;
                        ss.ignore(1);
                        ss >> reps;
                        ss.ignore(1);
                        ss >> interval;
                        ss.ignore(1);
                        ss >> set_pause;
                        ss.ignore(1);
                        ss >> exercise_pause;

                        if (name.length() > 15) {
                            name = name.substr(0, 12) + "...";
                        }
                        if (description.length() > 20) {
                            description = description.substr(0, 17) + "...";
                        }

                        std::cout << "\033[36m" << exercise_index << "\033[0m. " 
                                  << std::left 
                                  << std::setw(20) << name 
                                  << std::setw(25) << description 
                                  << std::right
                                  << std::setw(10) << sets 
                                  << std::setw(10) << reps 
                                  << std::setw(10) << interval 
                                  << std::setw(15) << set_pause 
                                  << std::setw(15) << exercise_pause 
                                  << std::endl;

                        exercise_index++;
                    }
                    std::cout << CYAN << std::string(WIDTH, '-') << RESET << std::endl;
                    break;
                }
                file_iterator++;
            }

            std::cout << std::endl;
        }
        else{
            std::cout << "No plans found.\n";
        }

        open_plan_maker();
    }

    void FitnessInterface::open_fitness_runner(){
        std::queue<Exercise> exercises;
        std::filesystem::path fitness_dir = "../db/fitness";
        std::string workout_name = "na";

        print_all_plans(fitness_dir);
        exercises =  parse_all_exercises(workout_name, fitness_dir);

        std::cout << std::endl;
        std::cout << CLEAR;
        UI ui;
        ui.set_header("Starting Workout...");
        std::cout << "Workout name: " << workout_name << std::endl;
        
        int wait_time = 5; 

        wait_for_seconds(wait_time);

        while(exercises.size() > 0){
            std::cout << std::endl;

            for(int i = 0; i <= wait_time; i++){
                std::cout << CLEAR;
                std::cout << "Exercise: " << exercises.front().name << "\n";
                std::cout << "\r" << std::setw(2) << "Starting in: "<< wait_time - i << std::flush;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }


            std::cout << std::endl;
            for(int i = 0; i < exercises.front().sets - 1; i++) {
                for (int j = exercises.front().interval; j >= 0; --j) {
                    std::cout << CLEAR; 
                    std::cout << "Exercise: " << exercises.front().name << "\n\n";
                    std::cout << "Set: " << i + 1 << " / " << exercises.front().sets << "\n";
                    std::cout << "Time remaining: " << j << " seconds\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }

                float pause = exercises.front().set_pause;

                for(int j = pause; j >= 0; --j){
                    std::cout << CLEAR;
                    std::cout << "Next set starts in: " << j << "\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }

            std::cout << CLEAR;

            float next_exercise_time = exercises.front().exercise_pause;

            if(exercises.size() == 1){
                exercises.pop();
                break;
            }

            for (int i = next_exercise_time; i >= 0; --i) {
                std::cout << "\r" << "Next exercise in: " << i << " seconds" << std::flush;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            exercises.pop();
            std::cout << std::endl;
        }

        std::cout << "Workout finished!" << std::endl;
        start();
    }

    void FitnessInterface::print_all_plans(std::filesystem::path at_path){
        if(std::filesystem::exists(at_path)){

            int index = 1;

            for(const auto& file: std::filesystem::directory_iterator(at_path)){
                if(file.path().filename().string().find(".txt") != std::string::npos){

                    std::string file_name = file.path().filename().string();
                    file_name.erase(file_name.size() - 4, 4);
                    std::cout << index << ". " << file_name << std::endl;
                    index++;
                }
            }
        }
    }

    std::queue<Exercise> FitnessInterface::parse_all_exercises(std::string& workout_name, std::filesystem::path at_path){

        std::queue<Exercise> exercises;
        int index = 1;
        std::cout << "Select plan: ";
        int plan_index;
        std::cin >> plan_index;

        for(const auto& file: std::filesystem::directory_iterator(at_path)){
            if(file.path().filename().string().find(".txt") != std::string::npos){

                std::string file_name = file.path().filename().string();
                file_name.erase(file_name.size() - 4, 4);

                if(index == plan_index){

                    std::ifstream file((at_path / (file_name + ".txt")).string());
                    std::string line;
                    workout_name = file_name;

                    while(std::getline(file, line)){
                        std::stringstream ss(line);
                        std::string name, description;
                        int sets, reps = 0;
                        float interval = 0;
                        float set_pause = 0;
                        float exercise_pause = 0;

                        std::getline(ss, name, ',');
                        std::getline(ss, description, ',');
                        ss >> sets;
                        ss.ignore(1);
                        ss >> reps;
                        ss.ignore(1);
                        ss >> interval;
                        ss.ignore(1);
                        ss >> set_pause;
                        ss.ignore(1);
                        ss >> exercise_pause;

                        Exercise exercise(name, description, sets, reps, interval, set_pause, exercise_pause);
                        exercises.push(exercise);
                    }
                }
                index++;
            }
        }   
        return exercises;
    }

    void FitnessInterface::wait_for_seconds(int time){
        for(int i = 0; i <= time; i++){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
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
