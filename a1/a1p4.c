#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum
#include <stdbool.h>
#include <math.h>

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

#define MAX_STRING_SIZE 60 //max length of a string
#define ARRAY_SIZE 17491 //best be prime
#define NAME_PROMPT "Enter term to get frequency or type \"quit\" to escape\n>>> " //you can use this string as your invitation to the user
#define NEW_LINE_PROMPT ">>> " //you can use this string as your invitation to the user where the user should input the name

typedef struct Element Element;
struct Element{
	
	int person_id;
	char deposition_id[MAX_STRING_SIZE];
	char surname[MAX_STRING_SIZE];
	char name[MAX_STRING_SIZE];
	int age;
	char person_type[MAX_STRING_SIZE];
	char gender[MAX_STRING_SIZE];
	char nationality[MAX_STRING_SIZE];
	char religion[MAX_STRING_SIZE];
	char occupation[MAX_STRING_SIZE];

	Element* next;
	Element* previous;
};

Element* hashTable[ARRAY_SIZE];
int collisions = 0;
int num_terms = 0;


long long hash_function (char* s) {
	unsigned long long hash = 181243; // 181243 very good
	unsigned long long multiplier = 47; // 47 very good
	
	while (*s) {
		hash ^= (unsigned long long)(*s);
		hash *= multiplier;
		hash = hash % ARRAY_SIZE;
		s++;
	}
	
	return abs(hash);
}

long long hash3 (char* s) {
	unsigned long long hash = 4273; // 4273 also very good
	unsigned long long multiplier = 47; // 47 very good
	
	while (*s) {
		hash ^= (unsigned long long)(*s);
		hash *= multiplier;
		hash = hash % ARRAY_SIZE;
		s++;
	}
	
	return abs(hash);
}

Element* createNewElement (Element* parent, int person_id, char* deposition_id, char* surname, char* name, int age, char* person_type, char* gender, char* nationality, char* religion, char* occupation) {
	Element* newElement = (Element*)malloc(sizeof(Element));
		
	newElement->person_id = person_id;
	strcpy(newElement->deposition_id, deposition_id);
	strcpy(newElement->surname, surname);
	strcpy(newElement->name, name);
	newElement->age = age;
	strcpy(newElement->person_type, person_type);
	strcpy(newElement->gender, gender);
	strcpy(newElement->nationality, nationality);
	strcpy(newElement->religion, religion);
	strcpy(newElement->occupation, occupation);
	
	newElement->previous = NULL;
	newElement->next = parent;
	
	return newElement;
}

void addElement (Element** head, int person_id, char* deposition_id, char* surname, char* name, int age, char* person_type, char* gender, char* nationality, char* religion, char* occupation) {
	Element* newNode = createNewElement(*head, person_id, deposition_id, surname, name, age, person_type, gender, nationality, religion, occupation);
	
	if (*head != NULL) (**head).previous = newNode;
	
	*head = newNode;
}

// returns the index of the surnames, -1 if not found
int search (char* surname) {
	long long initial = hash_function(surname);
	long long jump_hash = hash3(surname);
	long long temp = 0;
	
    for (int i = 0; i < ARRAY_SIZE; i++) {
		temp = abs(((i * jump_hash) + initial) % ARRAY_SIZE);
		
		if (hashTable[temp] != NULL) {
			if (hashTable[temp]->surname != NULL && surname != NULL) {
				if (strcmp(hashTable[temp]->surname, surname) == 0) {
					return temp;
				}
			}
		}
	}
    return -1;
}

int findSpace (char* surname) {
	int initial = hash_function(surname);
	int jump_hash = hash3(surname);
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (hashTable[((i * jump_hash) + initial) % ARRAY_SIZE] == NULL) return ((i * jump_hash) + initial) % ARRAY_SIZE;
		collisions++;
	} 
	printf("\nCould not find space.\n");
	return -1;
}

// assuming that no element of key name is in the list (use search first!), add element at the correct place in the list
// NB: it would be more efficient for search to return the index where it should be stored directly, but aiming for simplicity here!
void insert (int person_id, char* deposition_id, char* surname, char* name, int age, char* person_type, char* gender, char* nationality, char* religion, char* occupation) {
   num_terms++;
   int index = findSpace(surname);
   if (index >= 0) hashTable[index] = createNewElement(NULL, person_id, deposition_id, surname, name, age, person_type, gender, nationality, religion, occupation);
}

void print_list (Element* head) {
	Element* current = head;
	
	printf("%-10s%-20s%-15s%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", "Person ID", "Deposition ID", "Surname", "Forename", "Age", "Person Type", "Gender", "Nationality", "Religion", "Occupation");
	
	while (current != NULL) {
		printf("    %-9i%-20s%-14s%-17s%-17i%-20s%-20s%-20s%-20s%-20s\n", (*current).person_id, (*current).deposition_id, (*current).surname, (*current).name, (*current).age, (*current).person_type, (*current).gender, (*current).nationality, (*current).religion, (*current).occupation);
		current = (*current).next;
	}
	
	printf("\n");
}

// prints the number of occurences, or 0 if not in the file
void printNumberOfOccurences (char* surname) {
	int index = search(surname);
	
	if (index >= 0) print_list(hashTable[index]);
	else printf("%s not in table\n", surname);
}


//searches the name in the array, if it is there then add it to the linked list, otherwise place head
void addOrIncrement (int person_id, char* deposition_id, char* surname, char* name, int age, char* person_type, char* gender, char* nationality, char* religion, char* occupation) {
	int index = search(surname);
	
	if (index >= 0) addElement(&hashTable[index], person_id, deposition_id, surname, name, age, person_type, gender, nationality, religion, occupation);
	else insert(person_id, deposition_id, surname, name, age, person_type, gender, nationality, religion, occupation);
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

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	// Temporary Data Holders
	int person_id;
	char deposition_id[MAX_STRING_SIZE];
	char surname[MAX_STRING_SIZE];
	char name[MAX_STRING_SIZE];
	int age;
	char person_type[MAX_STRING_SIZE];
	char gender[MAX_STRING_SIZE];
	char nationality[MAX_STRING_SIZE];
	char religion[MAX_STRING_SIZE];
	char occupation[MAX_STRING_SIZE];
	
	// read until the end of the file
	while (!feof(f)) {
		next_token(buf, f, MAX_STRING_SIZE);
		
		if (strlen(buf) == 0) {
			buf[0] = '0';
			buf[1] = '\0';
		}
		
		if (skippedLine) {
			switch (paramCounter) {
				case 0:
					person_id = atoi(buf);
					break;
				case 1:
					strcpy(deposition_id, buf);
					break;
				case 2:
					strcpy(surname, buf);
					break;
				case 3:
					strcpy(name, buf);
					break;
				case 4:
					age = atoi(buf);
					break;
				case 5:
					strcpy(person_type, buf);
					break;
				case 6:
					strcpy(gender, buf);
					break;
				case 7:
					strcpy(nationality, buf);
					break;
				case 8:
					strcpy(religion, buf);
					break;
				case 9:
					strcpy(occupation, buf);
					break;
			}
		}
		
		if (paramCounter >= 9) {
			if (skippedLine) {
				//printf("%-20i%-20s%-20s%-20s%-20i%-20s%-20s%-20s%-20s%-20s\n", person_id, deposition_id, surname, name, age, person_type, gender, nationality, religion, occupation);
				addOrIncrement(person_id, deposition_id, surname, name, age, person_type, gender, nationality, religion, occupation);
			}
			skippedLine = true;
			paramCounter = -1;
		}
		
		paramCounter++;
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
		if (hashTable[i] != NULL) {
			printf("%-20i%-20s%-20s%-20s%-20i%-20s%-20s%-20s%-20s%-20s\n", hashTable[i]->person_id, hashTable[i]->deposition_id, hashTable[i]->surname, hashTable[i]->name, hashTable[i]->age, hashTable[i]->person_type, hashTable[i]->gender, hashTable[i]->nationality, hashTable[i]->religion, hashTable[i]->occupation);
		}
	}
}

void deleteElements (Element** head) {	
	Element* current = *head;
	
	while (current != NULL) {
		*head = (*current).next;
		
		free(current);
		
		current = *head;
	}
}

char quitString[5] = "quit\0";

void clearMemory() {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (hashTable[i] != NULL) deleteElements(&hashTable[i]);
	}
}

int quit (char* name) {
	for (int i = 0; i < 5; i++) {
		if (name[i] != quitString[i]) return 0;
	} return 1;
}

char input[MAX_STRING_SIZE];

int main ( int argc, char *argv[] ) {
    
	load_file(argv[argc-1]);
	
	printf(NAME_PROMPT);
	
	while (1) {
		scanf("%[^\n]%*c", input);
		if (quit(input)) {
			clearMemory();
			break;
		}
		printNumberOfOccurences(input);
		printf(NEW_LINE_PROMPT);
	}
    
    return 0;
}