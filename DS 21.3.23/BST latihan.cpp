#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct node{
	int value;
	node* left;
	node* right;
	
};

node* createNode(int value){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

node* insert(node* root, int value){
	if(!root){
		return createNode(value);
	}else if(value < root->value){
		root->left = insert(root->left, value); //recursive until it find no root then insert itself there
	}else if(value > root->value){
		root->right = insert(root->right, value);
			}
	return root;
}

node* find(node* root, int search){
	if(!root){
		printf("No Data\n");
		return NULL;
	}else if(root->value == search){
		printf("Found %d in tree\n", root->value);
	}else if(root->value > search){
		return find(root->left, search);
	}else if(root->value < search){
		return find(root->right, search);
	}
}

void inorder(node* root){
	if(!root){
		return;
	}
	inorder(root->left);
	printf("%d ", root->value);
	inorder(root->right);
}

node* pop(struct node* root, int search){
	if(!root){
		printf("No Data\n");
		return NULL;
	}else if(root->value > search){
		root->left = pop(root->left, search);
	}else if(root->value < search){
		root->right = pop(root->right, search);
	}else{
		if(!root->left && !root->right){
			free(root);
			root = NULL;
//		}else if(root->left && !root->right){
//			node* temp = root->left;
//			free(root);
//			root = temp;
//		}else if(!root->left&& root->right){
//			node* temp = root->right;
//			free(root);							// this is used to take the next one in the tree and replace it with the erased one
//			root = temp;
		}else if(!root->left || !root->right){
			printf("Masuk\n");
			node* temp = root->left!=NULL ? root->left : root->right;
			free(root);
			root = temp;	
		
		}else if(root->left&& root->right){
			node* temp = root->left;
			
			while(temp->right){
				temp = temp->right;
			}
			
			root->value = temp->value;
			root->left = pop(root->left, temp->value);
		}
	}
	return root;
}


int main(){
	node* root = NULL;
	root = insert(root, 20);
	root = insert(root, 210);
	root = insert(root, 10);
	root = insert(root, 30);
	
	inorder(root);
	printf("\n");
	
	find(root, 30);
	find(root, 12);
	
	pop(root, 210);
	
	inorder(root);
	printf("\n");
	
	
	
	
// delete
	

	return 0;	
}
