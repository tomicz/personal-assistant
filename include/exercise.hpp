#pragma once

#include <string>

namespace fitness{
    struct Exercise{
        const std::string name;
        const std::string description;
        const int reps;
        const int sets;
        const float interval;
        const float set_pause;
        const float exercise_pause;

        Exercise(std::string name, std::string description, int reps, int sets, float interval, float set_pause, float exercise_pause)
            : name(std::move(name)), 
            description(std::move(description)), 
            reps(reps), 
            sets(sets), 
            interval(interval),
            set_pause(set_pause),
            exercise_pause(exercise_pause)
        {}
    };
}
