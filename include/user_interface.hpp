#pragma once

#include <iostream>
#include <string>
#include <stack>

class UI{
    public:
        void open_home_menu();
        void set_header(const std::string& header_name);
        void open_dairy_menu();
        void open_food_database(bool show_as_list);
        void open_daily_entries_menu();
        void read_daily_entry(const std::string& date);
        void open_health_menu();
        void enter_weight();
        void read_weight();

    private:
        void read_meal_data(const std::string& date, const std::string& meal_name);
        void read_daily_entry_by_date();
        void enter_height();
        void read_height();
        void read_bmi();
        void read_remaining(double calories);
};
