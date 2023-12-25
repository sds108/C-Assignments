#include "t1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 20

int main() {
	srand(time(NULL));
	int arr[size];
	
	printf("\nFilling in Ascending Order\n");
	fill_ascending(arr, size);
	printArray(arr, size);
	
	printf("\nFilling in Descending Order\n");
	fill_descending(arr, size);
	printArray(arr, size);
	
	printf("\nFilling with a Random Number\n");
	fill_uniform(arr, size);
	printArray(arr, size);
	
	printf("\nFilling with Random Numbers\n");
	fill_with_duplicates(arr, size);
	printArray(arr, size);
	
	printf("\nFilling with Unique Random Numbers\n");
	fill_without_duplicates(arr, size);
	printArray(arr, size);
	
	return 0;
}