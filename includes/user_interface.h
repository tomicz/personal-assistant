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
        void open_menu_settings();
        void set_header(std::string header_name);
        void create_folder();
        void create_file();
        void add_category(std::string &category_name);
        void open_dairy_menu();
    
};

#endif
