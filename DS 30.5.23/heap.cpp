//Max Heap
#include <stdio.h>
#include <limits.h>

//check again for min heap in recording (at the end 1:20 in

int size = 0;
int heap[100] = {INT_MAX};
//int heap[100] = {INT_MIN}; //for min heap


void swap(int curr, int parent){
	int temp = heap[curr];
	heap[curr] = heap[parent];
	heap[parent] = temp;
}

void insert(int value){
	size++;
	heap[size] = value;
	
	//Upheapify Max Heap
	int currIndex = size;
	while(heap[currIndex] > heap[currIndex/2]){
		swap(currIndex,currIndex/2);
		
		currIndex = currIndex/2;
	}
	
//	//Upheapify Min heap
//	int currIndex = size;
//	while(heap[currIndex] < heap[currIndex/2]){
//		swap(currIndex,currIndex/2);
//		
//		currIndex = currIndex/2;
//	}
	
}

int getLeftChild(int curr){
	if(curr*2 > size){
		return INT_MIN;
	}
	
	return heap[curr*2];
}

int getRightChild(int curr){
	if(curr*2+1 > size){
		return INT_MIN;
	}
	
	return heap[curr*2+1];
}

void downHeapify(int curr){ 
	int parent = heap[curr];
	int leftchild = getLeftChild(curr);
	int rightchild = getRightChild(curr);
	
	//max
	if(leftchild>parent||rightchild>parent){
		if(leftchild > rightchild){
			swap(curr*2, curr);
			downHeapify(curr*2);
		}else if(rightchild > leftchild){
			swap(curr*2+1, curr);
			downHeapify(curr*2+1);
		}
	}
//	//min
//	if(leftchild<parent||rightchild<parent){
//		if(leftchild < rightchild){
//			swap(curr*2, curr);
//			downHeapify(curr*2);
//		}else if(rightchild < leftchild){
//			swap(curr*2+1, curr);
//			downHeapify(curr*2+1);
//		}
//	}
}

int extract(){
	int temp = heap[1];
	heap[1] = heap[size];
	heap[size] = 0;
	size--;
	
	downHeapify(1);
	
	return temp;
}

void print(){
	for(int i = 1; i<=size; i++){
		printf("Parent: %d ", heap[i]);
		printf("Left: %d ", heap[i*2]);
		printf("Right: %d\n", heap[(i*2)+1]);
	}
}

int main(){
	
	insert(10);
	insert(20);
	insert(30);
	insert(40);
	insert(50);
	print();
	
	puts("");
	printf("%d\n", extract());
	print();
	
	return 0;
}
