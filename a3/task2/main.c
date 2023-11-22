#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

int limit = 1;
int midpoint = 1;

int array[1610612738];

int level = 0;
int level_counter = 0;
int two_to_level = 1;

void update_multipliers () {
	if (level_counter > two_to_level - 1) {
		level++;
		two_to_level = pow(2, level);
		level_counter = -(two_to_level - 1);
	}
}

int main () {
	midpoint = 1-(INT_MIN / 2);
	
	unsigned int temp = UINT_MAX / 2;
	int log_result = round(log2(temp)) - 2;
	printf("Log_Result %i\n", log_result);
	printf("Log_Result actual %f\n", log2(temp));
	
	limit = pow(2, log_result);
	
	int start = midpoint - limit;
	int end  = midpoint + limit;
	
	printf("%i\n", end + 1);
	
	for (int i = 0; i < end; i++) {
		array[i] = 1;
	}
	
	int sum = 0;
	for (int i = 0; i < end; i++) {
		sum += array[0];
	}
	
	printf("Sum Before: %i\n", sum);
	
	int id = 0;
	
	while (level < 30) {
		double L = limit;
		double TTL = two_to_level;
		double LC = level_counter;
		double temp = round((L / TTL) * LC);
		int temp2 = temp;
		id = midpoint + temp2;
		array[id] = 0;
		level_counter += 2;
		update_multipliers();
	}
	
	sum = 0;
	for (int i = 0; i < end; i++) {
		sum += array[0];
	}
	
	printf("Sum After: %i\n", sum);
	
	return 0;
}