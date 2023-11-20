#include <stdio.h> 
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void swap (int* arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
	number_swaps++;
}

void selectionSort (int* arr, int size) {
	int min;
	for (int i = 0; i < size - 1; i++) {
		min = i;
		for (int j = i + 1; j < size; j++) {
			number_comparisons++;
			if (arr[j] < arr[min]) min = j;
		}
		swap(arr, i, min);
	}			
}

void insertionSort (int* arr, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = i; j >= 0; j--) {
			number_comparisons++;
			
			if (arr[j] < arr[j-1] && j > 0) swap(arr, j, j-1);
			else break;
		}
	}		
}

///*
void partition (int* arr, int start, int end) {
	int i = start;
	int j = end - 1;
	int p = end;
	
	int side = 0;
	
	if (start >= end) {
		number_comparisons++;
		return;
	}
	
	//if (end - start > 2) swap(arr, p, (end - start) / 2);
	
	while (i < j) {
		number_comparisons++;
		
		switch (side) {
			case 0: {
				if (arr[i] > arr[p]) side = !side;
				else i++;
				break;
			}
			
			case 1: {
				if (arr[j] < arr[p]) {
					swap(arr, j, i);
					side = !side;
				} else j--;
				break;
			}
		}
	}
	
	number_comparisons += 2;
	if (arr[j] > arr[p]) {
		swap(arr, p, j);
		p = j;
	} else if (j + 1 < p) {
		swap(arr, p, j + 1);
		p = j + 1;
		number_comparisons++;
	} else number_comparisons++;
	
	partition(arr, start, p - 1);
	partition(arr, p + 1, end);
}
//*/

/*
void partition (int* arr, int start, int end) {
	int i = start;
	int j = end - 1;
	int p = end;
	
	int side = 0;
	
	if (start >= end) {
		number_comparisons++;
		return;
	}
	
	while (i <= j) {
		number_comparisons++;
		
		switch (side) {
			case 0: {
				if (arr[i] > arr[p]) {
					swap(arr, i, p);
					p = i;
					side = !side;
				}
				i++;
				break;
			}
			
			case 1: {
				if (arr[j] < arr[p]) {
					swap(arr, j, p);
					p = j;
					side = !side;
				}
				j--;
				break;
			}
		}
	}
	number_comparisons++;
	
	partition(arr, start, p - 1);
	partition(arr, p + 1, end);
}
//*/

void quickSort (int* arr, int size) {
	partition(arr, 0, size - 1);
}