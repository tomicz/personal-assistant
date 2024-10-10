#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include <iostream>
#include <string>

class UI{
    public:
        void start_program();
        void open_menu_home(std::string &command);
        void open_menu_settings();
        void set_header(std::string header_name);
        void create_folder();
        void create_file();
        void add_category(std::string &category_name);
};

#endif
