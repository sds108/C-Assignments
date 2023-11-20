#include <stdio.h>
#include <stdbool.h>

// Part 2 & 3

#define MAX_LEN 10000

int next_field(FILE *csv, char *buffer, int max_len);



int main (int arguments, char* arg[]) {
	
	char buffer[MAX_LEN];
	
	FILE *file;
	
	bool skippedFirstLine = false;
	
	file = fopen(arg[1], "r");
	
	// Read out the file
	while (!feof(file)) {
		if (next_field(file, &buffer[0], MAX_LEN)) {
			if (skippedFirstLine) printf("%s\n\n", buffer);
			skippedFirstLine = true;
		}
		else if (skippedFirstLine) printf("%s \n", buffer);
	}
	
	fclose(file);
	
	return 0;
}

int next_field(FILE *csv, char *buffer, int max_len) {
	int c;
	int n = 0;
	
	bool insideQuote = false;
	
	// Read out next word
	while (!feof(csv)) {
		c = fgetc(csv);
		
		if (c == '\"') insideQuote = !insideQuote;	
		else if (c == ',' && !insideQuote) return 0;
		else if (c == '\n' || c == EOF) {
			*(buffer + n + 1) = '\0';
			return 1;
		} else {
			*(buffer + n) = c;
			*(buffer + n + 1) = '\0';
			n++;
		}
		
		if (n + 1 >= max_len) break;
	}
	
	return 1;
}
