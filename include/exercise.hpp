#pragma once

#include <string>

namespace fitness{
    struct Exercise{
        const std::string name;
        const std::string description;
        const int reps;
        const int sets;
        const float interval;

        Exercise(std::string name, std::string description, int reps, int sets, float interval)
            : name(std::move(name)), 
            description(std::move(description)), 
            reps(reps), 
            sets(sets), 
            interval(interval) 
        {}
    };
}