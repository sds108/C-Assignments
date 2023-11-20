#include <stdio.h>

// Part 1

char name[100];
int age;

int main () {
	
	// Prompt user for name
	printf("Name >> ");
	scanf("%s", name);
	
	// Prompt user for age
	printf("Age >> ");
	scanf("%i", &age);
	
	// Say Hello
	printf("Hello %s (%i)", name, age);

	return 0;
}
