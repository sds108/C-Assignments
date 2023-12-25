# Assignment 2 - Sorting

## Task 1
In this assignment, we want to evaluate sorting algorithms on different types of arrays. In this first task, you will write functions to generate these arrays.

Compile command:
gcc -Wall t1_skeleton.c t1_test_skeleton.c -o t1

Run command:
./t1

## Task 2 & 3
In this task, you will implement some sorting algorithms.

Update your code for task 2 to count the number of swaps and counts for each of them (using the global variables number_comparisons and number_swaps). Run t3_test.c to profile your implementations of the sort functions.

Compile command:
gcc -Wall t1_skeleton.c t2_skeleton.c t3_test.c -o t3

Run command:
./t3

## Task 4
You have been provided with a dataset of game reviews which have been gathered from IGN over the “last” 20 years. Write a program that takes the game reviews as an argument and sorts the reviews on the basis of game scores and finds out what the most popular games of the last 20 years are. (Load and sort IGN reviews and print the top 10 most popular games of the last 20 years)

Compile command:
gcc t4.c -o t4

Run command:
./t4 t4_ign.csv