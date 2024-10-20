#pragma once

#include <string>

class Parser{
    public:
        void read_file(const std::string& file_path);
        std::string create_date_stamp();
        std::string remove_symbols(const std::string& input);
        std::string convert_to_date(const std::string& file_name);
};
