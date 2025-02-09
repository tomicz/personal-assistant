#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../include/dairy.hpp"
#include "../include/parser.hpp"
#include "../include/database.hpp"

// Add these color constants
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

std::vector<Food> Dairy::get_food_entries(const std::string& date, const std::string& meal_name) {
    std::vector<Food> entries;
    std::string file_path = "db/dailies/" + date + "/" + meal_name + ".txt";
    std::string output;
    std::ifstream file(file_path);

    if (!file.is_open()) {
        return entries;
    }

    while (std::getline(file, output)) {
        std::stringstream ss(output); 
        Food entry;
        std::getline(ss, entry.name, ','); 
        std::getline(ss, entry.brand, ',');
        ss >> entry.amount;
        ss.ignore(1);
        ss >> entry.calories;
        ss.ignore(1);
        ss >> entry.fat;
        ss.ignore(1); 
        ss >> entry.carbs; 
        ss.ignore(1);
        ss >> entry.protein; 
        entries.push_back(entry);
    }

    file.close();
    return entries; 
}

Food Dairy::get_meal_total(const std::string& date, const std::string& meal_name){
    std::string file_path = "db/dailies/" + date + "/" + meal_name + ".txt";
    std::ifstream dairy_data(file_path);

    Food food = return_total(dairy_data);
    return food;
}

Food Dairy::return_total(std::ifstream& file){
    Food food;
    std::string total;
    double total_amount = 0.0;
    double total_calories = 0.0;
    double total_fat = 0.0;
    double total_carbs = 0.0;
    double total_protein = 0.0;

    std::string line;
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string article_name, brand_name;
        double amount, calories, fat, carbs, protein;
        
        std::getline(ss, article_name, ',');
        std::getline(ss, brand_name, ',');
        ss >> amount;
        ss.ignore(1);
        ss >> calories;
        ss.ignore(1);
        ss >> fat;
        ss.ignore(1);
        ss >> carbs;
        ss.ignore(1);
        ss >> protein;

        total_amount += amount;
        total_calories += calories;
        total_fat += fat;
        total_carbs += carbs;
        total_protein += protein;
        food.name = "Total";
        food.brand = "";
        food.amount = total_amount;
        food.calories = total_calories;
        food.fat = total_fat;
        food.carbs = total_carbs;
        food.protein = total_protein;
    }
    return food;
}

Food Dairy::get_total_all_meals(const std::string& date) {
    std::vector<Food> totals;
    Food total;
    Food breakfast_total = get_meal_total(date, "Breakfast");
    Food lunch_total = get_meal_total(date, "Lunch");
    Food dinner_total = get_meal_total(date, "Dinner");
    totals.push_back(breakfast_total);
    totals.push_back(lunch_total);
    totals.push_back(dinner_total);

    double total_amount = 0.0;
    double total_calories = 0.0;
    double total_fat = 0.0;
    double total_carbs = 0.0;
    double total_protein = 0.0;
    
    for(const Food& entry: totals){
        total_amount += entry.amount;
        total_calories += entry.calories;
        total_fat += entry.fat;
        total_carbs += entry.carbs;
        total_protein += entry.protein;
    }

    total.name = "Total all";
    total.brand = "";
    total.amount = total_amount;
    total.calories = total_calories;
    total.fat = total_fat;
    total.carbs = total_carbs;
    total.protein = total_protein;

    return total;
}

void Dairy::add_new_food()
{
    std::string item_name;
    std::string brand_name;

    double quantity = {0};
    double calories = {0};
    double fat = {0};
    double carbohydrates = {0};
    double protein = {0};

    std::string itemData;
    std::cin.ignore(1000, '\n');
    
    std::cout << "Enter item name: ";
    std::getline(std::cin, item_name);

    std::cout << "Enter brand name: ";
    std::getline(std::cin, brand_name);
    
    std::cout << "Enter quantity: ";
    std::cin >> quantity;

    std::cout << "Enter calories per 100g: ";
    std::cin >> calories;  

    std::cout << "Enter fat per 100g: ";
    std::cin >> fat;

    std::cout << "Enter carbohydrates per 100g: ";
    std::cin >> carbohydrates;
    
    std::cout << "Enter protein per 100g: ";
    std::cin >> protein;

    std::cout << "You added item " << item_name << std::endl;
    
    std::cout << "Brand: " << brand_name << std::endl;
    std::cout << "Quantity: " << quantity << " units" << std::endl;
    std::cout << "Calories: " << calories << "g" << std::endl;
    std::cout << "Fat: " << fat << "g" << std::endl;
    std::cout << "Carbohydrates: " << carbohydrates << "g" << std::endl;
    std::cout << "Protein: " << protein << "g" << std::endl;

    itemData = item_name + ", "
        + brand_name 
        + ", " + std::to_string(quantity) 
        + ", " + std::to_string(calories) 
        + ", " + std::to_string(fat) 
        + ", " + std::to_string(carbohydrates) 
        + ", " + std::to_string(protein);

    std::ofstream database("db/db.txt", std::ios::app);
    
    if (!database.is_open()) {
        std::cerr << "Error: Cannot open database file for writing." << std::endl;
        return;
    }

    // Add a newline before writing if the file is not empty
    std::ifstream check_file("db/db.txt");
    if (check_file.peek() != std::ifstream::traits_type::eof()) {
        database << std::endl;
    }
    check_file.close();

    database << itemData;
    database.close();

    std::cout << "Successfully added to database!" << std::endl;
}

void Dairy::remove_food(){
    std::ifstream database("../db/db.txt");
    std::ofstream temp_database("temp_database.txt");

    if (!database || !temp_database)
    {
        std::cout << "Error: Cannot open database" << std::endl;
        return;
    }

    std::cout << "Current entries in the database:\n";
    read_db();

    database.clear();
    database.seekg(0);

    char user_choice;
    std::cout << "\n Want to proceed? (Y)es?, (N)o?";
    std::cin >> user_choice;

    if (user_choice == 'n' || user_choice == 'N'){
        std::cout << "Operation cancelled.\n";
        return;
    }
    else if(user_choice == 'y' || user_choice == 'Y'){
        int index{};
        std::cout << "\nEnter food index to delete: ";
        std::cin >> index;

        std::string temp_line{};
        int current_index = 0;
        bool line_deleted = false;

        while (std::getline(database, temp_line))
        {
            if (current_index == index)
            {
                std::cout << "Line deleted: " << temp_line << std::endl;
                line_deleted = true;
            }
            else
            {
                temp_database << temp_line << std::endl;
            }
            ++current_index;
        }

        if (!line_deleted)
        {
            std::cout << "Error: Invalid index. No line was deleted." << std::endl;
        }

        database.close();
        temp_database.close();

        remove("../db/db.txt");
        rename("temp_database.txt", "../db/db.txt");
    }
}

std::string Dairy::add_meal_entry()
{
    // First, display the database
    UI ui;
    if (!ui.read_db()) {
        std::cerr << RED << "Error: Could not read food database. Please ensure it exists and has items." << RESET << std::endl;
        return "";
    }

    int food_choice;
    double amount;
    std::string line;

    std::cout << "\nEnter the number of the food item you want to add: ";
    while (!(std::cin >> food_choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << RED << "Invalid input. Please enter a number: " << RESET;
    }

    std::cout << "Enter amount in grams: ";
    while (!(std::cin >> amount)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << RED << "Invalid input. Please enter a number: " << RESET;
    }

    // Get the selected food item from database
    std::ifstream database("db/db.txt");
    if (!database.is_open()) {
        std::cerr << RED << "Error: Cannot open database file." << RESET << std::endl;
        return "";
    }

    int current_line = 0;
    while (std::getline(database, line)) {
        if (current_line == food_choice - 1) { // -1 because we displayed numbers starting from 1
            break;
        }
        current_line++;
    }
    database.close();

    if (current_line != food_choice - 1) {
        std::cerr << RED << "Error: Selected item number not found in database." << RESET << std::endl;
        return "";
    }

    // Modify the amount in the selected item
    std::string modified_line = line;
    size_t first_comma = modified_line.find(',');
    if (first_comma != std::string::npos) {
        size_t second_comma = modified_line.find(',', first_comma + 1);
        if (second_comma != std::string::npos) {
            size_t third_comma = modified_line.find(',', second_comma + 1);
            if (third_comma != std::string::npos) {
                // Replace the amount (between second and third comma)
                std::string before = modified_line.substr(0, second_comma + 2); // +2 to include comma and space
                std::string after = modified_line.substr(third_comma);
                modified_line = before + std::to_string(amount) + after;
            }
        }
    }

    return modified_line;
}

void Dairy::add_new_daily_entry()
{
    Parser parser;
    std::string file_path = "db/dailies/" + parser.create_date_stamp() + "/";
    
    create_directory(file_path);
    std::cout << file_path << std::endl;
    std::string meal_data = add_meal_entry() + "\n";
    
    std::ofstream timestamp(file_path + get_meal_time() + ".txt", std::ios::app);
    timestamp << meal_data;
    timestamp.close();
}

std::string Dairy::get_meal_time()
{
	const std::vector<std::string> meal_options = {"Breakfast", "Lunch", "Dinner"};
	
	std::cout << "Select:" << std::endl;
	for (size_t i = 0; i < meal_options.size(); ++i) {
		std::cout << i + 1 << ". " << meal_options[i] << std::endl;
	}

	int option;
	std::cout << "Enter option: ";
	std::cin >> option;
	
	if (option >= 1 && option <= static_cast<int>(meal_options.size())) {
		return meal_options[option - 1];
	}

	return "Invalid option";
}

void Dairy::write_to_db(const std::string& itemData) {
    std::ofstream database("db/db.txt", std::ios::app);  // Changed path and added append mode
    
    if (!database.is_open()) {
        std::cerr << RED << "Error: Cannot open database file for writing." << RESET << std::endl;
        return;
    }

    // Add a newline before writing if the file is not empty
    std::ifstream check_file("db/db.txt");
    if (check_file.peek() != std::ifstream::traits_type::eof()) {
        database << std::endl;
    }
    check_file.close();

    database << itemData;
    database.close();

    std::cout << GREEN << "Successfully added to database!" << RESET << std::endl;
}
