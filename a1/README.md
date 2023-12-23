# Assignment 0 - Introduction to the Module

## Task 1
You should write a hash table to store the frequency of names in an (unordered) list of Irish surnames.

Compile command:
gcc a1p1.c -o t1

Run command:
./t1 names.csv

## Task 2
Now find a better hash function hash2 for the data considered. Feel free to consult online resources, but make a reference to them in your report. Note, the sample data is only a sample! Do not overfit your function to the sample provided, it should work well with any lists of Irish surnames. Justify your choice of hash function in your report (half a page max). Test your function on the sample data, indicate in your report how many collisions occur, is it better than the result from task 1? (Note that it is expected that you will get less collisions than the automatic tests here!)

I ended up using FNV-1a (Fowler Noll Vo).

Compile command:
gcc a1p2.c -o t2

Run command:
./t2 names.csv

## Task 3
Demonstrate the improvement of double hashing over linear probing. (Compared to Task 1)

Compile command:
gcc a1p3.c -o t3

Run command:
./t3 names.csv

## Task 4
For this task you should expand (a copy of) your solution to the previous tasks. Instead of storing term counts at each index, you should store a list of people with a given surname. The keys of the hash table will be surnames. The values will be linked lists of people.

Compile command:
gcc a0p4.c -o t4

Run command:
./t4 people.csv
