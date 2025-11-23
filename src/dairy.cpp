#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include "../include/dairy.hpp"
#include "../include/parser.hpp"
#include "../include/database.hpp"

// Add these color constants
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string CYAN = "\033[36m";
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
        if (output.empty() || output.find_first_not_of(" \t") == std::string::npos) {
            continue; // Skip empty lines
        }
        
        std::stringstream ss(output); 
        Food entry;
        std::getline(ss, entry.name, ','); 
        // Trim whitespace from name
        entry.name.erase(0, entry.name.find_first_not_of(" \t"));
        entry.name.erase(entry.name.find_last_not_of(" \t") + 1);
        
        std::getline(ss, entry.brand, ',');
        // Trim whitespace from brand
        entry.brand.erase(0, entry.brand.find_first_not_of(" \t"));
        entry.brand.erase(entry.brand.find_last_not_of(" \t") + 1);
        
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
        // Skip empty lines to match the display logic in read_db()
        if (line.empty() || line.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }
        
        if (current_line == food_choice - 1) { // -1 because we displayed numbers starting from 1
            break;
        }
        current_line++;
    }
    database.close();

    // Check if we found a valid line (not empty)
    if (line.empty() || line.find_first_not_of(" \t") == std::string::npos) {
        std::cerr << RED << "Error: Selected item number not found in database." << RESET << std::endl;
        return "";
    }
    
    if (current_line != food_choice - 1) {
        std::cerr << RED << "Error: Selected item number not found in database." << RESET << std::endl;
        return "";
    }

    // Parse the database line to extract all values
    std::stringstream ss(line);
    std::string name, brand;
    double db_amount, db_calories, db_fat, db_carbs, db_protein;
    
    std::getline(ss, name, ',');
    // Remove leading/trailing spaces from name
    name.erase(0, name.find_first_not_of(" \t"));
    name.erase(name.find_last_not_of(" \t") + 1);
    
    std::getline(ss, brand, ',');
    // Remove leading/trailing spaces from brand
    brand.erase(0, brand.find_first_not_of(" \t"));
    brand.erase(brand.find_last_not_of(" \t") + 1);
    
    ss >> db_amount;
    ss.ignore(1); // Skip comma
    ss >> db_calories;
    ss.ignore(1); // Skip comma
    ss >> db_fat;
    ss.ignore(1); // Skip comma
    ss >> db_carbs;
    ss.ignore(1); // Skip comma
    ss >> db_protein;

    // Calculate scaling ratio based on amount
    double ratio = (db_amount > 0) ? amount / db_amount : 1.0;
    
    // Scale all nutritional values proportionally
    double scaled_calories = db_calories * ratio;
    double scaled_fat = db_fat * ratio;
    double scaled_carbs = db_carbs * ratio;
    double scaled_protein = db_protein * ratio;

    // Build the modified line with scaled values
    std::stringstream modified_ss;
    modified_ss << name << ", " 
                << brand << ", " 
                << std::fixed << std::setprecision(6) << amount << ", "
                << std::fixed << std::setprecision(6) << scaled_calories << ", "
                << std::fixed << std::setprecision(6) << scaled_fat << ", "
                << std::fixed << std::setprecision(6) << scaled_carbs << ", "
                << std::fixed << std::setprecision(6) << scaled_protein;

    return modified_ss.str();
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

Food Dairy::find_food_in_database(const std::string& name, const std::string& brand) {
    Food result;
    result.name = "";
    result.amount = 0;
    
    std::ifstream database("db/db.txt");
    if (!database.is_open()) {
        return result;
    }
    
    std::string line;
    while (std::getline(database, line)) {
        std::stringstream ss(line);
        std::string db_name, db_brand;
        
        std::getline(ss, db_name, ',');
        db_name.erase(0, db_name.find_first_not_of(" \t"));
        db_name.erase(db_name.find_last_not_of(" \t") + 1);
        
        std::getline(ss, db_brand, ',');
        db_brand.erase(0, db_brand.find_first_not_of(" \t"));
        db_brand.erase(db_brand.find_last_not_of(" \t") + 1);
        
        // Match by name and brand (case-insensitive)
        if (db_name == name && db_brand == brand) {
            result.name = db_name;
            result.brand = db_brand;
            ss >> result.amount;
            ss.ignore(1);
            ss >> result.calories;
            ss.ignore(1);
            ss >> result.fat;
            ss.ignore(1);
            ss >> result.carbs;
            ss.ignore(1);
            ss >> result.protein;
            break;
        }
    }
    
    database.close();
    return result;
}

void Dairy::fix_meal_entries(const std::string& date, const std::string& meal_name) {
    std::string file_path = "db/dailies/" + date + "/" + meal_name + ".txt";
    
    if (!std::filesystem::exists(file_path)) {
        std::cout << RED << "Meal file does not exist: " << file_path << RESET << std::endl;
        return;
    }
    
    // Read all entries from the meal file
    std::vector<Food> entries = get_food_entries(date, meal_name);
    
    if (entries.empty()) {
        std::cout << CYAN << "No entries found in " << meal_name << " for date " << date << RESET << std::endl;
        return;
    }
    
    std::vector<std::string> corrected_lines;
    int fixed_count = 0;
    
    // Fix each entry
    for (const auto& entry : entries) {
        // Look up the food in the database
        Food db_food = find_food_in_database(entry.name, entry.brand);
        
        if (db_food.amount == 0) {
            std::cerr << RED << "Warning: Food not found in database: " << entry.name << " (" << entry.brand << ")" << RESET << std::endl;
            // Keep the original entry if not found
            std::stringstream ss;
            ss << entry.name << ", " << entry.brand << ", "
               << std::fixed << std::setprecision(6) << entry.amount << ", "
               << std::fixed << std::setprecision(6) << entry.calories << ", "
               << std::fixed << std::setprecision(6) << entry.fat << ", "
               << std::fixed << std::setprecision(6) << entry.carbs << ", "
               << std::fixed << std::setprecision(6) << entry.protein;
            corrected_lines.push_back(ss.str());
            continue;
        }
        
        // Calculate scaling ratio
        double ratio = (db_food.amount > 0) ? entry.amount / db_food.amount : 1.0;
        
        // Scale all nutritional values proportionally
        double scaled_calories = db_food.calories * ratio;
        double scaled_fat = db_food.fat * ratio;
        double scaled_carbs = db_food.carbs * ratio;
        double scaled_protein = db_food.protein * ratio;
        
        // Build corrected line
        std::stringstream corrected_ss;
        corrected_ss << entry.name << ", " << entry.brand << ", "
                     << std::fixed << std::setprecision(6) << entry.amount << ", "
                     << std::fixed << std::setprecision(6) << scaled_calories << ", "
                     << std::fixed << std::setprecision(6) << scaled_fat << ", "
                     << std::fixed << std::setprecision(6) << scaled_carbs << ", "
                     << std::fixed << std::setprecision(6) << scaled_protein;
        
        corrected_lines.push_back(corrected_ss.str());
        fixed_count++;
    }
    
    // Write corrected entries back to file
    std::ofstream out_file(file_path, std::ios::trunc);
    if (!out_file.is_open()) {
        std::cerr << RED << "Error: Cannot write to file: " << file_path << RESET << std::endl;
        return;
    }
    
    for (size_t i = 0; i < corrected_lines.size(); ++i) {
        out_file << corrected_lines[i];
        if (i < corrected_lines.size() - 1) {
            out_file << std::endl;
        }
    }
    
    out_file.close();
    std::cout << GREEN << "Fixed " << fixed_count << " entries in " << meal_name << " for date " << date << RESET << std::endl;
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
