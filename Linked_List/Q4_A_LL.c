//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveEvenItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
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


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all even integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveEvenItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving even integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
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

// 홀수 값을 가진 노드 => 짝수 값을 가진 노드들 

void moveEvenItemsToBack(LinkedList *ll)
{
	ListNode *cur;
	cur = ll->head;
	ListNode *prev;
	prev = NULL;

	if (ll == NULL) {
		return;
	}
	//짝수 값을 가진 노드들의 연결 리스트 head
	ListNode *evenHead = NULL; 
	// 짝수 값을 가진 노드들의 연결 리스트 tail
	ListNode *evenTail = NULL; 
	// 홀수 값을 가진 노드들 중 가장 마지막 노드 
	ListNode *oddTail = NULL; 

	while (cur != NULL ) {

		// 다음 노드 
		ListNode *nextNode = cur->next; 

		//현재 노드의 item이 짝수인 경우
		if (cur -> item % 2 == 0 ) {
			//짝수 노드 연결리스트의 head가 null이라면 
			if (evenHead == NULL) {
				evenHead = cur; 
				evenTail = cur;
			}
			
			//evenHead가 null이 아니라면 
			//짝수 값이 그전에 이미 존재했다면
			else {
				evenTail -> next = cur;
				evenTail = cur; 
			}

			evenTail -> next = NULL; 

			//이전 노드가 NULL이 아니라면 
			// 이전 노드의 next 는 다음 노드 
			if (prev != NULL) {
				prev -> next = nextNode;
			} 
			else {
				//이전 노드가 NULL이면 				
				ll-> head = nextNode; 
			}
		} 

		// 현재 노드가 홀수인 경우 
		else {
			prev = cur ;
			//홀수 노드들의 연결 리스트가 NULL 이거나
			// 이전 노드의 item이 홀수라면 
			if (oddTail == NULL || prev-> item % 2 != 0) {
				oddTail = prev; 
			}

		}
		
		cur = nextNode ; 
	}

	//홀수 노드들 연결 리스트가 not null이면 
	//홀수값을 가진 노드들의 끝에 짝수 노드들 연결 
	if (oddTail != NULL) {
		oddTail -> next = evenHead; 
	} 
	//홀수 노드들 연결 리스트가 null이면 
	//바로 ll->head = evenHead; 
	else {
		ll-> head = evenHead;
	}
	
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
