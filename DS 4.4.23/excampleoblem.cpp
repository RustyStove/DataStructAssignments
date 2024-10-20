#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> 

#define m 20

//make node for hash table and create node#
//make it chaning#
//division method has cahining function#
//make id uppercase first two letters of name,,first letter of gender, age, and 2 random numbers#
// push pop view#



//make name case sensitive gender not, job free, age in between 18-70
//make search function

struct node{
	char name [20];
	char gender[10];
	char id[10];
	int age;
	char job[30];
	
	node* next;
	node* prev;
}*head[m], *tail[m];

char * idfunc(char name [], char gender[],int age){
	char id[10]= "";
	id [0] = toupper(name[0]);
	id [1] = toupper(name[1]);
	id [2] = toupper(gender[0]);
	sprintf(id +strlen(id), "%d", age);
	srand(time(NULL));
	int randomnum = rand() % 100;
	sprintf(id +strlen(id), "%d", randomnum);
	
	return id;
	
}


node* createNode(char name [], char gender[],int age,char job[]){
	node* newnode = (node*)malloc(sizeof(node));
	
	strcpy(newnode->name,name);
	strcpy(newnode->gender,gender);
	strcpy(newnode->job,job);
	newnode->age = age;
	
	strcpy(newnode->id,idfunc(name,gender,age));
	
	newnode->next = newnode->prev = NULL;
	
	return newnode;
}

int hashfunc(char id[]){
	int key = 0;
	
	for(int i = 0; id[i] != '\0'; i++){
		key += id[i];
	}
	
	key = key % m;
	
	return key;
}

void insert(node* data){
	int hash = hashfunc(data->id);
	
	if(head[hash] == NULL){
		head[hash]=tail[hash]=data;
	}else if(data->age < head[hash]->age){
		data->next = head[hash];
		head[hash]->prev = data;
		head[hash] = data;
	}else if(data->age > tail[hash]->age){
		data->prev = tail[hash];
		tail[hash]->next = data;
		tail[hash] = data;
	}else{
		node*curr = head[hash];
		while(curr && curr->age <= data->age){
			curr= curr->next;
		}
		data->next = curr;
		data->prev = curr->prev;
		curr->prev->next = data;
		curr->prev =data;
	}
}

void datadel(char id[]){
	int hash = hashfunc(id);
	
	if(!head[hash]){
		printf("No data\n");
	}else if(strcmp(head[hash]->id, id) == 0){
		node* del = head[hash];
		head[hash] = head[hash]->next;
		free(del);
		del = NULL;
		return;
	}else if(strcmp(tail[hash]->id, id) == 0){
		node* del = tail[hash];
		tail[hash] = tail[hash]->prev;
		free(del);
		tail[hash]->next = NULL;
		return;
	}else{
		node* curr = head[hash];
		while(curr->next && strcmp(curr->next->id, id) != 0){
			curr= curr->next;
		}
		
		if(!curr->next){
			printf("No Data Found\n");
			return;
		}
		
		node*del = curr->next;
		curr->next = del->next;
		del->next->prev = curr;
		free(del);
		del= NULL;
		printf("Data Deleted!");
		
		return;
	}	
}

void search(char id()){
	
	
}

void printAll(){
	
	for(int i = 0; i<=m; i++){
		printf("---Table %d---\n", i);
		node*curr = head[i];
		
		if(!curr){
			printf("No data in this table\n");
			printf("\n");
			continue;
		}
		
		int count = 1;
		
		printf("|%-5s|%-10s|%-25s|%-4s|%-8s|%-35s|\n","No.","ID","Name", "Age", "Gender", "Job");
		
		
		
		while(curr){
			printf("|%-5d|%-10s|%-25s|%-4d|%-8s|%-35s|\n",count,curr->id,curr->name,curr->age,curr->gender,curr->job);
			count++;
			curr = curr->next;
		}
		printf("\n");
	}
}

int main(){
	int input = 0;
	while(input != 4){
		printAll();
		printf("---MENU---\n");
		printf("1. Add\n");
		printf("2. Search\n");
		printf("3. Delete\n");
		printf("4. Exit\n");
		printf("Please select option: ");
		
		scanf("%d", &input);
		getchar();
		
		switch(input){
			case 1:{
				char tname [20];
				char tgender[10];
				int tage;
				char tjob[30];
				//make name case sensitive gender not, job free, age in between 18-70
				
				do{
					printf("Enter Name[5-20][Case-Sensitive]: ");
					scanf("%[^\n]", tname);
					getchar();
					
					if(!isupper(tname[0])){
						printf("First Letter must be uppercase!\n");
					}
					
					if(strlen(tname)<5||strlen(tname)>20){
						printf("Name must be 5-20 characters long!\n");
					}
					
				}while(!isupper(tname[0])||strlen(tname)<5||strlen(tname)>20);
				
				do{
					printf("Enter Gender[Male or Female][Case-Inensitive]: ");
					scanf("%[^\n]", tgender);
					getchar();
					
					for(int i = 0; i<strlen(tgender); i++){
						tgender[i] = toupper(tgender[i]);
					}
					
					tgender[8] = '\0';
					
					if(strcmp("MALE", tgender) != 0&&strcmp("FEMALE", tgender) != 0){
						printf("Gender must be Male or Female\n");
					}
					
				}while(strcmp("MALE", tgender) != 0&&strcmp("FEMALE", tgender) != 0);
				
				do{
					printf("Enter Age[18-70]: ");
					scanf("%d", &tage);
					getchar();
					
					if(tage<18||tage>70){
						printf("Age must be in between 18-70\n");
					}
				}while(tage<18||tage>70);
				
				do{
					
					printf("Enter Job[5-30][Case-Inensitive]: ");
					scanf("%[^\n]", tjob);
					getchar();
					
					if(!isupper(tjob[0])){
						printf("First Letter must be uppercase!\n");
					}
					
					if(strlen(tjob)<5||strlen(tjob)>20){
						printf("Job must be 5-20 characters long!\n");
					}
					
				}while(!isupper(tjob[0])||strlen(tjob)<5||strlen(tjob)>20);
				
				
				insert(createNode(tname, tgender,tage, tjob));
				break;
			}
			
			case 2:{
				
				break;
			}
			
			case 3:{
				char iddel[10] = "";
				printf("Enter ID to be deleted:");
				scanf("%s", iddel);
				getchar();
				datadel(iddel);
				printf("Press Enter to continue\n");
				getchar();
				break;
			}
			
			default:{
				break;
			}
		}
		
	}
	
	return 0;
}
