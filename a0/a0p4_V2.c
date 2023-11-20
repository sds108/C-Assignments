#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

int next_field(FILE *csv, char *buffer, int max_len);

struct pokemon {
	int number, Total, HP, Attack, Defense, SpAtk, SpDef, Speed, Generation;
	char name[MAX_LEN];
	char type1[MAX_LEN];
	char type2[MAX_LEN];
	char Legendary[MAX_LEN];
	char PokedexEntry[MAX_LEN];
};

struct pokemon pokedex[1000];

int main (int arguments, char* arg[]) {
	
	char buffer[MAX_LEN];
	
	FILE *file;
	
	file = fopen(arg[1], "r");
	
	int lineCounter = -1, paramCounter = 0;
	
	while (!feof(file)) {
		if (next_field(file, &buffer[0], MAX_LEN) && !feof(file)) {
			if (lineCounter >= 0) {
				memcpy(pokedex[lineCounter].PokedexEntry, buffer, MAX_LEN);
			}
			lineCounter++;
			paramCounter = 0;
		} else {
			if (lineCounter >= 0) {
				switch (paramCounter) {
					case 0: {
						pokedex[lineCounter].number = atoi(buffer);
					}
					case 1: {
						memcpy(pokedex[lineCounter].name, buffer, MAX_LEN);
					}
					case 2: {
						memcpy(pokedex[lineCounter].type1, buffer, MAX_LEN);
					}
					case 3: {
						memcpy(pokedex[lineCounter].type2, buffer, MAX_LEN);
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
						memcpy(pokedex[lineCounter].Legendary, buffer, MAX_LEN);
					}
				}
			}
			paramCounter++;
		}
	}
	
	double avg = 0;
	for (int i = 0; i <= lineCounter; i++) {
		avg += pokedex[i].Attack;
	}
	
	avg /= lineCounter + 1;
	
	printf("%.5f0", avg);
	
	fclose(file);
	
	return 0;
}

int next_field(FILE *csv, char *buffer, int max_len) {
	int c;
	int n = 0;
	
	bool insideQuote = false;
	
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