#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
	char name[50];
	int priority;
	node* next;
	node* prev;
	
}*head = NULL, *tail = NULL;

node* createNode(char name[20],int priority){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->priority = priority;
	strcpy(newNode->name, name);
	newNode->next = newNode->prev = NULL;
	
	return newNode;
}

void pushHead(node* project){
	if(!head){
		head = tail = project;
	}else{
		project->next = head;
		head->prev = project;
		head = project;
	}
}

void pushTail(node* project){
	if(!head){
		head = tail = project;
	}else{
		project->prev = tail;
		tail->next = project;
		tail = project;
	}
}

void pushMid(node* data){
	if(!head){
		head = tail = data;
	}else if(data->priority <= head->priority){
		pushHead(data);
	}else if(data->priority >= tail->priority){	//make case if same priorirty
		pushTail(data);
	}else{
		node* curr = head;
		while(curr && curr->priority <=data->priority){
			curr = curr->next;
		}
		data->next = curr;
		data->prev = curr->prev;
		curr->prev->next = data;
		curr->prev = data;
		
	}
}


void inputproject(){
	
	printf("Register New Project\n");
	printf("========================================================================\n");
	
	
	char name[50] = " ";
	int priority = 0;
	int len = 0;
				
	while(len < 5 || len > 40){
					
		printf("Input project name [5-40]: ");
		scanf("%[^\n]", &name);
		len = strlen(name);
		getchar();
	}
	
	while (priority < 1 || priority > 10){
		printf("Input project priority [1-10]: ");
		scanf("%d", &priority);
	}
	
	pushMid(createNode(name, priority));
	printf("Successfully registered a new project!\n");
	getchar();
	
	return;
	
}


void viewdata(){
	
	if(!head){
		printf("No Projects.\n");
		return;
	}
	
	printf("View Project List\n");
	printf("========================================================================\n");
	printf("\n");
	
	printf("|==============================================================|\n");
	printf("| %-2s | %-40s | %-12s |\n", "NO", "Project Name", "Priority");
	printf("|====|=========================================================|\n");
	
	node* curr = head;
	int i = 1;
	
	while(curr){
		
		printf("| %-2d | %-40s | %12d |\n", i, curr->name, curr->priority);
		printf("|==============================================================|\n");
		curr = curr->next;
		i++;
	}
	return;
}

int main(){
	
	int choice= 0;
	while (choice != 4){
		choice = 0;
		printf("CStich Project Manager\n");
		printf("========================================================================\n");
		printf("1. Register New Project\n");
		printf("2. Assign Programmer to Project\n");
		printf("3. View Project List\n");
		printf("4. Exit\n");
		printf("Choose: ");
		
		scanf("%d", &choice);
		getchar();
		
		switch(choice){
			case 1:
			
				printf("\n");
				
				inputproject();
				
				printf("\nPress ENTER To Continue\n");
				getchar();
				
				break;
			
			case 2:
				printf("\n");
			
				printf("\nPress ENTER To Continue\n");
				getchar();
				
				break;	
			
			case 3:
				printf("\n");
				
				viewdata();
				
				printf("\nPress ENTER To Continue\n");
				getchar();
				
				break;
		}
	}
	
	printf("\nAll data successfully removed!\n");
	printf("Program Exited\n");
	return 0;
}
