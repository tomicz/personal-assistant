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

![Weight](https://i.imgur.com/0fDG1Zr.png)

## BMI Calculator

The BMI Calculator feature allows users to easily calculate their Body Mass Index (BMI) based on their height and weight. By entering their height in centimeters and weight in kilograms, users can receive an immediate calculation of their BMI value. The feature also provides classifications (underweight, normal weight, overweight, and obesity) to help users understand their health status in relation to their BMI. This tool aims to promote awareness of healthy weight management and facilitate discussions about nutrition and wellness.

![bmi calculator](https://i.imgur.com/AS9f4h2.png)

## Goals

The Goals feature allows users to set and track their fitness goals. Users can set their weight loss or gain goals, and the program will help them track their progress towards these goals. The feature provides a clear overview of the user's current progress and the remaining distance to their goal, motivating them to stay on track and achieve their desired results.

## Fitness planner

This allows users to create personalized fitness plans, helping them set up workout routines tailored to their goals. It can guide users in organizing exercises, targeting specific muscle groups, and managing their progress over time.

![Exercises](https://i.imgur.com/d5gISMj.png)

### Supported platforms

Currently only UNIX is supported. If you need the applicatin to run on Windows, feel free to contribute.
