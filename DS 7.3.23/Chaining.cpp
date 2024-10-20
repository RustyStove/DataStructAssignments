#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 5

struct Book{
	char title[50];
	int price;
	Book* next;
	Book* prev;
}*head[SIZE], *tail[SIZE];


Book* createBook(char title[], int price){
	Book* newBook = (Book*)malloc(sizeof(Book));
	
	strcpy(newBook->title, title);
	
	newBook->price = price;
	newBook->next = NULL;
	newBook->prev = NULL;
	
	return newBook;
}

int hashFunction(char title[]){
	return title[0] % SIZE;
}


void push(Book* newBook){
	int hashKey = hashFunction(newBook->title);
	
	if(head[hashKey] == NULL){
		head[hashKey] = tail[hashKey] =newBook;
		
	} else if(newBook->price < head[hashKey]->price){
		newBook->next = head[hashKey];
		head[hashKey]->prev = newBook;
		head[hashKey]= newBook;
	} else if(newBook->price > tail[hashKey]->price){
		tail[hashKey]->next = newBook;
		newBook->prev = tail[hashKey];
		tail[hashKey] = newBook;
	} else{
		Book* curr = head[hashKey];
		Book* prevCurr = head[hashKey];
		
		while(curr){
			if(curr->price > newBook->price){
				prevCurr->next = newBook;
				newBook->next =curr;
				
				curr->prev =newBook;
				newBook->prev = prevCurr;
				
				break;
			}
			prevCurr = curr;
			curr = curr->next;
		}
	}
}

void printBook(){
	for(int i = 0; i<SIZE; i++){
		printf("%d. ", i);
		
		Book* curr = head[i];
		while(curr != NULL){
			printf("%s, %d ->", curr->title, curr->price);
			curr = curr->next;
		}
		
		printf("-\n");
	}
}

int main(){
	push(createBook("asd", 15000));
	printBook();
	
	printf("\n");
	
	push(createBook("bcd", 43000));
	printBook();
	
	printf("\n");
	
	push(createBook("abc", 44000));
	printBook();
	
	printf("\n");
	
	return 0;
}
