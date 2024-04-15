//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			//removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

//insertSortedLL

// 정수 삽입 - 연결 리스트에 오름차순으로 정수 삽입 
// 현재 연결 리스트에 삽입하려는 정수가 이미 있다면 삽입하지 않음
	// 1. 현재 연결 리스트에 int item이 있는지 중복 확인
	// 2. 현재 연결 리스트 안에 int item 값이 없다면 
	
	// 현재 ll에 오름차순으로 정여 삽입하려는 정수가 들어갈 index에 맞게 삽입
		// new item이 추가되면 return index position 

// 함수가 성공하지 못하면 return -1 
// a sorted linked list  OR an empty list 

int insertSortedLL(LinkedList *ll, int item) 
{	
	//현재의 index - curindex 
	int curindex;
	curindex= 0;

	ListNode *cur; 
	cur = ll -> head;

	if (ll==NULL) 
		return -1;
	else 
	{
		//현재의 item이 insert하려는 item보다 작거나 같은 경우
		while (cur != NULL && cur -> item <= item) {
			//이미 값이 있는 경우 - 중복값인 경우
			if (cur-> item == item) {
				return -1;
			}
			//현재 노드의 item보다 
			//insert하려는 item이 더 작은 경우
			else 
			{ 
				cur = cur -> next;
				curindex = curindex +1 ;
			}
		}
		insertNode(ll, curindex, item);
		return curindex;
	}

	// int curindex;
	// curindex =0;

	// ListNode *temp;
	// temp = ll -> head; //연결 리스트의 헤드

	// //새로운 노드 동적 할당 
	// ListNode *newNode = malloc(sizeof(ListNode));

	// if (ll==NULL || newNode == NULL) 	
	// 	return -1; 
	// else {
	// 	newNode -> item = item;
	// 	newNode -> next = NULL;
		
	// 	while (temp != NULL &&  temp-> item <= item) {
	// 		temp = temp->next;
	// 	}

	// 	//이미 값이 존재하는 경우 
	// 	if (temp != NULL && temp->item == item) {
	// 		free(newNode);
	// 		return -1;
	// 	}



	// 	//연결리스트의 크기 증가 
	// 	ll->size ++;
	// 	return ll->size -1;
	// }
}
///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}