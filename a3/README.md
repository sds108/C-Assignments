# Assignment 3 - Searching with Trees

## Task 1
Implement a binary search tree using char as the data records.

Using the function above, the string “FLOCCINAUCINIHILIPILIFICATION” can be loaded and printed in sorted order.

Compile command:
gcc -Wall bst_skeleton.c main.c -o t1

Run command:
./t1

## Task 2
Implement a database which uses a binary search tree with a randomly generated dataset. Try to keep the tree balanced if possible.

Compile command:
gcc -Wall -g src/task2.c src/bstdb.c src/db/profiler.c src/db/database.c src/db/listdb.c -o task2 -lm

Run command:
./task2