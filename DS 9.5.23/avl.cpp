#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	int num;
	char name[50];
	int height;
	Node* right;
	Node* left;
};

int getHeight(Node* newNode){
	if(!newNode){
		return 0;
	}
	
	return newNode->height;
}

//max value from height children
int getMax(int a, int b){
	if(a < b){
		return b;
	}
	return a;
}

int getBalancedFactor(Node* newNode){
	if(!newNode){
		return 0;
	}
	
	return getHeight(newNode->left) - getHeight(newNode->right);
}

Node* createNode(int num, char name[]){
	Node* newNode= (Node*) malloc(sizeof(Node));
	
	newNode->num = num;
	strcpy(newNode->name,name);
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	
	return newNode;
}

Node* leftRotate(Node* node){
	Node* right = node->right;
	Node* rightLeft = right->left;
	
	right->left = node;
	node->right = rightLeft;
	
	node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
	
	right->height = getMax(getHeight(right->left), getHeight(right->right)) + 1;
	
	return right;
}

Node* rightRotate(Node* node){
	Node* left = node->left;
	Node* leftRight = left->right;
	
	left->right = node;
	node->left = leftRight;
	
	node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
	
	left->height = getMax(getHeight(left->left), getHeight(left->right)) + 1;
	
	return left;
}

Node* insertNode(Node* root, Node* newNode){
	if(!root){
		return newNode;
	}
	
	if(newNode->num < root->num){
		root->left = insertNode(root->left,newNode);
	}else if (newNode->num >= root->num){
		root->right = insertNode(root->right,newNode);
	}else{
		return root;
	}
 
//	int leftHeight = getHeight(root->left);
//	int rightHeight = getHeight(root->right);
		
	//height from root
	root->height = getMax(getHeight(root->left),getHeight(root->right)) + 1;
		
	int bf = getBalancedFactor(root);
	
	//left
	if(bf < -1  && getBalancedFactor(root->right) <= 0){
		return leftRotate(root);
		
	//left right	
	}else if(bf > 1 && getBalancedFactor(root->left) < 0){
		newNode->left = leftRotate(root);
		return rightRotate(root);
		
	//right	
	} else if (bf > 1  && getBalancedFactor(root->left) >= 0){
		return rightRotate(root);
		
	//right left	
	}else if(bf < -1 && getBalancedFactor(root->right) > 0){
		newNode->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

Node* popAll(Node* root){
	if(!root){
		return root;
	}else{
		root->left = popAll(root->left);
		root->right = popAll(root->right);
		
		root->left = NULL;
		root->right = NULL;
		
		free(root);
		root = NULL;
	}
	return root;
}

Node* popNode(Node* root, int num){
	if(!root){
		printf("Not found\n");
		return root;
	}else if(num < root->num){
		root->left = popNode(root->left,num);
		
	}else if(num > root->num){
		root->right = popNode(root->right,num);
		
	}else if(num == root->num){
		if(!root->left && !root->right){
			free(root);
			root = NULL;
		}else if(!root->left || !root->right){
			Node* temp = root->left != NULL? root->left : root->right;
			free(root);
			root = temp;
//		}else if(root->left && !root->right){
//			Node* temp = root->;
//			free(root);
//			root = temp;
//		}else if(!root->left && root->right){
//			Node* temp = root->right;
//			free(root);
//			root = temp;
		}else if(root->left && root->right){
			Node* temp = root->left;
			while(temp->right){
				temp = temp->right;
			}
			
			strcpy(root->name, temp->name);
			root->num = temp->num;
			
			root->left = popNode(root->left, temp->num);
		}
	}
	if(!root){
		return root;
	}
	
	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);
		
	//height from root
	root->height = getMax(leftHeight,rightHeight) + 1;
		
	int bf = getBalancedFactor(root);
	
	//left
	if(bf < -1  && getBalancedFactor(root->right) <= 0){
		return leftRotate(root);
		
	//left right	
	}else if(bf < -1 && getBalancedFactor(root->left) < 0){
		root->left = leftRotate(root);
		return rightRotate(root);
		
	//right	
	} else if (bf > 1  && getBalancedFactor(root->left) >= 0){
		return rightRotate(root);
		
	//right left	
	}else if(bf < -1 && getBalancedFactor(root->right) > 0){
		rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

Node* updateNode(Node* root, int num,char name[] ){
	if(!root){
		printf("Not Found!\n");
		return root;
		
	}else if(root->num == num){
		strcpy(root->name,name);
	}
	
	if (num< root->num){
		return updateNode(root->left, num, name);
	}else if(num > root->num){
		return updateNode(root->right, num, name);
	}
}

bool searchNode(Node* root, int num){
	if(!root){
		printf("Not Found!\n");
		return false;
	}else if(root->num == num){
		printf("%d found\n", root->num);
		return true;
	}
	
	if (num< root->num){
		return searchNode(root->left, num);
	}else if(num > root->num){
		return searchNode(root->right, num);
	}
}

void printInOrder(Node* node){
	if(node){
		printInOrder(node->left);
		printf("%s: %d (height = %d)\n",node->name, node->num, node->height);
		printInOrder(node->right);
		
	}
}

int main(){
	Node* root = NULL;
	
	root = insertNode(root, createNode(3, "abc"));
	root = insertNode(root, createNode(5, "bcd"));
	root = insertNode(root, createNode(7, "cde"));
	root = insertNode(root, createNode(9, "efg"));
	printInOrder(root);
	
	printf("\n");
	
	printf("Search\n");
	searchNode(root, 3);
	searchNode(root, 5);
	searchNode(root, 7);
	searchNode(root, 10);
	
	printf("\n");
	
	printf("Update\n");
	updateNode(root, 3, "ababa");
	updateNode(root, 5, "adadad");
	updateNode(root, 7, "acacac");
	
	printInOrder(root);
	
	printf("\n");
	
	printf("Pop Node\n");
	
	root = popNode(root,5);
	
	printInOrder(root);
	
	printf("\n");
	
	printf("Pop All\n");
	
	root = popAll(root);
	
	printInOrder(root);
	return 0;
}
