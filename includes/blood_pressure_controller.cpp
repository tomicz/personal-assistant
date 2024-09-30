#include <string>
#include "database.h"

void enter_pulse(int pulse)
{
	std::string file_path = "db/dailies/" + create_date_stamp() + "/";
	std::string file_path_entry = "db/dailies/" + create_date_stamp() + "/daily_entry.txt";
	std::string pulse_data = "pulse: " + std::to_string(pulse);

	create_db_file(file_path, "daily_entry");
	write_to_table(file_path_entry, pulse_data);
}

void enter_sys_and_dia(int sys, int dia)
{
	std::string file_path = "db/dailies/" + create_date_stamp() + "/";
	std::string file_path_entry = "db/" + create_date_stamp() + "/daily_entry.txt";
	
	std::string sys_data = "sys: " + std::to_string(sys);
	std::string dia_data = "dia: " + std::to_string(dia);

	create_db_file(file_path, "daily_entry");
	write_to_table(file_path_entry, sys_data);
	write_to_table(file_path_entry, dia_data);
}

