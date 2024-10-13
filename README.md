# Welcome

Your personal assistant application is a C++ program designed to help users manage their nutrition and fitness by offering a food database to log daily meals, track calories and macronutrients, and monitor daily weight. It simplifies tracking progress and maintaining healthy habits with its user-friendly interface for entering and reading data.

# Getting Started

-   Navigate to the root folder.
-   Type `make` in terminal to build the program.
-   After compilation has completed, navigate to folder build/
-   Type `./output` to run the program.

# Features

## Food Database

This feature allows users to enter detailed information about their food, including:

-   Name: Enter the name of the food item.
-   Brand: Record the brand of the food, providing more specific tracking for branded products.
-   Amount: Specify the serving size or quantity of the food.
-   Macros: Track the fat, carbs, and protein content of each food item.

![Food database](https://i.imgur.com/OHHqiRl.png)

## Daily Calorie Intake

This feature lets users select food items from the database and enter the amount consumed. The program then calculates the total calories based on the consumed amount, providing a clear overview of daily intake and the specific food consumed.

![Daily Entries](https://i.imgur.com/dwYXomd.png)

## Daily Weight Tracking

Users can log their weight each day, and the program stores this data for easy reading and tracking over time, helping to monitor progress.

![Weight](https://i.imgur.com/YM9PmJP.png)

### Supported platforms

Currently only UNIX is supported. If you need the applicatin to run on Windows, feel free to contribute.
