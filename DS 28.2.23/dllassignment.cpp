#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	char name[20];
	int id;
	int stock;
	node* next;// to show next data
	node* prev;// to show prev data
	
}*head = NULL,*tail = NULL;


node* createNode(char name[20],int id, int stock){
	node* newNode = (node*)malloc(sizeof(node)); //(node*) is typecast
	newNode->stock = stock;
	strcpy(newNode->name, name);
	newNode->id = id;
	newNode->stock = stock;
	newNode->next = newNode->prev = NULL;
	
	return newNode;
}

void pushHead(node* item){
	if(!head){
		head = tail = item;
	}else{
		item->next = head;
		head->prev = item;
		head = item;
	}
}

void pushTail(node* item){
	if(!head){
		head = tail = item;
	}else{
		item->prev = tail;
		tail->next = item;
		tail = item;
	}
}

void pushMid(node* data){
	if(!head){
		head = tail = data;
	}else if(data->id <= head->id){
		pushHead(data);
	}else if(data->id >= tail->id){
		pushTail(data);
	}else{
		node* curr = head;
		while(curr && curr->id <=data->id){
			curr = curr->next;
		}
		data->next = curr;
		data->prev = curr->prev;
		curr->prev->next = data;
		curr->prev = data;
		
	}
}

void popHead(){
	if(!head){
		printf("No data\n");
		return;
	}else if(head == tail){
		free(head);
		head = NULL;
	}else{
		node*del = head;
		head = head->next;
		free(del);
		del = NULL;
	}
}

void popTail(){
	if(!head){
		printf("No Data\n");
		return;
	}else if(head == tail){
		free(head);
		head = NULL;
	}else{
		node*del = tail;
		tail = tail->prev;
		tail->next = NULL;
		free(del);
	}
}

void popMid(int value){
	
	char option = ' ';
	
	if(!head){
		printf("No Data In List\n");
		getchar();
		return;
	}else{
		if(head->id == value){
			while(option != 'Y' || option != 'N'){
				printf("\nAre you sure you want to delete this item? [Y\\N]: ");
				scanf(" %c", &option);
				getchar();
				
				if(option == 'Y'){
					popHead();
					return;
				}else if(option == 'N'){
					printf("Item Not Deleted\n");
					return;
				}else{
					printf("Please Enter Valid Option\n");
					continue;
				}
				
			}
		}else if(tail->id == value){
			while(option != 'Y' || option != 'N'){
				printf("\nAre you sure you want to delete this item? [Y\\N]: ");
				scanf(" %c", &option);
				getchar();
				
				if(option == 'Y'){
					popTail();
					return;
				}else if(option == 'N'){
					printf("Item Not Deleted\n");
					return;
				}else{
					printf("Please Enter Valid Option\n");
					continue;
				}
				
			}
			
		}else{
			node* curr= head;
			
			while(curr->next && curr->next->id != value){
				curr = curr->next;
			}
			
			if(!curr->next){
				printf("There is no item with that ID\n");
				return;
			}
			
			while(option != 'Y' || option != 'N'){
				printf("\nAre you sure you want to delete this item? [Y\\N]: ");
				scanf(" %c", &option);
				getchar();
				
				if(option == 'Y'){
					node* del = curr->next;
					curr->next = del->next;
					del->next->prev = curr;
					del=NULL;
					free(del);
					return;
				}else if(option == 'N'){
					printf("Item Not Deleted\n");
					return;
				}else{
					printf("Please Enter Valid Option\n");
					continue;
				}
				
			}
		} 
	}
}

void printAll(){
	if(!head){
		printf("No Data In List\n");
		return;
	}
	node* curr = head;
	
	while(curr){
		printf("#%d | %s | %d\n", curr->id, curr->name, curr->stock);
		curr = curr->next;
	}
}

int main(){
	int choice= 0;
	while (choice != 4){
		choice = 0;
		printf("----Main Menu----\n");
		printf("1. Insert Data\n");
		printf("2. View Data\n");
		printf("3. Delete Data\n");
		printf("4. Exit\n");
		printf("Please Choose An Option: ");
		
		scanf("%d", &choice);
		getchar();
		
		switch(choice){
			case 1:
				printf("\n");
				char name[20];
				int id;
				int stock;
				printf("Enter Item ID: ");
				scanf("%d", &id);
				getchar();
				printf("Enter Item Name [<=20]: ");
				scanf("%[^\n]", name);
				printf("Enter Amount of Stock: ");
				scanf("%d", &stock);
				getchar();
				pushMid(createNode((char*)name, id, stock));
				printf("\n");
				break;
				
			case 2:
				printf("\n");
				printAll();
				printf("\nPress ENTER To Continue\n");
				getchar();
				break;
				
			case 3:
				printf("\n");
				int temp;
				char confirm;
				printf("Enter Item ID to delete: ");
				scanf("%d", &temp);
				
				popMid(temp);
				printf("\nPress ENTER To Continue\n");
				getchar();
				break;
				
			default:
				printf("\n");
				break;
		}
	}
	node* curr= head;
			
	while(curr->next){
		curr = curr->next;
		node* del = curr->next;
		curr->next = del->next;
		del->next->prev = curr;
		del=NULL;
		free(del);
		
	}
	printf("Program Exited\n");
	return 0;
}
