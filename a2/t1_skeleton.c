#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "t1.h"

//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size) {
    for (int i = 0; i < size; i++) {
		array[i] = i;
	}
}

//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size) {
    for (int i = 0; i < size; i++) {
		array[(size - 1) - i] = i;
	}
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size) {
	//srand(time(NULL));
	int temp = ((int)rand()) % 10;
	for (int i = 0; i < size; i++) {
		array[i] = temp;
	}
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size) {
	//srand(time(NULL));
    for (int i = 0; i < size; i++) {
		array[i] = ((int)rand()) % size;
	}
}

// Returns 1 if num is unique in array, 0 if not
int uniqueCheck (int* arr, int size, int num) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == num) return 0;
	} return 1;
}

//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size) {
	//srand(time(NULL));
	int temp;
	for (int i = 0; i < size; i++) {
		temp = rand() % size;
		while (!uniqueCheck(array, i, temp)) {
			temp = ((int)rand()) % size;
		}
		array[i] = temp;		
	}
}

void printArray(int* arr, int size){
	int i;
	for(i=0; i<size;i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}