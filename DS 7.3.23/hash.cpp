#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 5

struct Book{
	char title[50];
	int price;
}*shelf[SIZE];

Book* createBook(char title[], int price){
	Book* newBook = (Book*)malloc(sizeof(Book));
	
	strcpy(newBook->title, title);
	newBook->price = price;
	
	return newBook;
}

int hashFunction(char title[]){
	return title[0] % SIZE;
}

void push(Book *newBook){
	int  hashKey = hashFunction(newBook->title);
	
	if(shelf[hashKey] == NULL){
		shelf[hashKey] = newBook;
		
	} else {
		int index = hashKey;
		
		while(shelf[hashKey] != NULL){
			hashKey = (hashKey+1) % SIZE;
			if(index == hashKey) break;
		}
		if(index == hashKey){
			printf("Shelf is full\n");
		} else {
			shelf[hashKey] =newBook;
		}
	}
}

void pop(char title[]){
	for(int i = 0; i < SIZE; i++){
		if(shelf[i] && strcmp(shelf[i]->title, title) == 0){
			free(shelf[i]);
			shelf[i] = NULL;
			
			return;
		}
	}
	printf("Book not found\n");
}

void search(char title[]){
	for(int i = 0; i < SIZE; i++){
		if(shelf[i] && strcmp(shelf[i]->title, title) == 0){
			printf("Book %s Found In index %d\n", title, i);
			
			return;
		}
	}
	printf("Book not found\n");
}

void printBook(){
	for(int i = 0; i < SIZE; i++){
		if(shelf[i] == NULL){
			printf("%d. -\n", i);
		} else {
			
			printf("%d. %s, %d\n", i, shelf[i]->title, shelf[i]->price);
		}
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
	

	pop("asd");
	
	
	printf("\n");
	
	printBook();
	
	search("asd");
	
	search("bcd");
	
	
	return 0;
}
