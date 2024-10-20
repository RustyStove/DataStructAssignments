#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50

struct node{
	
	int idx;
	char value[50];
	
}*table[20];//sebesar size table

char toLower(char ch){
	if(ch >='A' && ch <= 'Z'){
		ch = ch + 'a' - 'A';
	}
	return ch;
}

int hash(char ch[50]){
//	return toLower(ch[0])- 'a';

	for(int i=0;ch[i] != '\0';i++){
		
	}
	
	return 0;
}

void push(char ch[50]){
	node* tnode = (node*)malloc(sizeof(node));
	strcpy(tnode->value, ch);
	int idx = hash(ch);
	node->idx;
	
	table[tnode->idx] = tnode;
}

void view(){
	for(int i=0; i< SIZE; i++){
		if(table[i]) {
			printf("H[%d] %s\n",i, table[i]);
	}
}
}

int main(){
	
	hash("DEFINE");
	view();
	
	return 0;
}
