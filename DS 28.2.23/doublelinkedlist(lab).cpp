#include <stdio.h>
#include <stdlib.h>

struct node{
	int value;
	node* next;// to show next data
	node* prev;// to show prev data
	
}*head,*tail;


node* createNode(int value){
	node* newNode = (node*)malloc(sizeof(node)); //(node*) is typecast
	newNode->value = value;
	newNode->next = newNode->prev = NULL;
	
	return newNode;
}

void pushHead(node* data){
	if(!head){
		head = tail = data;
	}else{
		data->next = head;
		head->prev = data;
		head = data;
	}
}

void pushTail(node* data){
	if(!head){
		head = tail = data;
	}else{
		data->prev = tail;
		tail->next = data;
		tail = data;
	}
}

void pushMid(node* data){
	if(!head){
		head = tail = data;
	}else if(data->value <= head->value){
		pushHead(data);
	}else if(data->value >= tail->value){
		pushTail(data);
	}else{
		node* curr = head;
		while(curr && curr->value <=data->value){
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
	if(!head){
		printf("No Data\n");
	}else{
		if(head->value == value){
			popHead();
		}else if(tail->value == value){
			popTail();
		}else{
			node* curr= head;
			
			while(curr->next && curr->next->value != value){
				curr = curr->next;
			}
			
			if(!curr->next){
				printf("No Data\n");
			}
			
			node* del = curr->next;
			curr->next = del->next;
			del->next->prev = curr;
			del=NULL;
			free(del);
		}
	}
}

void Search(int value){
	if(!head){
		printf("No Data\n");
		return;
	}else{
		if(head->value == value){
			printf("Found at Head");
			return;
		}else if(tail->value == value){
			printf("Found at Tail");
			return;
		}else{
			node* curr= head;
			
			int count = 0;
			
			while(curr && curr->value != value){
				curr = curr->next;
				count++;
			}
			
			if(!curr->next){
				printf("No Data\n");
				return;
			}
			
			printf("Found at %d\n", count);
		}
	}
	
}

void printAll(){
	node* curr = head;
	
	while(curr){
		printf("%d->", curr->value);
		curr = curr->next;
	}
}


int main(){
	pushMid(createNode(1));
	pushMid(createNode(12));
	pushMid(createNode(11));
	pushMid(createNode(10));
	pushMid(createNode(0));
	pushMid(createNode(13));
	printAll();
	Search(10);
	popHead();
	popTail();
	printf("\n");
	printAll();
	
	popMid(10);
	popMid(12);
	
	printf("\n");
	printAll();
;	return 0;
}
