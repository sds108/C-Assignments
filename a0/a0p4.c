#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Part 4

#define MAX_LEN 1000

int next_field(FILE *csv, char *buffer, int max_len);

struct pokemon {
	int number;
	char name[MAX_LEN];
	char type1[MAX_LEN];
	char type2[MAX_LEN];
	int Total;
	int HP;
	int Attack;
	int Defense;
	int SpAtk;
	int SpDef;
	int Speed;
	int Generation;
	char Legendary[MAX_LEN];
	char PokedexEntry[MAX_LEN];
};

struct pokemon pokedex[1000];

int main () {
	
	char buffer[MAX_LEN];
	
	FILE *file;
	
	file = fopen("pokemon.csv", "r");
	
	int lineCounter = -1;
	int paramCounter = 0;
	
	// Read out the file
	while (!feof(file)) {
		if (next_field(file, &buffer[0], MAX_LEN) && !feof(file)) {
			if (lineCounter >= 0) {
				memcpy(buffer, pokedex[lineCounter].PokedexEntry, sizeof pokedex[lineCounter].PokedexEntry);
			}
			lineCounter++;
			paramCounter = 0;
		} else {
			switch (paramCounter) {
				case 0: {
					pokedex[lineCounter].number = atoi(buffer);
				}
				case 1: {
					memcpy(buffer, pokedex[lineCounter].name, sizeof pokedex[lineCounter].name);
					//pokedex[lineCounter].name = buffer;
				}
				case 2: {
					memcpy(buffer, pokedex[lineCounter].type1, sizeof pokedex[lineCounter].type1);
					//pokedex[lineCounter].type1 = buffer;
				}
				case 3: {
					memcpy(buffer, pokedex[lineCounter].type2, sizeof pokedex[lineCounter].type2);
					//pokedex[lineCounter].type2 = buffer;
				}
				case 4: {
					pokedex[lineCounter].Total = atoi(buffer);
				}
				case 5: {
					pokedex[lineCounter].HP = atoi(buffer);
				}
				case 6: {
					pokedex[lineCounter].Attack = atoi(buffer);
				}
				case 7: {
					pokedex[lineCounter].Defense = atoi(buffer);
				}
				case 8: {
					pokedex[lineCounter].SpAtk = atoi(buffer);
				}
				case 9: {
					pokedex[lineCounter].SpDef = atoi(buffer);
				}
				case 10: {
					pokedex[lineCounter].Speed = atoi(buffer);
				}
				case 11: {
					pokedex[lineCounter].Generation = atoi(buffer);
				}
				case 12: {
					memcpy(buffer, pokedex[lineCounter].Legendary, sizeof pokedex[lineCounter].Legendary);
					//pokedex[lineCounter].Legendary = buffer;
				}
			}
			paramCounter++;
		}
	}
	
	fclose(file);
	
	return 0;
}

int next_field(FILE *csv, char *buffer, int max_len) {
	int c;
	int n = 0;
	
	bool insideQuote = false;
	
	// Get the next entry
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
}
