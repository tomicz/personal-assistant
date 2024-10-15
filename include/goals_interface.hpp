#pragma once

#include <string>
#include "user_interface.hpp"

class GoalsInterface{
    public:
        void start();
    
    private:
        void print_goal_types();
        void set_header(const std::string& header_name);
        void add_goal();
        void view_goals();
        void add_weight_goal();
        void add_calorie_goal();
};

