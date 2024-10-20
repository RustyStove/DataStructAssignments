#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char name[21];
    double bmi;
    char category[15];
    
    node* next;
    node* prev;
    
}*head=NULL,*tail=NULL;

node* createNode(char name[],double weight, double height){
    
    node* newnode = (node*)malloc(sizeof(node));
    strcpy(newnode->name,name);
    newnode->bmi = weight/(height*height);
    newnode->next = newnode->prev = NULL;
    if (newnode->bmi<18.5){
        strcpy(newnode->category,"Underweight");
    }else if(newnode->bmi>25){
        strcpy(newnode->category,"Overweight");
    }else if(newnode->bmi>=18.5 || newnode->bmi<=25){
        strcpy(newnode->category,"Normal");
    }
    
    return newnode;
}

void pushHead(node* data){
    if(!head){
        head=tail=data;
    }else{
        data->next=head;
        head->prev=data;
        head=data;
    }
}

void pushTail(node* data){
    if(!head){
        head=tail=data;
    }else{
        data->prev=tail;
        tail->next=data;
        tail=data;
    }
}

void pushMid(node* data){
    if(!head){
        head=tail=data;
    }else if(data->bmi < head->bmi){
        pushHead(data);
    }else if(data->bmi > tail->bmi){
        pushTail(data);
    }else{
        node*curr= head;
        while (curr && curr->bmi <= data->bmi){
            curr=curr->next;
        }
        
        data->next=curr;
        data->prev=curr->prev;
        curr->prev->next=data;
        curr->prev=data;
    }
}

void popHead(){
    node*del= head;
    head=head->next;
    free(del);
    del=NULL;
}

void popTail(){
    node*del=tail;
    tail=tail->prev;
    free(del);
    tail->next=NULL;
}

void popNormal(){
    if(!head){
        printf("No Data Yet\n");
        return;
    }
    
    if(strcmp(head->category,"Normal")==0){
        popHead();
    }
    
    if (strcmp(tail->category,"Normal")==0){
        popTail();
    }
    
    node*curr= head;
    
    while(curr && curr->next){
        if(strcmp(curr->next->category,"Normal")==0){
            node*del= curr->next;
            curr->next=del->next;
            del->next->prev= curr;
            free(del);
            del=NULL;
            
        }
    }
}

void popAll(){
    
    while(head){
        popHead();
    }
    
    head=tail=NULL;
}

void printAll(){
    if(!head){
        printf("No Data Yet!\n");
        return;
    }
    
    node* curr= head;
    
	printf("|%-25s|%-10s|%-20s|\n", "Name", "BMI", "Category");
    
	while(curr){
    	printf("|%-25s|%-10.2lf|%-20s|\n",curr->name,curr->bmi,curr->category);
    	curr=curr->next;
	}
}

int main() {
	int input=0;
	while(input != 3){
    	printAll();
    	printf("1.Add new data\n2.Delete Normal BMI\n3.Exit\nPlease select an option:");
    	scanf("%d",&input);
    	getchar();
        
        switch(input){
            case 1:
            {
            	char tempname[21] = "";
    			double tempweight;
    			double tempheight;
    			int namecount;	
    			
    			do{
    				printf("Full Name: [2-20]: ");
    				scanf("%[^\n]", tempname);
    				getchar();
    				namecount = strlen(tempname);
    				
    				if(namecount<2||namecount>20){
    					printf("Name must be 2-20 characters long!\n");
					}
					
					
				}while(namecount<2||namecount>20);
				
				do{
					printf("Weight: [35.00-300.00] in KG: ");
    				scanf("%lf", &tempweight);
    				
    				if(tempweight<35.00||tempweight>300.00){
    					printf("Weight must be in between 35.00-300.00 KG\n");
					}
				}while(tempweight<35.00||tempweight>300.00);
				
				do{
					printf("Height: [0.50-3.00] in Meters: ");
    				scanf("%lf", &tempheight);
    				getchar();
    				
    				if(tempheight<0.50||tempheight>3.00){
    					printf("Height must be in between 0.50-3.00 Meters\n");
					}
				}while(tempheight<0.50||tempheight>3.00);
				
				pushMid(createNode(tempname,tempweight,tempheight));
				
				printf("Success Adding new data!\n");
            	break;
            }
           
        	case 2:
        	{
        		popNormal();
				break;
            }
        	default:
        	{
			break;
    		}
		}
	}
    
    popAll();
    printf("Program Ended\n");
    
    return 0;
}
