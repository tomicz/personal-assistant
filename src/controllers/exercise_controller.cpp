#include "../../include/exercise_controller.hpp"
#include "../../include/exercise.hpp"
#include <filesystem>
#include <fstream>

namespace fitness{
    ExerciseController::ExerciseController()
    {

    }

    ExerciseController::~ExerciseController()
    {

    }

    Exercise* ExerciseController::create_exercise(const std::string & name, const std::string & description, int reps, int sets, float interval)
    {
        auto exercise = std::make_unique<Exercise>(name, description, reps, sets, interval);
    }

    void ExerciseController::delete_exercise(const std::string& name)
    {
        // TODO: Implement this method
    }

    void ExerciseController::update_exercise(const Exercise& exercise)
    {
        // TODO: Implement this method
    }

    void ExerciseController::list_exercises() const
    {
        // TODO: Implement this method
    }
}