#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define TRY do { jmp_buf buf_state; if ( !setjmp(buf_state)) {
#define CATCH } else {
#define ENDTRY }} while(0)
#define THROW longjmp(buf_state, 1)

struct Node {
	char name;
	struct Node* previous;
	struct Node* next;
};

void add_node (struct Node** list, char data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	
	(*newNode).name = data;
	
	(*newNode).previous = NULL;
	
	(*newNode).next = *list;
	
	if (*list != NULL) (**list).previous = newNode;
	
	*list = newNode;
}

void print_list (struct Node* list) {
	struct Node* current = list;
	
	while (current != NULL) {
		printf("%c\n", (*current).name);
		current = (*current).next;
	}
	
	printf("\n");
}

void remove_node (struct Node** list, char data) {
	printf("\n\nRemove Node: %c\n", data);
	
	struct Node* current = *list;
	
	while (current != NULL) {
		if ((*current).name == data) {
			// if head, else
			if (current == *list) *list = (*current).next;
			else (*((*current).previous)).next = (*current).next;
			
			// if not last
			if ((*current).next != NULL) (*((*current).next)).previous = (*current).previous;
			
			// free the node
			free(current);
			
			break;
		}
		
		current = (*current).next;
	}
}

void remove_node_recursive () {}

void delete_list (struct Node** list) {
	printf("\n\nDelete List\n");
	
	struct Node* current = *list;
	
	while (current != NULL) {
		*list = (*current).next;
		
		free(current);
		
		current = *list;
	}
}

void reverse_list (struct Node** list) {
	printf("\n\nReverse List\n");
	
	struct Node* current = *list;
	struct Node* tempPrev = *list;
	struct Node* tempNext = *list;
	
	
	while (current != NULL) {
		if ((*current).next != NULL) *list = (*current).next;
		
		tempNext = (*current).next;
		
		tempPrev = (*current).previous;
		
		(*current).previous = (*current).next;
		
		(*current).next = tempPrev;
		
		current = tempNext;
	}
}

int main () {
	
	struct Node* head = NULL;
	
	add_node(&head, 'A');
	add_node(&head, 'B');
	add_node(&head, 'C');
	add_node(&head, 'D');
	add_node(&head, 'E');
	add_node(&head, 'F');
	add_node(&head, 'G');
	add_node(&head, 'H');
	
	print_list(head);
	
	remove_node(&head, 'A');
	
	print_list(head);
	
	reverse_list(&head);
	
	print_list(head);
	
	delete_list(&head);
	
	print_list(head);

	return 0;
}