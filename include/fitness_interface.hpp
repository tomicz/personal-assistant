#pragma once

#include <string>
#include <filesystem>
#include <queue>
#include "exercise.hpp"

namespace fitness {
    class FitnessInterface {
    public:
        FitnessInterface() = default;
        ~FitnessInterface() = default;
        void start();

    private:
        void open_plan_maker();
        void open_fitness_runner();
        void create_plan();
        void delete_plan();
        void list_plans();
        std::string create_fitness_folder();
        void list_exercises();
        void print_all_plans(std::filesystem::path at_path);
        std::queue<Exercise> parse_all_exercises(std::string& workout_name, std::filesystem::path at_path);
        void wait_for_seconds(int time);
    };
}
