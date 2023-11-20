#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum
#include <stdbool.h>

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

typedef struct Element Element;
struct Element{
	char name[MAX_STRING_SIZE];
	int freq;
};

Element* hashTable[ARRAY_SIZE];
int collisions = 0;
int num_terms = 0;

int hash_function (char* s) {
    int hash = 0;
    while (*s) {
    	hash = (hash + *s - 'A') % ARRAY_SIZE;
    	s++;
    }
    return hash;
}

int hash3 (char* s){
	int hash = 0;
	while(*s){
		hash = 1 + (hash + *s -'A') % (ARRAY_SIZE - 1);
		s++;
	}
	return hash;
}

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
	int jump_hash = hash3(name);
	
    for (int i = 0; i < ARRAY_SIZE; i++) {
		match = true;
		if (hashTable[((i * jump_hash) + initial) % ARRAY_SIZE] != NULL) {
			for (int c = 0; c < MAX_STRING_SIZE; c++) {
				if (name[c] != hashTable[((i * jump_hash) + initial) % ARRAY_SIZE]->name[c]) {
					match = false;
					break;
				}
				
				if (!name[c]) break;
			}
			
			if (match) return hashTable[((i * jump_hash) + initial) % ARRAY_SIZE];
		}
	}
    return NULL;
}

int findSpace (char* name) {
	int initial = hash_function(name);
	int jump_hash = hash3(name);
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (hashTable[((i * jump_hash) + initial) % ARRAY_SIZE] == NULL) return ((i * jump_hash) + initial) % ARRAY_SIZE;
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