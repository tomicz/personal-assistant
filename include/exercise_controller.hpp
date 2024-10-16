#pragma once

#include "exercise.hpp"
#include <filesystem>

namespace fitness{
    class ExerciseController{
        public:
            ExerciseController();
            ~ExerciseController();

            Exercise* create_exercise(const std::string & name, const std::string & description, int reps, int sets, float interval);
            void delete_exercise(const std::string& name);
            void update_exercise(const Exercise& exercise);
            void list_exercises() const;
    };
}