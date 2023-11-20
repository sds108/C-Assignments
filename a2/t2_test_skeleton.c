#include "t1.h"
#include "t2.h"
#include <stdio.h>

#define size 40

int main() {
    int arr[size];
	
	printf("\n\nSelection Sort\n");
	fill_ascending(arr, size);
	printArray(arr, size);
	
	selectionSort(arr, size);
	printArray(arr, size);
	
	printf("\n\nSelection Sort\n");
	fill_descending(arr, size);
	printArray(arr, size);
	
	selectionSort(arr, size);
	printArray(arr, size);
	
	printf("\n\nSelection Sort\n");
	fill_with_duplicates(arr, size);
	printArray(arr, size);
	
	selectionSort(arr, size);
	printArray(arr, size);
	
	printf("\n\nSelection Sort\n");
	fill_without_duplicates(arr, size);
	printArray(arr, size);
	
	selectionSort(arr, size);
	printArray(arr, size);
	
	
	
	printf("\n\nInsertion Sort\n");	
	fill_ascending(arr, size);
	printArray(arr, size);
	
	insertionSort(arr, size);
	printArray(arr, size);
	
	printf("\n\nInsertion Sort\n");
	fill_descending(arr, size);
	printArray(arr, size);
	
	insertionSort(arr, size);
	printArray(arr, size);
	
	printf("\n\nInsertion Sort\n");
	fill_with_duplicates(arr, size);
	printArray(arr, size);
	
	insertionSort(arr, size);
	printArray(arr, size);
	
	printf("\n\nInsertion Sort\n");
	fill_without_duplicates(arr, size);
	printArray(arr, size);
	
	insertionSort(arr, size);
	printArray(arr, size);
	
	
	
	printf("\n\nQuick Sort\n");	
	fill_ascending(arr, size);
	printArray(arr, size);
	
	quickSort(arr, size);
	printArray(arr, size);
	
	printf("\n\nQuick Sort\n");
	fill_descending(arr, size);
	printArray(arr, size);
	
	quickSort(arr, size);
	printArray(arr, size);
	
	printf("\n\nQuick Sort\n");
	fill_with_duplicates(arr, size);
	printArray(arr, size);
	
	quickSort(arr, size);
	printArray(arr, size);
	
	printf("\n\nQuick Sort\n");
	fill_without_duplicates(arr, size);
	printArray(arr, size);
	
	quickSort(arr, size);
	printArray(arr, size);
	
	return 0;
}