#include<stdio.h>
#include<stdlib.h>

struct tnode{
	int value;
	struct tnode *next;
	
}*head=NULL, *tail=NULL;

void print(){
	struct tnode *curr = head;
	
	while(curr){
		printf("%d ", curr -> value);
		curr = curr ->next;
	}
}

void pushHead(int x){ //head
	struct tnode *node =(struct tnode*) malloc(sizeof(struct tnode));
	node -> value = x;
	node -> next = head;
	head = node;
	
	print();
	puts("");
}

void pushTail(int x){ //tail
	struct tnode *node =(struct tnode*) malloc(sizeof(struct tnode));
	node -> value = x;
	node -> next = NULL;
	
	struct tnode *curr = head;
	
	if(!head) head = node;
	else{
		while(curr -> next){
			curr = curr -> next;
		}
		
		curr -> next = node;
	}

//	if(!head) head = tail = node;
//	else{
//			tail -> next = node;
//			tail = node;
//	

	print();
	puts("");
}

void pushAfter(int x, int key){
    struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
    node->value = x;
    node->next = NULL;
    
    if(tail && tail->value == key){
        pushTail(x);
        return;
    }
    
    struct tnode *curr = head;
    while(curr && curr->value != key){
        curr = curr->next;
    }
    
    if(curr){
        node->next = curr->next;
        curr->next = node;
    }else puts("Key not found!!");
    
    print();
    puts("");
}

void pushBefore(int x, int key){
    struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
    node->value = x;
    node->next = NULL;
    
    if(head && head->value == key){
        pushHead(x);
        return;
    }
    
    struct tnode *curr = head;
    while(curr && curr->next && curr->next->value != key){
        curr = curr->next;
    }
    
    if(curr){
        node->next = curr->next;
        curr->next = node;
    }else puts("Key not found!!");
    
    print();
    puts("");
}

void popHead(){
    struct tnode *del = head;
    head = head->next;
    free(del);
    print();
    puts("");
}

void popTail(){
	struct tnode *curr = head;
	
	while(curr -> next && curr -> next -> next){// if it is at second to last node which is going to be tail that means curr->next->next is null
		curr = curr ->next;
	}
	tail = curr;
	free(curr -> next);
	tail ->next = NULL;
	print();
	puts("");
	
}

void popKey(int key){
    if(key==head->value){
        popHead();
        return;
    }else if(key==tail->value){
        popTail();
        return;
    }
    
    tnode *curr = head;
    
    while(curr->next && curr->next->value != key){
        curr = curr->next;
    }
    
    if(curr){
        tnode *del =curr->next;
        curr->next = del->next;
        free(del);
    }
    print();
    puts("");
}

void popAll(){
	while(head){
		popHead();
	}
	
}

int main(){
	pushHead(10);
	pushHead(20);
	pushHead(30);
	pushTail(60);
	pushAfter(25, 30);
	pushBefore(35,30);
	pushHead(40);
	pushHead(50);
	popTail();
	popHead();
	popKey(30);
	popAll();
	
	return 0 ;
}
