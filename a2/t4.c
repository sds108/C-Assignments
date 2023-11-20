#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARRAY_SIZE 50000
#define MAX_STRING_SIZE 200

typedef struct Game Game;
struct Game {
	char title[MAX_STRING_SIZE];
	char platform[MAX_STRING_SIZE];
	int score, release_year;
};

int gameCounter = -1;
int scores[ARRAY_SIZE];
Game* database[ARRAY_SIZE];

void swap (int a, int b) {
	int tempS = scores[a];
	Game* tempP = database[a];
	
	database[a] = database[b];
	database[b] = tempP;
	
	scores[a] = scores[b];
	scores[b] = tempS;
}

void partition (int start, int end) {
	int i = start;
	int j = end - 1;
	int p = end;
	
	int side = 0;
	
	if (start == end) return;
	
	while (i <= j) {
		switch (side) {
			case 0: {
				if (scores[i] > scores[p]) {
					swap(i, p);
					p = i;
					side = !side;
				} else i++;
				break;
			}
			
			case 1: {
				if (scores[j] < scores[p]) {
					swap(j, p);
					p = j;
					side = !side;
				} else j--;
				break;
			}
		}
	}
	
	if (p - 1 >= start) partition(start, p - 1);
	if (p + 1 <= end) partition(p + 1, end);	
}

void quickSort (int size) {
	if (size > 0) partition(0, size - 1);
}

void next_token (char* buffer, FILE* csv, int max_len) {
	int c;
	int n = 0;
	bool insideQuotes = false;
	
	while (1) {
		c = fgetc(csv);
		
		// Switch because this is killing me
		if (c == EOF) {
			buffer[n] = '\0';
			break;
		}
		
		if (c == '\n') {
			buffer[n] = '\0';
			break;
		}
		
		if (c == '\"') {
			insideQuotes = !insideQuotes;
		}
		
		if (c == ',') {
			if (insideQuotes) {
				buffer[n] = c;
				n++;
			} else {
				buffer[n] = '\0';
				break;
			}
		}
		
		else {
			buffer[n] = c;
			n++;
		}
		
		/*
		if (c == 32) {
			buffer[n] = c;
			n++;
		}
		
		if (c >= 48 && c <= 57) {
			buffer[n] = c;
			n++;
		}
		
		if (c >= 65 && c <= 90) {
			buffer[n] = c;
			n++;
		}
		
		if (c >= 97 && c <= 122) {
			buffer[n] = c;
			n++;
		}
		*/
		
		if (n + 1 >= max_len) {
			buffer[n] = '\0';
			break;
		}
	}
	
	if (n == 0) {
		buffer[0] = '0';
		buffer[1] = '\0';
	}
}

//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];
	int paramCounter = 0;
	bool skippedLine = false;
	Game* current = NULL;

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	// read until the end of the file
	while (!feof(f)) {
		next_token(buf, f, MAX_STRING_SIZE);
		
		if (strlen(buf) == 0) {
			buf[0] = '0';
			buf[1] = '\0';
		}
		
		if (skippedLine) {
			if (current != NULL) {
				switch (paramCounter) {
					case 0:
						strcpy(current->title, buf);
						break;
					case 1:
						strcpy(current->platform, buf);
						break;
					case 2:
						current->score = atoi(buf);
						scores[gameCounter] = current->score;
						break;
					case 3:
						current->release_year = atoi(buf);
						break;
				}
			}
		}
		
		if (paramCounter >= 3 && !feof(f)) {
			if (skippedLine) {
				current = (Game*)malloc(sizeof(Game));
				gameCounter++;
				database[gameCounter] = current;
			}
			skippedLine = true;
			paramCounter = -1;
		}
		
		paramCounter++;
	}
	
	// always remember to close your file stream
	fclose(f);

	return 1;
}

void printArray () {
	///*
	for (int i = 0; i < gameCounter; i++) {
		if (database[i] != NULL) {
			printf("%-51s%-21s%i", database[i]->title, database[i]->platform, database[i]->score);
			if (database[i]->score < 10) printf("  %i\n", database[i]->release_year);
			else printf(" %i\n", database[i]->release_year);
		} else printf("NULL\n");
	}
	//*/
	
	/*
	for (int i = 0; i < gameCounter; i++) {
		printf("%i\n", scores[i]);
	}
	//*/
}

void printTop10 () {
	int temp = 0;
	for (int i = 0; i < 10; i++) {
		temp = (gameCounter - 1) - i;
		if (database[temp] != NULL) {
			printf("%-51s%-21s%i", database[temp]->title, database[temp]->platform, database[temp]->score);
			if (database[temp]->score < 10) printf("  %i\n", database[temp]->release_year);
			else printf(" %i\n", database[temp]->release_year);
		}
	}
}

void delete () {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (database[i] != NULL) free(database[i]);
	}
}

int main ( int argc, char *argv[] ) {
    
	load_file(argv[argc-1]);
	
	quickSort(gameCounter);
	
	//printArray();
	
	printTop10();
	
	delete();
	
	return 0;
}