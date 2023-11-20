#include "t1.h"
#include <stdio.h>

#define size 20

int main() {
	int arr[size];
	
	fill_ascending(arr, size);
	printArray(arr, size);
	
	fill_descending(arr, size);
	printArray(arr, size);
	
	fill_uniform(arr, size);
	printArray(arr, size);
	
	fill_with_duplicates(arr, size);
	printArray(arr, size);
	
	fill_without_duplicates(arr, size);
	printArray(arr, size);
	
	return 0;
}