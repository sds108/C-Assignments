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

#define MAX_STRING_SIZE 200 //max length of a string
#define ARRAY_SIZE 99991 //best be prime
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

/*
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
*/

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
	unsigned long long hash = 4273; // 181243 very good
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
	/*
	Element* newNode = (struct Node*)malloc(sizeof(struct Node));
	
	(*newNode).name = data;
	
	(*newNode).previous = NULL;
	
	(*newNode).next = *head;
	*/
	
	if (*head != NULL) (**head).previous = newNode;
	
	*head = newNode;
}

// returns the index of the surnames, -1 if not found
int search (char* surname) {
	long long initial = hash_function(surname);
	long long jump_hash = hash3(surname);
	long long temp = 0;
	
	//printf("%s\n", surname);
	
    for (int i = 0; i < ARRAY_SIZE; i++) {
		///*
		temp = abs(((i * jump_hash) + initial) % ARRAY_SIZE);
		//printf("index %i jump %i init %i\n", temp, jump_hash, initial);
		
		if (hashTable[temp] != NULL) {
			if (hashTable[temp]->surname != NULL && surname != NULL) {
				if (strcmp(hashTable[temp]->surname, surname) == 0) {
					return temp;
				}
			}
		}
		//*/
		
		/*
		match = true;
		if (hashTable[((i * jump_hash) + initial) % ARRAY_SIZE] != NULL) {
			for (int c = 0; c < MAX_STRING_SIZE; c++) {
				//printf("%c\n", surname[c]);
				//printf("%c\n", hashTable[((i * jump_hash) + initial) % ARRAY_SIZE]->surname[c]);
				if (hashTable[((i * jump_hash) + initial) % ARRAY_SIZE]->surname != NULL && surname != NULL) {
					if (surname[c] != NULL && hashTable[((i * jump_hash) + initial) % ARRAY_SIZE]->surname[c] != NULL) {
						if (surname[c] != hashTable[((i * jump_hash) + initial) % ARRAY_SIZE]->surname[c]) {
							match = false;
							break;
						}
						
						if (surname[c] == '\0') break;
					} else printf("NULL ERROR\n");
				}
			}
			
			if (match) return ((i * jump_hash) + initial) % ARRAY_SIZE;
		}
		//*/
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



// From assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_tokenfggrf ( char *buf, FILE *f, int string_max ) {
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
			
void next_tokenfhgj (char* buffer, FILE* csv, int max_len) {
	int c;
	int n = 0;
	
	while (1) {
		c = fgetc(csv);
		
		printf("c == %d\n", c);
		
		// Switch because this is killing me
		if (c == EOF) {
			buffer[n] = '\0';
			return;
		}
		
		switch (c) {
			case 10:
				buffer[n] = '\0';
				return;
			case 44:
				buffer[n] = '\0';
				return;
			case 32:
				buffer[n] = c;
				n++;
			case 48:
				buffer[n] = c;
				n++;
			case 49:
				buffer[n] = c;
				n++;
			case 50:
				buffer[n] = c;
				n++;
			case 51:
				buffer[n] = c;
				n++;
			case 52:
				buffer[n] = c;
				n++;
			case 53:
				buffer[n] = c;
				n++;
			case 54:
				buffer[n] = c;
				n++;
			case 55:
				buffer[n] = c;
				n++;
			case 56:
				buffer[n] = c;
				n++;
			case 57:
				buffer[n] = c;
				n++;
			case 65:
				buffer[n] = c;
				n++;
			case 66:
				buffer[n] = c;
				n++;
			case 67:
				buffer[n] = c;
				n++;
			case 68:
				buffer[n] = c;
				n++;
			case 69:
				buffer[n] = c;
				n++;
			case 70:
				buffer[n] = c;
				n++;
			case 71:
				buffer[n] = c;
				n++;
			case 72:
				buffer[n] = c;
				n++;
			case 73:
				buffer[n] = c;
				n++;
			case 74:
				buffer[n] = c;
				n++;
			case 75:
				buffer[n] = c;
				n++;
			case 76:
				buffer[n] = c;
				n++;
			case 77:
				buffer[n] = c;
				n++;
			case 78:
				buffer[n] = c;
				n++;
			case 79:
				buffer[n] = c;
				n++;
			case 80:
				buffer[n] = c;
				n++;
			case 81:
				buffer[n] = c;
				n++;
			case 82:
				buffer[n] = c;
				n++;
			case 83:
				buffer[n] = c;
				n++;
			case 84:
				buffer[n] = c;
				n++;
			case 85:
				buffer[n] = c;
				n++;
			case 86:
				buffer[n] = c;
				n++;
			case 87:
				buffer[n] = c;
				n++;
			case 88:
				buffer[n] = c;
				n++;
			case 89:
				buffer[n] = c;
				n++;
			case 90:
				buffer[n] = c;
				n++;
			case 97:
				buffer[n] = c;
				n++;
			case 98:
				buffer[n] = c;
				n++;
			case 99:
				buffer[n] = c;
				n++;
			case 100:
				buffer[n] = c;
				n++;
			case 101:
				buffer[n] = c;
				n++;
			case 102:
				buffer[n] = c;
				n++;
			case 103:
				buffer[n] = c;
				n++;
			case 104:
				buffer[n] = c;
				n++;
			case 105:
				buffer[n] = c;
				n++;
			case 106:
				buffer[n] = c;
				n++;
			case 107:
				buffer[n] = c;
				n++;
			case 108:
				buffer[n] = c;
				n++;
			case 109:
				buffer[n] = c;
				n++;
			case 110:
				buffer[n] = c;
				n++;
			case 111:
				buffer[n] = c;
				n++;
			case 112:
				buffer[n] = c;
				n++;
			case 113:
				buffer[n] = c;
				n++;
			case 114:
				buffer[n] = c;
				n++;
			case 115:
				buffer[n] = c;
				n++;
			case 116:
				buffer[n] = c;
				n++;
			case 117:
				buffer[n] = c;
				n++;
			case 118:
				buffer[n] = c;
				n++;
			case 119:
				buffer[n] = c;
				n++;
			case 120:
				buffer[n] = c;
				n++;
			case 121:
				buffer[n] = c;
				n++;
			case 122:
				buffer[n] = c;
				n++;
		}
		
		if (n + 1 >= max_len) break;
	}
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
	
	//printArray();
	printf(NAME_PROMPT);
	
	while (1) {
		scanf("%[^\n]%*c", input);
		//fgets(input, MAX_STRING_SIZE, stdin);
		if (quit(input)) {
			clearMemory();
			break;
		}
		printNumberOfOccurences(input);
		printf(NEW_LINE_PROMPT);
	}
    
    return 0;
}