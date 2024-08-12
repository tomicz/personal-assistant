#include <iostream>
#include <string>
#include <filesystem>

void write_to_table(std::string &file_path, std::string &data);
void write_to_file(std::string file_path, std::string file_name, std::string data);
void create_db_file(std::string file_path, std::string file_name);
std::string remove_symbols(const std::string& input);
void create_directory(const std::string& file_path);
std::string create_date_stamp();
int get_database_size();
void remove_element_at_index();
std::string modify_data_at_index(int index, std::string &data);
void enter_new_data_at_index(int index, double amount, std::string &data);
void read_db(bool = false);
std::string get_element_from_db(int = 0);
void add_weight(std::string &file_path, const double &weight);
void write_to_db(const std::string &item_data);
