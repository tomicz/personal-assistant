#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "dairy.hpp"
#include "database.hpp"
#include "fitness_interface.hpp"
#include "goals_interface.hpp"

class UI {
    public:
        bool open_home_menu();
        void open_dairy_menu();
        void open_food_database(bool show_as_list = false);
        void open_fitness_menu();
        void open_goals_menu();
        bool read_db();
        void set_header(const std::string& header_name);
        void open_daily_entries_menu();
        void read_daily_entry(const std::string& date);
        void open_health_menu();
        void enter_weight();
        void read_weight();
        bool read_meal_data(const std::string& date, const std::string& meal_name);

    private:
        void read_daily_entry_by_date();
        void enter_height();
        void read_height();
        void read_bmi();
        void read_remaining(double calories);
        void display_menu_options();
        void display_dairy_options();
        void display_fitness_options();
        void display_goals_options();
        void clear_screen();
};
