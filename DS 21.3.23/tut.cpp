#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct tnode{
	int x;
	struct tnode *left, *right;
}*root = NULL;

void inOrder(struct tnode *curr){
	if(curr->left) inOrder(curr->left);
	printf("%d ", curr->x);
	if(curr->right) inOrder(curr->right); 
}

void preOrder(struct tnode *curr){
	printf("%d ", curr->x);
	if(curr->left) inOrder(curr->left);
	if(curr->right) inOrder(curr->right); 
}

void postOrder(struct tnode *curr){
	if(curr->left) inOrder(curr->left);
	if(curr->right) inOrder(curr->right); 
	printf("%d ", curr->x);
}

struct tnode *newNode(int x){
	struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
	node->left = node->right = NULL;
	node->x = x;
}

int find(struct tnode *curr, int x){
	if(curr){
		if(curr->x == x) printf("Found!\n");
		else if(x<curr->x) find(curr->left, x);		
		else if(x>curr->x) find(curr->right, x);		
	}
}

void insert(struct tnode *curr, int x){
	if(!root) root = newNode(x);
	else{
		if(x < curr->x){
			if(curr->left) insert(curr->left, x);
			else curr->left = newNode(x);
		}else if(x>curr->x){
//			
		}
	}
}

int main(){
	
	root = newNode(40);
	
	root->left = newNode(20);
	root->right = newNode(70);
	
	postOrder(root);
	
	return 0;
}
