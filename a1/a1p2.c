#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

// NB: this skeleton is here to help you - ignore anything that does not help you
// There are a lot of others (and better!) ways of doing this

// note this sekeleton uses a global variable. It therefore will only work with 
// one hashtable, of the size set. In general global variables should be avoided
// as their global scope makes it very challenging to see where they are updated 
// (as it can be anywhere!), and don't work well when several threads/programs
// update them at the same time (concurency), amongst others problems.
// Having said that, they can make coding a bit easier, so that's why we are using 
// one here. If you can, try using a hashTable as a variable, passing it as a 
// parameter to functions!

#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 59 //best be prime
#define NAME_PROMPT "Enter term to get frequency or type \"quit\" to escape\n>>> " //you can use this string as your invitation to the user
#define NEW_LINE_PROMPT ">>> " //you can use this string as your invitation to the user where the user should input the name
#define PI 3.14159265359 

/*
// Character Prevelance
const double charStrength[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8.4966, 2.072, 4.5388, 3.3844, 11.1607, 1.8121, 2.4705, 3.0034, 7.5448, 0.1965, 1.1016, 5.4893, 3.0129, 6.6544, 7.1635, 3.1671, 0.1962, 7.5809, 5.7351, 6.9509, 3.6308, 1.0074, 1.2899, 0.2902, 1.7779, 0.2722, 0, 0, 0, 0, 0, 0, 8.4966, 2.072, 4.5388, 3.3844, 11.1607, 1.8121, 2.4705, 3.0034, 7.5448, 0.1965, 1.1016, 5.4893, 3.0129, 6.6544, 7.1635, 3.1671, 0.1962, 7.5809, 5.7351, 6.9509, 3.6308, 1.0074, 1.2899, 0.2902, 1.7779, 0.2722};

// Character Placement
const double charPlacement[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8.4966, 10.5686, 15.1074, 18.4918, 29.6525, 31.4646, 33.9351, 36.9385, 44.4833, 44.6798, 45.7814, 51.2707, 54.2836, 60.938, 68.1015, 71.2686, 71.4648, 79.0457, 84.7808, 91.7317, 95.3625, 96.3699, 97.6598, 97.95, 99.7279, 0, 0, 0, 0, 0, 0, 0, 8.4966, 10.5686, 15.1074, 18.4918, 29.6525, 31.4646, 33.9351, 36.9385, 44.4833, 44.6798, 45.7814, 51.2707, 54.2836, 60.938, 68.1015, 71.2686, 71.4648, 79.0457, 84.7808, 91.7317, 95.3625, 96.3699, 97.6598, 97.95, 99.7279};

// Character Placement increased error
const double charPlacementShifted[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8.2894, 10.11472, 14.76896, 17.37573, 29.47129, 31.21755, 33.63476, 36.18402, 44.46365, 44.56964, 45.23247, 50.96941, 53.61816, 60.22165, 67.78479, 71.24898, 70.70671, 78.47219, 84.08571, 91.36862, 95.26176, 96.24091, 97.63078, 97.77221, 99.70068, 0, 0, 0, 0, 0, 0, 0, 8.2894, 10.11472, 14.76896, 17.37573, 29.47129, 31.21755, 33.63476, 36.18402, 44.46365, 44.56964, 45.23247, 50.96941, 53.61816, 60.22165, 67.78479, 71.24898, 70.70671, 78.47219, 84.08571, 91.36862, 95.26176, 96.24091, 97.63078, 97.77221, 99.70068};

// Dataset Sourced
const double charPlacementDataset[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.151857835, 0.16720517, 0.215670436, 0.258481422, 0.334410339, 0.344911147, 0.378029079, 0.451534733, 0.516155089, 0.516962843, 0.524232633, 0.605008078, 0.6453958, 0.759289176, 0.843295638, 0.846526656, 0.84733441, 0.907915994, 0.928917609, 0.945880452, 0.968497577, 0.973344103, 0, 0.976575121, 0, 0, 0, 0, 0, 0, 0, 0, 0.151857835, 0.16720517, 0.215670436, 0.258481422, 0.334410339, 0.344911147, 0.378029079, 0.451534733, 0.516155089, 0.516962843, 0.524232633, 0.605008078, 0.6453958, 0.759289176, 0.843295638, 0.846526656, 0.84733441, 0.907915994, 0.928917609, 0.945880452, 0.968497577, 0.973344103, 0, 0.976575121, 0};

// Dataset Sourced
const double charStrengthDataset[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.151857835, 0.015347334, 0.048465267, 0.042810985, 0.075928918, 0.010500808, 0.033117932, 0.073505654, 0.064620355, 0.000807754, 0.00726979, 0.080775444, 0.040387722, 0.113893376, 0.084006462, 0.003231018, 0.000807754, 0.060581583, 0.021001616, 0.016962843, 0.022617124, 0.004846527, 0.003231018, 0, 0.023424879, 0, 0, 0, 0, 0, 0, 0, 0.151857835, 0.015347334, 0.048465267, 0.042810985, 0.075928918, 0.010500808, 0.033117932, 0.073505654, 0.064620355, 0.000807754, 0.00726979, 0.080775444, 0.040387722, 0.113893376, 0.084006462, 0.003231018, 0.000807754, 0.060581583, 0.021001616, 0.016962843, 0.022617124, 0.004846527, 0.003231018, 0, 0.023424879, 0};
*/

typedef struct Element Element;
struct Element{
	char name[MAX_STRING_SIZE];
	int freq;
};

Element* hashTable[ARRAY_SIZE];
int collisions = 0;
int num_terms = 0;

/*
long hash_function (char* s) {
    long hash = 0;
    while (*s) {
       hash = (int)(hash*PI + *s - 'A') % ARRAY_SIZE; // 13, 7 good, PI very good
        s++;
    }
    return hash;
}
*/

unsigned long long hash_function (char* s) {
	unsigned long long hash = 181243; // 181243 very good
	unsigned long long multiplier = 47; // 47 very good
	
	while (*s) {
		hash ^= (unsigned long long)(*s);
		hash *= multiplier;
		hash = hash % ARRAY_SIZE;
		s++;
	}
	
	return hash;
}

/*
long hash_function (char* s) {
    long hash = 17;
    int c;

    while (*s) {
        hash = (((hash << 5) + hash) + *s) % ARRAY_SIZE;
		s++;
    }

    return hash;
}
*/

/*
int modifyNum (int num) {
	if (num == 32) return 0;
	return num - 64;
}
*/

/*
int custom_hash (char* s, int len) {
    int hash = 0;
	
	if (len > 1) hash = abs(modifyNum(s[0]) + modifyNum(s[1]) + modifyNum(s[len - 1]) + modifyNum(s[len]));
	
	printf("len %i hash %i\n", len, hash);
	
	return (int)(hash*PI*PI*PI*PI*PI / 232) % ARRAY_SIZE;
}
*/

Element* createNewElement (char* name) {
	Element* newElement = (Element*)malloc(sizeof(Element));
    newElement->freq = 1;
	strcpy(newElement->name, name);
	
	return newElement;
}


// returns the element with name name or NULL if the element is not present
Element* search (char* name) {
	bool match = true;
	int initial = hash_function(name);
	
    for (int i = 0; i < ARRAY_SIZE; i++) {
		match = true;
		if (hashTable[(i + initial) % ARRAY_SIZE] != NULL) {
			for (int c = 0; c < MAX_STRING_SIZE; c++) {
				if (name[c] != hashTable[(i + initial) % ARRAY_SIZE]->name[c]) {
					match = false;
					break;
				}
				
				if (!name[c]) break;
			}
			
			if (match) return hashTable[(i + initial) % ARRAY_SIZE];
		}
	}
    return NULL;
}

int findSpace (char* name) {
	int initial = hash_function(name);
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (hashTable[(i + initial) % ARRAY_SIZE] == NULL) return (i + initial) % ARRAY_SIZE;
		collisions++;
	} 
	printf("\nCould not find space.\n");
	return -1;
}

// assuming that no element of key name is in the list (use search first!), add element at the correct place in the list
// NB: it would be more efficient for search to return the index where it should be stored directly, but aiming for simplicity here!
void insert (char* name) {
   num_terms++;
   int index = findSpace(name);
   if (index >= 0) hashTable[index] = createNewElement(name);
}

// prints the number of occurences, or 0 if not in the file
void printNumberOfOccurences (char* name) {
	Element* ptr = search(name);
	
	if (ptr != NULL) {
		printf("%s - %i \n", name, ptr->freq);
	} else printf("%s - 0 \n", name);
}

//searches the name in the array, if it is there increment its count, if not, add it
void addOrIncrement(char* name){
	Element* ptr = search(name);
	
	if (ptr != NULL) ptr->freq++;
	else if (ptr == NULL) insert(name);
}



// From assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token ( char *buf, FILE *f, int string_max ) {
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);                // get next character from file
		if( !isalnum(buf[i]) ) { 
            if(buf[i]!=' '){ // we still want to keep spaces
                break; // only load letters and numbers
            }
        } 
		if( feof(f) ) { break; }          // file ended?
		if( i < (string_max-1) ) { ++i; } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string
}


//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	// read until the end of the file
	while ( !feof(f) ) {
		next_token(buf, f, MAX_STRING_SIZE);
		addOrIncrement(buf);
	}
    
    printf("File %s loaded\n", fname);
    float load = (float)num_terms / ARRAY_SIZE;
    printf(" Capacity: %i\n Num Terms: %i\n Collisions: %i\n Load: %f\n", ARRAY_SIZE, num_terms, collisions, load);
	// always remember to close your file stream
	fclose(f);

	return 1;
}

void printArray () {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		printf("Index: %i", i);
		if (hashTable[i] != NULL) printf(", Name: %s, Frequency: %i\n", hashTable[i]->name, hashTable[i]->freq);
		else printf(", Pointer: NULL\n");
	}
}

char quitString[5] = "quit\0";

int quit (char* name) {
	for (int i = 0; i < 5; i++) {
		if (name[i] != quitString[i]) return 0;
	} return 1;
}

char input[MAX_STRING_SIZE];

int main ( int argc, char *argv[] ) {
    
	//TODO0
	//advice: follow the TODO number order
	//first test insert and search
    //then move on to addOrIncrement
    //only then worry about loading the file - see the function above and assignment 0 as to have to use arguments for your executable
    //and later again about an interactive interface - see the assignment 0 solution and the #define strings above
	
	load_file(argv[1]);
	
	//printArray();
	printf(NAME_PROMPT);
	
	while (1) {
		scanf("%[^\n]%*c", input);
		if (quit(input)) return 0;
		printNumberOfOccurences(input);
		printf(NEW_LINE_PROMPT);
	}
    
    return 0;
}