#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include <iostream>
#include <string>
#include <stack>

class UI{
    public:
        std::string root = "root/";
        std::string dairy = root + "dairy/";
        std::string current_path;
        
        void start_program();
        void open_menu_home();
        void set_header(std::string header_name);
        void open_dairy_menu();
        void open_food_database(bool show_as_list);
        void open_daily_entries_menu();
        void read_daily_entry();

    private:
        void read_meal_data(std::string meal_name);
};

#endif
