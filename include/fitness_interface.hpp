#pragma once

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
    };
}
