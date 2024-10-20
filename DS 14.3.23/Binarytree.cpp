#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// view
// inorder
// preorder
// postorder

//predecessor kiri 1x, kanan sampai habis
//successor kanan 1x, kiri sampai habis

struct node{
	char name[50];
	int age;
	node* left;
	node* right;
	
};

node* createNode(char name[], int age){
	node* newNode = (node*)malloc(sizeof(node));
	strcpy(newNode->name, name);
	newNode->age = age;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

node* insert(node* root, char name[], int age){
	if(!root){
		return createNode(name, age);
	}else if(age < root->age){
		root->left = insert(root->left, name, age); //recursive until it find no node then insert itself there
	}else if(age > root->age){
		root->right = insert(root->right, name, age);
			}
	return root;
}

node* update(node* root, char name[], int search){
	if(!root){
		printf("No Data\n");
		return NULL;
	}else if(root->age == search){
		strcpy(root->name, name);
		return root;
	}else if(root->age > search){
		return update(root->left, name, search);
	}else if(root->age < search){
		return update(root->right, name, search);
	}
}

void inorder(node* root){
	if(!root){
		return;
	}
	inorder(root->left);
	printf("%s, %d\n", root->name, root->age);
	inorder(root->right);
}

void preorder(node* root){
	if(!root){
		return;
	}
	printf("%s, %d\n", root->name, root->age);
	inorder(root->left);
	inorder(root->right);
}

void postorder(node* root){
	if(!root){
		return;
	}
	inorder(root->left);
	inorder(root->right);
	printf("%s, %d\n", root->name, root->age);
}

node* popAll(struct node *root){
	if(!root){
		return NULL;
	}
	root->left = popAll(root->left);
	root->right = popAll(root->right);
	free(root);
	root = NULL;
	return root;
}

node* find(struct node* root, int search){
	if(!root){
		printf("No Data\n");
		return NULL;
	}else if(root->age == search){
		return root;
	}else if(root->age >= search){
		return find(root->left, search);
	}else if(root->age < search){
		return find(root->right, search);
	}
}

node* pop(struct node* root, int search){
	if(!root){
		printf("No Data\n");
		return NULL;
	}else if(root->age > search){
		root->left = pop(root->left, search);
	}else if(root->age < search){
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
			node* temp = root->left!=NULL ? root->left : root->right;
			free(root);
			root = temp;	
		
		}else if(root->left&& root->right){
			node* temp = root->left;
			
			while(temp->right){
				temp = temp->right;
			}
			
			root->age = temp->age;
			strcpy(root->name, temp->name);
			root->left = pop(root->left, temp->age);
		}
	}
	return root;
}

int main(){
	node* root = NULL; //starting point once a node is added it becomes root similir to how in linked list it becomes head
	root = insert(root, "johny", 12);
	root = insert(root, "jill", 5);
	root = insert(root, "bob", 15);
		
	inorder(root);
	printf("\n");
	
	preorder(root);
	printf("\n");
	
	postorder(root);
	printf("\n");
	
	update(root, "stuart", 12);
	update(root, "james", 5);
	update(root, "jim", 15);
	
	printf("\n");
	
	pop(root,12);
	
	inorder(root);
	
	node* temp = find(root,15);
	
	printf("\n");
	
	if(temp){
		printf("%s %d\n", temp->name, temp->age);
	}

	popAll(root);
	printf("\n");
	
	return 0;	
}
