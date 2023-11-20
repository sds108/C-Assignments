#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArray (int* array, int size) {
	for (int i = 0; i < size; i++) {
		array[i] = rand();
	}
}

int sortArray (int* array, int size) {
	int counter = 1;
	
	int temp;
	
	while (counter != 0) {
		counter = 0;
		
		for (int i = 0; i < size - 1; i++) {
			// Smallest to Largest
			if (array[i] > array[i + 1]) {
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				counter++;
			}
		}
	}
	
	return 1;
}

void printArray (int* array, int size) {
	for (int i = 0; i < size; i++) {
		printf("%i\n", array[i]);
	}
	
	printf("\n\n");
}
	

int main () {
	srand(time(NULL));
	
	const int size = 100000;
	int arr[size];
	
	fillArray(arr, size);
	
	//printArray(arr, size);
	
	if (sortArray(arr, size)) printf("Done\n"); // printArray(arr, size);
	
	return 0;
}